#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"
#include "tellud.h"



int main(int argc, char *argv[]) {
	int i, j;
	int thisSocket, thatSocket;
	int *confPort;
	unsigned int tmpSeconds;

	char *confConfig, *confEngine, *confPassword;
	char magicCookie[] = "TELLUTELLUTELLUTELLUTELLUTELLU";

	size_t s;

	uid_t *thisUid;
	gid_t *thisGid;

	/*
	 *
	 * Initialize default values.
	 *
	 */

	pMainMainInfo = &mainMainInfo;
	pMainThreadInfo = &mainThreadInfo;

	memset(pMainMainInfo, 0, sizeof(mainMainInfo));
	memset(pMainThreadInfo, 0, sizeof(mainThreadInfo));

	memset(&threadPool, 0, sizeof(threadPool));

	/*
	 *
	 * Read command line and parse configuration file.
	 *
	 */

	cmdRead(argv, argc);

	if((confConfig = configFetch("config_file", &i)) != NULL) {
		if(configRead(confConfig) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}
	else {
		if(configRead(CONFIG_DEFAULT_FILE) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}

	cmdRead(argv, argc);

	nodeInitNames();

	/*
	 *
	 * Initialize configurable subroutines.
	 *
	 */

	pMainThreadInfo->threadReady = 1;

	for(j = 0; j < THREAD_TELLUD; j++) {
		threadPool[j].threadReady = 1;

		threadPool[j].magicCookie = magicCookie;
		threadPool[j].pMainInfo = pMainMainInfo;

		if((confEngine = configFetch("storage_engine", &i)) != NULL) {
			if(strncasecmp(confEngine, "plain", strlen(confEngine)) == 0) {
				threadPool[j].dbInfo.connect = plainConnect;
				threadPool[j].dbInfo.disconnect = plainDisconnect;
				threadPool[j].dbInfo.escape = plainEscape;
				threadPool[j].dbInfo.push = plainPush;
				threadPool[j].dbInfo.pullid = plainPullID;

				pMainThreadInfo->dbInfo.connect = plainConnect;
				pMainThreadInfo->dbInfo.disconnect = plainDisconnect;
				pMainThreadInfo->dbInfo.escape = plainEscape;
				pMainThreadInfo->dbInfo.push = plainPush;
				pMainThreadInfo->dbInfo.pullid = plainPullID;

				continue;
			}
		}

		threadPool[j].dbInfo.connect = mysqlConnect;
		threadPool[j].dbInfo.disconnect = mysqlDisconnect;
		threadPool[j].dbInfo.escape = mysqlEscape;
		threadPool[j].dbInfo.push = mysqlPush;
		threadPool[j].dbInfo.pullid = mysqlPullID;

		pMainThreadInfo->dbInfo.connect = mysqlConnect;
		pMainThreadInfo->dbInfo.disconnect = mysqlDisconnect;
		pMainThreadInfo->dbInfo.escape = mysqlEscape;
		pMainThreadInfo->dbInfo.push = mysqlPush;
		pMainThreadInfo->dbInfo.pullid = mysqlPullID;
	}

	/*
	 *
	 * Initialize magick cookie.
	 *
	 */

	if((confPassword = configFetch("agent_password", &i)) != NULL) {
		s = strlen(confPassword);

		if(s > DATA_COOKIE_SIZE) {
			s = DATA_COOKIE_SIZE;
		}

		strncpy(magicCookie, confPassword, s);
	}

	/*
	 *
	 * Initialize main thread.
	 *
	 */

	configSetUmask(0077);

	if(configSetLocale(CONFIG_DEFAULT_LOCALE) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to set default locale");
	}

	if(configChangeRoot(CONFIG_DEFAULT_ROOT) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to change root directory");
	}

	if(configCloseInput() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close standard input");
	}

	if(configDaemonize() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to daemonize process");
	}

	threadStack(THREAD_TELLUD);
	beginProcess(pMainThreadInfo);

	/*
	 *
	 * Initialize timer.
	 *
	 */

	if(timerInit(TIMER_RESOLUTION_STATUS, 0, timerStatThreads) != 0) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to initialize timer");
	}

	/*
	 *
	 * Initialize worker threads.
	 *
	 */

	pMainMainInfo->allRunning = 0;
	pMainMainInfo->theEnd = 0;
	pMainMainInfo->threadEnd = 0;

	for(i = 0; i < THREAD_TELLUD; i++) {
		if(threadInit(&threadPool[i], workerThread, &threadPool[i]) != 0) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to initialize worker thread");
		}

		j = 0;

		while(threadPool[i].threadReady != 0) {
			timerWait(&tmpSeconds, 0, THREAD_AGAIN);

			if(j == 10000 || j == 20000 || j == 30000 || j == 40000 || j == 50000) {
				warningMessage(ERROR_SLIGHT, "Waiting for worker threads to start taking too long, still waiting");
			}
			else if(j >= 60000) {
				warningMessage(ERROR_FATAL, "Waiting for threads to start taking too long");
			}

			j++;
		}
	}

	/*
	 *
	 * Create socket to listen.
	 *
	 */

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		thisSocket = netCreateListenSocket(*confPort);
	}
	else {
		thisSocket = netCreateListenSocket(CONFIG_DEFAULT_PORT);
	}

	/*
	 *
	 * Create process id, shm segment, switch user and group id's.
	 *
	 */

	pidCreate();
	shmCreate(DAEMON_TELLUD, THREAD_TELLUD);

	if((thisUid = configFetch("user_id", &i)) != NULL) {
		if(*thisUid != -1) {
			if(uidSwitch(*thisUid) != 0) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to change user id");
			}
		}
	}

	if((thisGid = configFetch("group_id", &i)) != NULL) {
		if(*thisGid != -1) {
			if(gidSwitch(*thisGid) != 0) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to change group id");
			}
		}
	}

	/*
	 *
	 * Serve connected clients.
	 *
	 */

	startProcess(THREAD_TELLUD);

	pMainMainInfo->allRunning++;
	pMainMainInfo->rushThreadCounter = 0;

	while(pMainMainInfo->theEnd == 0) {
		thatSocket = netWaitConnection(thisSocket, pMainThreadInfo);

		if(pMainMainInfo->theEnd != 0) {
			break;
		}
mainLoop:
		for(i = 0; i < THREAD_TELLUD; i++) {
			if(threadPool[i].threadReady == 0) {
				threadPool[i].threadReady++;
				threadPool[i].threadSocket = thatSocket;

				shmUpdate(i, DAEMON_TELLUD);

				if(threadWake(&threadPool[i]) != 0) {
					netCloseSocket(threadPool[i].threadSocket);

					threadPool[i].threadReady = 0;
					threadPool[i].threadSocket = 0;

					warningMessage(ERROR_SLIGHT, "Error occurred while trying to start worker thread");
				}

				pMainMainInfo->rushThreadCounter = 0;

				break;
			}
		}

		if(i == THREAD_TELLUD) {
			if(pMainMainInfo->rushThreadCounter > 1000) {
				pMainMainInfo->rushThreadCounter = 0;

				warningMessage(ERROR_SLIGHT, "No free worker thread available - it is necessary to enlarge the thread pool, dropping agent");

				netCloseSocket(thatSocket);
			}
			else {
				pMainMainInfo->rushThreadCounter++;

				if(pMainMainInfo->rushThreadCounter < 2) {
					warningMessage(ERROR_SLIGHT, "No free worker thread available, it may be necessary to enlarge the thread pool");
				}

				timerWait(&tmpSeconds, 0, THREAD_AGAIN);

				goto mainLoop;
			}
		}
	}

	/*
	 *
	 * Free allocated resources and terminate program.
	 *
	 */

	netCloseSocket(thisSocket);

	pMainMainInfo->threadEnd++;

	if(timerInit(TIMER_RESOLUTION_THREADSTOP, 0, timerStopThreads) == 0) {
		pMainMainInfo->timerThreadAccess = 1;

		for(i = 0; i < THREAD_TELLUD; i++) {
			threadWake(&threadPool[i]);
		}

		pMainMainInfo->timerThreadAccess = 0;
	}
	else {
		for(i = 0; i < THREAD_TELLUD; i++) {
			threadKill(&threadPool[i]);
		}
	}

	timesProcess(pMainThreadInfo);

	pidRemove();
	shmRemove(DAEMON_TELLUD);

	exitProcess(0);
	exit(0);
}



int checkExistence(struct threadInfo * ti) {
	for(ti->i = 0; ti->i < THREAD_TELLUD; ti->i++) {
		if(threadPool[ti->i].th != 0 && threadPool[ti->i].th == ti->th) {
			return(-1);
		}
	}

	return(0);
}

void handlerProcess(void) {
	pMainMainInfo->theEnd++;

	netDummyConnect();
}

void timerStatThreads(int signalNumber) {
	shmUsage(DAEMON_TELLUD);
}

void timerStopThreads(int signalNumber) {
	int i;

	if(pMainMainInfo->timerThreadAccess == 0) {
		return;
	}

	warningMessage(ERROR_SLIGHT, "At least one thread refused to stop it's activity as requested, using force to terminate it");

	for(i = 0; i < THREAD_TELLUD; i++) {
		threadKill(&threadPool[i]);
	}
}
