#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



void replyPrepare(unsigned int thisClass, unsigned int thisItem, unsigned int thisParam, char *thisReply, struct threadInfo * ti) {
	ti->s = CONFIG_SPACE_SIZE;

	if(thisReply != NULL) {
		ti->s += strlen(thisReply);
	}

	if((ti->dataBuffer = malloc(ti->s + 1)) != NULL) {
		if(thisReply != NULL) {
			snprintf(
				ti->dataBuffer,
				ti->s,
				"%.8u%c%.8u%c%.8u%c%s%c",
				thisClass,
				ITEM_DELIMITER,
				thisItem,
				ITEM_DELIMITER,
				thisParam,
				ITEM_DELIMITER,
				thisReply,
				0
			);
		}
		else {
			snprintf(
				ti->dataBuffer,
				ti->s,
				"%.8u%c%.8u%c%.8u%c",
				thisClass,
				ITEM_DELIMITER,
				thisItem,
				ITEM_DELIMITER,
				thisParam,
				0
			);
		}
	}
}

void replyFree(struct threadInfo * ti) {
	if(ti->dataBuffer != NULL) {
		free(ti->dataBuffer);

		ti->dataBuffer = NULL;
	}
}

char *replyThis(struct threadInfo * ti) {
	return(ti->dataBuffer);
}
