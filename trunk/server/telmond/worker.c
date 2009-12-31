#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"
#include "worker.h"



void workerThread(void *threadArg) {
	struct threadInfo *ti;

	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	void (*dbEscape)(struct threadStorageInfo *, char *, char *);
	void (*dbPush)(struct threadStorageInfo *, char *);
	char *(*dbPull)(struct threadStorageInfo *, char *);
	void (*dbFree)(struct threadStorageInfo *);

	ti = (struct threadInfo *) threadArg;

	memset(ti->dataSpace, 0, sizeof(ti->dataSpace));

	dbConnect = ti->dbInfo.connect;
	dbDisconnect = ti->dbInfo.disconnect;
	dbEscape = ti->dbInfo.escape;
	dbPush = ti->dbInfo.push;
	dbPull = ti->dbInfo.pull;
	dbFree = ti->dbInfo.free;

	ti->threadReady = 0;
	ti->threadTasks = 0;

	while(ti->pMainInfo->threadEnd == 0) {
		ti->r = threadWait(ti);

		if(ti->pMainInfo->threadEnd != 0) {
			break;
		}

		if(ti->r != 0) {
			timerWait(&ti->tmpSeconds, 0, THREAD_AGAIN);

			continue;
		}

		// Read packet from the client
		if((ti->dataPacket = netReadPacket(ti->threadSocket, ti)) != NULL) {
			// Get data strings out from data packet
			ti->dataPointer = ti->dataPacket + DATA_COOKIE_SIZE;
			ti->n = 0;

			for(ti->i = 0; ti->i < DATA_ARRAYS_COUNT; ti->i++) {
				memcpy(ti->dataSpace, ti->dataPointer, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->k = atoi(ti->dataSpace);

				memcpy(ti->dataSpace, ti->dataPointer + DATA_POINTER_SIZE, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->s = atoi(ti->dataSpace) - ti->k;
				ti->dataPointer += DATA_POINTER_SIZE;

				if(ti->s > 0 && ti->n == 3) {
					if((ti->dataBuffer = malloc(ti->s + 1)) == NULL) {
						warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

						break;
					}

					memcpy(ti->dataBuffer, ti->dataPacket + ti->k, ti->s);

					ti->dataBuffer[ti->s] = 0;

					switch(atoi(ti->dataBuffer)) {
						case STAT_USAGE_TELLUD:
							shmFetch(DAEMON_TELLUD, &ti->daemonInfo);

							netSendReply(monitorArrays, DATA_REPLY_STAT_COUNT, ti);

							break;
						case STAT_USAGE_TELMOND:
							shmFetch(DAEMON_TELMOND, &ti->daemonInfo);

							netSendReply(monitorArrays, DATA_REPLY_STAT_COUNT, ti);

							break;
						case STAT_USAGE_TELSKIND:
							shmFetch(DAEMON_TELSKIND, &ti->daemonInfo);

							netSendReply(monitorArrays, DATA_REPLY_STAT_COUNT, ti);

							break;
						case STAT_HISTORY_DAYS:
							if(dbConnect(&ti->storageInfo) != 0) {
								break;
							}

							ti->t = CONFIG_SPACE_SIZE;

							if((ti->statBuffer = malloc(ti->t)) == NULL) {
								warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

								dbDisconnect(&ti->storageInfo);

								break;
							}

							snprintf(
								ti->statBuffer, ti->t,
								"SELECT DISTINCT DAYNAME(time) AS name, DAY(time) AS day, MONTHNAME(time) AS month, YEAR(time) AS year FROM history ORDER BY time DESC LIMIT 365%c",
								0
							);

							if(dbPull(&ti->storageInfo, ti->statBuffer) == NULL) {
								free(ti->statBuffer);

								dbDisconnect(&ti->storageInfo);

								break;
							}

							free(ti->statBuffer);

							netSendReply(historyArrays, DATA_REPLY_HIST_COUNT, ti);

							dbFree(&ti->storageInfo);
							dbDisconnect(&ti->storageInfo);

							break;
						case STAT_HISTORY_CHART:
							if(dbConnect(&ti->storageInfo) != 0) {
								break;
							}

							ti->t = CONFIG_SPACE_SIZE;

							if((ti->statBuffer = malloc(ti->t)) == NULL) {
								warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

								dbDisconnect(&ti->storageInfo);

								break;
							}

							ti->tmpPacket = ti->dataBuffer;

							while(*ti->tmpPacket != ' ' && *ti->tmpPacket != 0) {
								ti->tmpPacket++;
							}

							ti->j = 0;

							for(ti->i = 0; ti->i < 24; ti->i++) {
								snprintf(
									ti->statBuffer, ti->t,
									"SELECT %s FROM %s WHERE %s AND HOUR(%s) = '%d'%c",
									TABLECOL_CHART,
									TABLE_HIST,
									ti->tmpPacket,
									TABLECOL_HIST_TIME,
									ti->i,
									0
								);

								if(dbPull(&ti->storageInfo, ti->statBuffer) != NULL) {
									if(ti->storageInfo.replyBuffer[0] == 0) {
										ti->j += snprintf(
											ti->itemSpace + ti->j,
											sizeof(ti->itemSpace) - ti->j,
											"0%c",
											ITEM_DELIMITER
										);
									}
									else {
										ti->j += snprintf(
											ti->itemSpace + ti->j,
											sizeof(ti->itemSpace) - ti->j,
											"%s%c",
											ti->storageInfo.replyBuffer,
											ITEM_DELIMITER
										);
									}

									dbFree(&ti->storageInfo);
								}
								else {
									ti->j += snprintf(
										ti->itemSpace + ti->j,
										sizeof(ti->itemSpace) - ti->j,
										"0%c",
										ITEM_DELIMITER
									);
								}
							}

							ti->itemSpace[ti->j] = 0;

							if(ti->i != 24) {
								free(ti->statBuffer);

								dbDisconnect(&ti->storageInfo);

								break;
							}

							free(ti->statBuffer);

							netSendReply(chartArrays, DATA_REPLY_CHART_COUNT, ti);

							dbDisconnect(&ti->storageInfo);

							break;
						default:
							warningThread(ERROR_SLIGHT, "Received data packet has unknown command tag, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

							break;
					}

					free(ti->dataBuffer);

					break;
				}

				ti->n++;
			}

			netFreePacket(ti->dataPacket);
		}

		netCloseSocket(ti->threadSocket);

		ti->threadReady = 0;
		ti->threadSocket = 0;

		ti->threadTasks++;
	}

	exitThread(ti, NULL);
}
