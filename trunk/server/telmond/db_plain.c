#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



int plainConnect(struct threadStorageInfo * db) {
	if((db->mysqlDatabase = configFetch("plain_file", &db->i)) == NULL) {
		db->mysqlDatabase = CONFIG_DEFAULT_PLAINFILE;
	}

	if((db->plainFile = fopen(db->mysqlDatabase, "a")) == NULL) {
		plainMessage(db, ERROR_SLIGHT, "Error occurred while trying to initialize database connection", NULL);

		return(-1);
	}

	return(0);
}

void plainDisconnect(struct threadStorageInfo * db) {
	if(db->plainFile != NULL) {
		if(fclose(db->plainFile) != 0) {
			plainMessage(db, ERROR_SLIGHT, "Error occurred while trying to terminate database connection", NULL);
		}

		db->plainFile = NULL;
	}
}

void plainEscape(struct threadStorageInfo * db, char *destString, char *srcString) {
	for(db->i = 0, db->s = 0; ; db->i++, db->s++) {
		if(srcString[db->s] == 0) {
			destString[db->i] = 0;

			break;
		}

		if(srcString[db->s] == '\'' || srcString[db->s] == '\\') {
			destString[db->i] = '\\';

			db->i++;
		}

		destString[db->i] = srcString[db->s];
	}
}

void plainMessage(struct threadStorageInfo * db, int fatalError, char *infoMessage, char *plainString) {
	if(plainString != NULL) {
		snprintf(db->errorString, sizeof(db->errorString), "%s: %s%c", infoMessage, plainString, 0);
	}
	else {
		snprintf(db->errorString, sizeof(db->errorString), "%s%c", infoMessage, 0);
	}

	warningThread(fatalError, db->errorString, db->errorSpace, sizeof(db->errorSpace), db->a, &db->i);
}

void plainPush(struct threadStorageInfo * db, char *thisString) {
	if(fwrite(thisString, strlen(thisString), 1, db->plainFile) < 1) {
		plainMessage(db, ERROR_SLIGHT, "Error occurred while trying to push data to database", thisString);
	}

	if(fwrite("\n", 1, 1, db->plainFile) < 1) {
		plainMessage(db, ERROR_SLIGHT, "Error occurred while trying to push data to database", NULL);
	}
}

char *plainPull(struct threadStorageInfo * db, char *thisString) {
	db->replyBuffer = NULL;

	return(db->replyBuffer);
}

void plainFree(struct threadStorageInfo * db) {
	if(db->replyBuffer != NULL) {
		free(db->replyBuffer);

		db->replyBuffer = NULL;
	}
}
