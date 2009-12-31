#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>

#include "declarations.h"
#include "defines.h"



void netSendReply(struct cmdArray * thisArray, int replyCount, struct threadInfo * ti) {
	const char infoCookie[] = "000000000000000000000000";

	char *(*cmdAllocator)(struct threadInfo *);
	void (*cmdDestroyer)(char *);

	ti->s = DATA_BLOCK_SIZE;

	if((ti->sendBuffer = malloc(ti->s)) == NULL) {
		warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for reply packet", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return;
	}

	ti->k = strlen(ti->magicCookie);

	memset(ti->sendBuffer, 0, ti->s);
	memcpy(ti->sendBuffer, ti->magicCookie, ti->k);
	memcpy(ti->sendBuffer + ti->k, infoCookie, strlen(infoCookie));

	ti->o = ti->k + (replyCount * DATA_POINTER_SIZE);
	ti->k += strlen(infoCookie);

	memset(&ti->dataSpace, 0, sizeof(ti->dataSpace));

	for(ti->l = 0; ; ti->l++) {
		if(thisArray[ti->l].task == NULL) {
			break;
		}

		cmdAllocator = *thisArray[ti->l].allocator;
		cmdDestroyer = *thisArray[ti->l].destroyer;

		snprintf(ti->dataSpace, sizeof(ti->dataSpace), "%.8u", ti->o);
		memcpy(ti->sendBuffer + ti->k, ti->dataSpace, DATA_POINTER_SIZE);

		ti->k += DATA_POINTER_SIZE;

		if((ti->dataString = (char *) (*cmdAllocator)((struct threadInfo *) ti)) != NULL) {
			ti->s += strlen(ti->dataString);

			if((ti->tmpPacket = realloc(ti->sendBuffer, ti->s)) == NULL) {
				free(ti->sendBuffer);

				return;
			}

			ti->sendBuffer = ti->tmpPacket;

			memcpy(ti->sendBuffer + ti->o + strlen(infoCookie), ti->dataString, strlen(ti->dataString));

			ti->o += strlen(ti->dataString);

			if(cmdDestroyer != NULL) {
				(void) (*cmdDestroyer)((char *) ti->dataString);
			}
		}
	}

	snprintf(ti->dataSpace, sizeof(ti->dataSpace), "%.8u", DATA_COMPRESS_NONE);
	memcpy(ti->sendBuffer + strlen(ti->magicCookie), ti->dataSpace, DATA_POINTER_SIZE);

	snprintf(ti->dataSpace, sizeof(ti->dataSpace), "%.8u", ti->o);
	memcpy(ti->sendBuffer + strlen(ti->magicCookie) + DATA_POINTER_SIZE, ti->dataSpace, DATA_POINTER_SIZE);

	snprintf(ti->dataSpace, sizeof(ti->dataSpace), "%.8u", ti->o);
	memcpy(ti->sendBuffer + strlen(ti->magicCookie) + (DATA_POINTER_SIZE * 2), ti->dataSpace, DATA_POINTER_SIZE);

	ti->t = 0;

	while(1) {
		if((ti->d = send(ti->threadSocket, ti->sendBuffer, ti->o + (DATA_POINTER_SIZE * 3), 0)) == -1) {
			warningThread(ERROR_SLIGHT, "Error occurred while trying to send reply to peer", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->j);
	
			break;
		}

		ti->t += ti->d;

		if(ti->t >= ti->o + (DATA_POINTER_SIZE * 3)) {
			break;
		}
	}

	free(ti->sendBuffer);
}
