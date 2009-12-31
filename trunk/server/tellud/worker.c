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
	unsigned long long (*dbPullID)(struct threadStorageInfo *, char *);

	ti = (struct threadInfo *) threadArg;

	dbConnect = ti->dbInfo.connect;
	dbDisconnect = ti->dbInfo.disconnect;
	dbEscape = ti->dbInfo.escape;
	dbPush = ti->dbInfo.push;
	dbPullID = ti->dbInfo.pullid;

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

		if(dbConnect(&ti->storageInfo) != 0) {
			netCloseSocket(ti->threadSocket);
		}
		else {
			// Read packet from the agent
			if((ti->dataPacket = netReadPacket(ti->threadSocket, ti)) == NULL) {
				netCloseSocket(ti->threadSocket);
			}
			else {
				netCloseSocket(ti->threadSocket);

				// Get node, domain and system out from data packet
				ti->dataPointer = ti->dataPacket + DATA_COOKIE_SIZE + (DATA_POINTER_SIZE * 3);

				memcpy(ti->dataSpace, ti->dataPointer, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->k = atoi(ti->dataSpace);

				memcpy(ti->dataSpace, ti->dataPointer + DATA_POINTER_SIZE, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->s = atoi(ti->dataSpace) - ti->k;
				ti->dataPointer += DATA_POINTER_SIZE;

				ti->n = 0;

				if(ti->s <= 0) {
					ti->n++;
				}
				else {
					if((ti->dataBuffer = malloc(ti->s + 1)) == NULL) {
						ti->n++;
					}
					else {
						if((ti->escpBuffer = malloc((ti->s * 2) + 2)) == NULL) {
							free(ti->dataBuffer);

							ti->n++;
						}
						else {
							ti->t = (ti->s * 3) + CONFIG_SPACE_SIZE;

							if((ti->statBuffer = malloc(ti->t)) == NULL) {
								free(ti->dataBuffer);
								free(ti->escpBuffer);

								ti->n++;
							}
						}
					}
				}

				if(ti->n != 0) {
					warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);
				}
				else {
					ti->n = 0;

					// Get one piece of data string and construct SQL statement
					ti->o = snprintf(
						ti->statBuffer, ti->t,
						"SELECT " TABLEKEY_ID " FROM " TABLE_NODEDATA " WHERE " TABLEKEY_DISPOSED " = 0 AND %s = ",
						workerKeys[ti->n]
					);

					ti->l = 0;

					for(ti->j = 0; ti->j < ti->s + 1; ti->j++) {
						if(ti->dataPacket[ti->k + ti->j] == ITEM_SEPARATOR ||
						   ti->dataPacket[ti->k + ti->j] == 0 ||
						   ti->j == ti->s) {
							ti->dataBuffer[ti->l] = 0;

							dbEscape(&ti->storageInfo, ti->escpBuffer, ti->dataBuffer);

							ti->o += snprintf(
								ti->statBuffer + ti->o, ti->t - ti->o,
								"'%s'",
								ti->escpBuffer
							);

							if(ti->n++ == 2) {
								ti->o += snprintf(
									ti->statBuffer + ti->o, ti->t - ti->o,
									"%c",
									0
								);

								break;
							}

							ti->o += snprintf(
								ti->statBuffer + ti->o, ti->t - ti->o,
								" AND %s=",
								workerKeys[ti->n]
							);

							ti->l = 0;
						}
						else {
							ti->dataBuffer[ti->l++] = ti->dataPacket[ti->k + ti->j];
						}
					}

					free(ti->dataBuffer);
					free(ti->escpBuffer);

					// Check machine's existence
					ti->th = 0;
					ti->id = dbPullID(&ti->storageInfo, ti->statBuffer);

					if(ti->id == -1) {
						free(ti->statBuffer);

						break;
					}
					else if(ti->id == 0) {
						// Machine is new, get new id for it and create bare tables
						ti->id = randGetId(ti);
						ti->th = ti->id;

						snprintf(
							ti->statBuffer, ti->t,
							"INSERT INTO " TABLE_MACHINEDATA " (" TABLECOL_MACHINE ") VALUES('%llu', '" APPLICATION_NAME " " APPLICATION_VERSION "')%c",
							ti->id,
							0
						);

						dbPush(&ti->storageInfo, ti->statBuffer);
					}
					else {
						// Machine is already in database, update existing content
						if(checkExistence(ti) != 0) {
							free(ti->statBuffer);

							warningThread(ERROR_SLIGHT, "Agent is already being served, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

							break;
						}

						ti->th = ti->id;

						for(ti->i = 0; ; ti->i++) {
							if(workerTables[ti->i] == NULL) {
								break;
							}

							snprintf(
								ti->statBuffer, ti->t,
								"DELETE FROM %s WHERE " TABLEKEY_ID " = '%llu'%c",
								workerTables[ti->i], ti->id,
								0
							);

							dbPush(&ti->storageInfo, ti->statBuffer);
						}

						snprintf(
							ti->statBuffer, ti->t,
							"UPDATE " TABLE_MACHINEDATA " SET " TABLEKEY_MOFIFIER " = '" APPLICATION_NAME " " APPLICATION_VERSION "', " TABLEKEY_MODIFIED " = NOW() WHERE " TABLEKEY_ID " = '%llu'%c",
							ti->id,
							0
						);

						dbPush(&ti->storageInfo, ti->statBuffer);
					}

					free(ti->statBuffer);

					// Get data strings out from data packet
					ti->dataPointer = ti->dataPacket + DATA_COOKIE_SIZE;
					ti->n = 0;

					// Loop through data pointers
					for(ti->i = 0; ti->i < DATA_ARRAYS_COUNT; ti->i++) {
						memcpy(ti->dataSpace, ti->dataPointer, DATA_POINTER_SIZE);

						ti->dataSpace[DATA_POINTER_SIZE] = 0;
						ti->k = atoi(ti->dataSpace);

						memcpy(ti->dataSpace, ti->dataPointer + DATA_POINTER_SIZE, DATA_POINTER_SIZE);

						ti->dataSpace[DATA_POINTER_SIZE] = 0;
						ti->s = atoi(ti->dataSpace) - ti->k;
						ti->dataPointer += DATA_POINTER_SIZE;

						// Allocate buffers for SQL statement construction
						if(ti->s > 0) {
							if((ti->dataBuffer = malloc(ti->s + 1)) == NULL) {
								warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

								break;
							}

							if((ti->escpBuffer = malloc((ti->s * 2) + 2)) == NULL) {
								free(ti->dataBuffer);

								warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

								break;
							}

							ti->t = (ti->s * 3) + CONFIG_SPACE_SIZE;

							if((ti->statBuffer = malloc(ti->t)) == NULL) {
								free(ti->dataBuffer);
								free(ti->escpBuffer);

								warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

								break;
							}

							ti->o = snprintf(
								ti->statBuffer, ti->t,
								"INSERT INTO %s (%s) VALUES('%llu',",
								workerTables[ti->n], workerCols[ti->n], ti->id
							);

							ti->l = 0;

							// Get one piece of data string and construct SQL statement
							for(ti->j = 0; ti->j < ti->s + 1; ti->j++) {
								if(ti->dataPacket[ti->k + ti->j] == ITEM_SEPARATOR ||
								   ti->dataPacket[ti->k + ti->j] == ITEM_DELIMITER ||
								   ti->dataPacket[ti->k + ti->j] == 0 ||
								   ti->j == ti->s) {
									ti->dataBuffer[ti->l] = 0;

									dbEscape(&ti->storageInfo, ti->escpBuffer, ti->dataBuffer);

									ti->o += snprintf(
										ti->statBuffer + ti->o, ti->t - ti->o,
										"'%s'",
										ti->escpBuffer
									);

									if(ti->dataPacket[ti->k + ti->j] == ITEM_DELIMITER) {
										ti->o += snprintf(
											ti->statBuffer + ti->o, ti->t - ti->o,
											")%c",
											0
										);

										dbPush(&ti->storageInfo, ti->statBuffer);

										ti->o = snprintf(
											ti->statBuffer, ti->t,
											"INSERT INTO %s (%s) VALUES('%llu',",
											workerTables[ti->n], workerCols[ti->n], ti->id
										);
									}
									else if(ti->j == ti->s) {
										ti->o += snprintf(
											ti->statBuffer + ti->o, ti->t - ti->o,
											")%c",
											0
										);
									}
									else {
										ti->o += snprintf(
											ti->statBuffer + ti->o, ti->t - ti->o,
											","
										);
									}

									ti->l = 0;
								}
								else {
									ti->dataBuffer[ti->l++] = ti->dataPacket[ti->k + ti->j];
								}
							}

							dbPush(&ti->storageInfo, ti->statBuffer);

							free(ti->dataBuffer);
							free(ti->escpBuffer);
							free(ti->statBuffer);
						}

						ti->n++;
					}
				}

				netFreePacket(ti->dataPacket);
			}

			dbDisconnect(&ti->storageInfo);
		}

		ti->th = 0;

		ti->threadReady = 0;
		ti->threadSocket = 0;

		ti->threadTasks++;
	}

	exitThread(ti, NULL);
}
