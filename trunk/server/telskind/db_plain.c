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

char *plainRound(struct threadStorageInfo * db, char *thisString) {
	plainPush(db, thisString);

	db->replyBuffer = NULL;

	return(db->replyBuffer);
}

void plainFree(struct threadStorageInfo * db) {
	if(db->replyBuffer != NULL) {
		free(db->replyBuffer);

		db->replyBuffer = NULL;
	}
}

void plainExpire(struct threadStorageInfo * db) {
	return;
}

int plainCookie(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	return(-1);
}

int plainInsert(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	return(-1);
}

int plainLogin(char *thisUid, char *thisPwd, int thisUidLength, int thisPwdLength, struct threadStorageInfo * db) {
	return(-1);
}

int plainLogout(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	return(-1);
}

int plainSession(char *thisCookie, char *thisUid, int thisCookieLength, int thisUidLength, struct threadStorageInfo * db) {
	db->e = 0;

	if((db->mysqlBool = configFetch("auth_ldap", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->e++;
		}
	}

	if((db->mysqlBool = configFetch("auth_internal", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->e++;
		}
	}

	if(db->e == 0) {
		return(0);
	}

	db->e = -1;

	return(db->e);
}

int plainPermission(int thisLevel, char *thisUid, char *thisItem, char *thisDomain, int thisUidLength, int thisItemLength, int thisDomainLength, struct threadStorageInfo * db) {
	return(-1);
}
