#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>



int timerInit(time_t timerSeconds, long timerUSeconds, void *timerProcess) {
	struct itimerval inValue;
	struct itimerval outValue;

	struct sigaction newAction;

	memset(&inValue, 0, sizeof(inValue));
	memset(&outValue, 0, sizeof(outValue));
	memset(&newAction, 0, sizeof(newAction));

	sigemptyset(&newAction.sa_mask);

	newAction.sa_flags = SA_SIGINFO | SA_RESTART;
	newAction.sa_handler = NULL;
	newAction.sa_sigaction = timerProcess;

	if((sigaction(SIGALRM, &newAction, NULL)) != 0) {
		return(-1);
	}

	inValue.it_value.tv_sec = timerSeconds;
	inValue.it_value.tv_usec = timerUSeconds;
	inValue.it_interval.tv_sec = timerSeconds;
	inValue.it_interval.tv_usec = timerUSeconds;

	outValue.it_value.tv_sec = 0;
	outValue.it_value.tv_usec = 0;
	outValue.it_interval.tv_sec = 0;
	outValue.it_interval.tv_usec = 0;

	if((setitimer(ITIMER_REAL, &inValue, &outValue)) != 0) {
		return(-1);
	}

	return(0);
}

void timerWait(unsigned int *tmpSeconds, unsigned int reqSeconds, useconds_t reqMicroSeconds) {
	if(reqSeconds > 0) {
		while(1) {
			*tmpSeconds = sleep(reqSeconds);

			if(*tmpSeconds == 0) {
				break;
			}

			reqSeconds = *tmpSeconds;
		}
	}

	if(reqMicroSeconds > 0 && reqMicroSeconds < 1000000) {
		usleep(reqMicroSeconds);
	}
}
