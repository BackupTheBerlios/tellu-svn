#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "declarations.h"
#include "defines.h"



int threadInit(struct threadInfo * ti, void *threadProcess, void *threadArg) {
	if(pthread_mutex_init(&ti->threadMutex, NULL) != 0) {
		return(-1);
	}

	if(pthread_cond_init(&ti->threadCond, NULL) != 0) {
		pthread_mutex_destroy(&ti->threadMutex);

		return(-1);
	}

	if(pthread_attr_init(&ti->threadAttr) != 0) {
		pthread_cond_destroy(&ti->threadCond);
		pthread_mutex_destroy(&ti->threadMutex);

		return(-1);
	}

	if(pthread_attr_setdetachstate(&ti->threadAttr, PTHREAD_CREATE_JOINABLE) != 0) {
		pthread_attr_destroy(&ti->threadAttr);
		pthread_cond_destroy(&ti->threadCond);
		pthread_mutex_destroy(&ti->threadMutex);

		return(-1);
	}

	if(pthread_create(&ti->threadID, &ti->threadAttr, threadProcess, threadArg) != 0) {
		pthread_attr_destroy(&ti->threadAttr);
		pthread_cond_destroy(&ti->threadCond);
		pthread_mutex_destroy(&ti->threadMutex);

		return(-1);
	}

	ti->ticksPerSec = sysconf(_SC_CLK_TCK);

	if(ti->ticksPerSec == 0 || ti->ticksPerSec == -1) {
		ti->ticksPerSec = 1;
	}

	ti->clockBegin = times(&ti->beginClock);

	return(0);
}

int threadKill(struct threadInfo * ti) {
	if(ti->threadID == 0) {
		return(0);
	}

	if(pthread_kill(ti->threadID, SIGKILL) != 0) {
		return(-1);
	}

	ti->threadID = 0;

	return(0);
}

int threadWait(struct threadInfo * ti) {
	if(pthread_mutex_lock(&ti->threadMutex) != 0) {
		return(-1);
	}

	if(pthread_cond_wait(&ti->threadCond, &ti->threadMutex) != 0) {
		pthread_mutex_unlock(&ti->threadMutex);

		return(-1);
	}

	pthread_mutex_unlock(&ti->threadMutex);

	return(0);
}

int threadWake(struct threadInfo * ti) {
	if(pthread_mutex_lock(&ti->threadMutex) != 0) {
		return(-1);
	}

	if(pthread_cond_signal(&ti->threadCond) != 0) {
		pthread_mutex_unlock(&ti->threadMutex);

		return(-1);
	}

	pthread_mutex_unlock(&ti->threadMutex);

	return(0);
}

void threadStack(int numThreads) {
	long i;

	struct rlimit newLimit;

	if((i = sysconf(_SC_THREAD_STACK_MIN)) == -1) {
		return;
	}

	if(getrlimit(RLIMIT_STACK, &newLimit) == -1) {
		return;
	}

	i *= numThreads;

	if(newLimit.rlim_cur < i) {
		newLimit.rlim_cur = i;

		setrlimit(RLIMIT_STACK, &newLimit);
	}
}

void beginProcess(struct threadInfo * ti) {
	struct sigaction newAction;

	ti->ticksPerSec = sysconf(_SC_CLK_TCK);

	if(ti->ticksPerSec == 0 || ti->ticksPerSec == -1) {
		ti->ticksPerSec = 1;
	}

	ti->clockBegin = times(&ti->beginClock);

	sigemptyset(&newAction.sa_mask);

	newAction.sa_flags = SA_SIGINFO | SA_RESTART;
	newAction.sa_handler = NULL;
	newAction.sa_sigaction = (void *) &handlerProcess;

	sigaction(SIGHUP, &newAction, NULL);
	sigaction(SIGINT, &newAction, NULL);
	sigaction(SIGQUIT, &newAction, NULL);
	sigaction(SIGTERM, &newAction, NULL);
}

void startProcess(int thisMany) {
	int i;
	int *confPort;
	short thisPort;

	char dataBuffer[CONFIG_SPACE_SIZE];

	thisPort = CONFIG_DEFAULT_PORT;

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		thisPort = *confPort;
	}

	snprintf(
		dataBuffer,
		sizeof(dataBuffer),
		"started, listening port %d with %d worker threads%c",
		thisPort,	
		thisMany,
		0
	);

	logMessage(dataBuffer);
}

void timesProcess(struct threadInfo * ti) {
	char dataBuffer[CONFIG_SPACE_SIZE];

	if(ti->ticksPerSec != 0) {
		ti->clockEnd = times(&ti->endClock);

		snprintf(
			dataBuffer,
			sizeof(dataBuffer),
			"terminated, elapsed %.2f secs, usr %.2f, sys %.2f, chldusr %.2f, chldsys %.2f%c",
			(float) (ti->clockEnd - ti->clockBegin) / ti->ticksPerSec,
			(float) ti->endClock.tms_utime / ti->ticksPerSec,
			(float) ti->endClock.tms_stime / ti->ticksPerSec,
			(float) ti->endClock.tms_cutime / ti->ticksPerSec,
			(float) ti->endClock.tms_cstime / ti->ticksPerSec,
			0
		);

		logMessage(dataBuffer);
	}
}

void exitProcess(int processRetValue) {
	exit(processRetValue);
}

void exitThread(struct threadInfo * ti, void *threadRetValue) {
	pthread_attr_destroy(&ti->threadAttr);
	pthread_cond_destroy(&ti->threadCond);
	pthread_mutex_destroy(&ti->threadMutex);

	if(ti->ticksPerSec != 0) {
		ti->clockEnd = times(&ti->endClock);
	}

	ti->threadID = 0;

	pthread_exit(threadRetValue);
}
