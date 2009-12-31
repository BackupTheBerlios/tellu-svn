#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"
#include "worker.h"



void workerThread(void *threadArg) {
	struct threadInfo *ti;

	void (*cmdConstructor)(struct threadInfo *);
	char *(*cmdAllocator)(struct threadInfo *);
	void (*cmdDestroyer)(struct threadInfo *);

	int (*dbSession)(char *, char *, int, int, struct threadStorageInfo *);
	int (*dbPermission)(int, char *, char *, char *, int, int, int, struct threadStorageInfo *);

	ti = (struct threadInfo *) threadArg;

	memset(ti->dataSpace, 0, sizeof(ti->dataSpace));

	dbSession = ti->dbInfo.session;
	dbPermission = ti->dbInfo.permission;

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

			memset(&ti->handlerArrays, 0, sizeof(ti->handlerArrays));

			for(ti->i = 0; ti->i < DATA_ARRAYS_COUNT; ti->i++) {
				memcpy(ti->dataSpace, ti->dataPointer, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->k = atoi(ti->dataSpace);

				memcpy(ti->dataSpace, ti->dataPointer + DATA_POINTER_SIZE, DATA_POINTER_SIZE);

				ti->dataSpace[DATA_POINTER_SIZE] = 0;
				ti->s = atoi(ti->dataSpace) - ti->k;
				ti->dataPointer += DATA_POINTER_SIZE;

				ti->handlerArrays[ti->n].buffer = NULL;
				ti->handlerArrays[ti->n].size = 0;

				if(ti->s > 0) {
					if((ti->handlerArrays[ti->n].buffer = malloc(ti->s + 1)) == NULL) {
						warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet block, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

						break;
					}

					memcpy(ti->handlerArrays[ti->n].buffer, ti->dataPacket + ti->k, ti->s);

					ti->handlerArrays[ti->n].buffer[ti->s] = 0;
					ti->handlerArrays[ti->n].size = ti->s;
				}

				ti->n++;
			}

			netFreePacket(ti->dataPacket);

			// Handle command requested by the client
			for(ti->m = 0; ; ti->m++) {
				if(cmdArrays[ti->m].task == NULL) {
					warningThread(ERROR_SLIGHT, "Received data packet has unknown command tag, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);

					break;
				}

				if(strcmp(cmdArrays[ti->m].task, ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer) == 0) {
					// Check session cookie supplied by the client
					cmdConstructor = *cmdArrays[ti->m].constructor;
					cmdAllocator = *cmdArrays[ti->m].allocator;
					cmdDestroyer = *cmdArrays[ti->m].destroyer;

					if(cmdArrays[ti->m].level != PRIVILEGE_LEVEL_PREAUTH) {
						if(dbSession(ti->handlerArrays[HANDLER_ARRAY_COOKIE].buffer, ti->handlerArrays[HANDLER_ARRAY_UID].buffer, ti->handlerArrays[HANDLER_ARRAY_COOKIE].size, ti->handlerArrays[HANDLER_ARRAY_UID].size, &ti->storageInfo) != 0) {
							snprintf(
								ti->logSpace,
								sizeof(ti->logSpace),
								"Unauthorized access for \"%s\" command \"%s\" target \"%s\"%c",
								ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
								ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
								ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
								0
							);

							logMessage(ti->logSpace);

							cmdConstructor = *sessArrays[0].constructor;
							cmdAllocator = *sessArrays[0].allocator;
							cmdDestroyer = *sessArrays[0].destroyer;
						}

						if(dbPermission(cmdArrays[ti->m].level, ti->handlerArrays[HANDLER_ARRAY_UID].buffer, ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer, ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer, ti->handlerArrays[HANDLER_ARRAY_UID].size, ti->handlerArrays[HANDLER_ARRAY_ITEM].size, ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size, &ti->storageInfo) != 0) {
							snprintf(
								ti->logSpace,
								sizeof(ti->logSpace),
								"Permission denied for \"%s\" command \"%s\" target \"%s\"%c",
								ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
								ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
								ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
								0
							);

							logMessage(ti->logSpace);

							cmdConstructor = *sessArrays[1].constructor;
							cmdAllocator = *sessArrays[1].allocator;
							cmdDestroyer = *sessArrays[1].destroyer;
						}
					}

					// Execute command requested by the client
					if(cmdConstructor != NULL) {
						(void) (*cmdConstructor)(ti);
					}

					if(cmdAllocator != NULL) {
						if((char *) (*cmdAllocator)(ti) != NULL) {
							netSendReply(replyArrays, DATA_REPLY_COMMAND_COUNT, ti);

							if(cmdDestroyer != NULL) {
								(void) (*cmdDestroyer)(ti);
							}
						}
					}

					break;
				}
			}

			// Free data buffer arrays received from the client
			for(ti->m = 0; ti->m < DATA_ARRAYS_COUNT; ti->m++) {
				if(ti->handlerArrays[ti->m].buffer != NULL) {
					free(ti->handlerArrays[ti->m].buffer);

					ti->handlerArrays[ti->m].buffer = NULL;
				}

				ti->handlerArrays[ti->m].size = 0;
			}
		}

		netCloseSocket(ti->threadSocket);

		ti->threadReady = 0;
		ti->threadSocket = 0;

		ti->threadTasks++;
	}

	exitThread(ti, NULL);
}
