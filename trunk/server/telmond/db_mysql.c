#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



int mysqlConnect(struct threadStorageInfo * db) {
	if(mysql_init(&db->mysqlHandle) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to initialize database connection", NULL);

		return(-1);
	}

	if((db->mysqlHostname = configFetch("mysql_hostname", &db->i)) == NULL) {
		db->mysqlHostname = MYSQL_HOSTNAME;
	}

	if((db->mysqlSocket = configFetch("mysql_socket", &db->i)) == NULL) {
		db->mysqlSocket = MYSQL_SOCKET;
	}

	if((db->mysqlPort = configFetch("mysql_port", &db->i)) == NULL) {
		*db->mysqlPort = MYSQL_PORT;
	}

	if((db->mysqlDatabase = configFetch("mysql_database", &db->i)) == NULL) {
		db->mysqlDatabase = MYSQL_DATABASE;
	}

	if((db->mysqlUsername = configFetch("mysql_username", &db->i)) == NULL) {
		db->mysqlUsername = MYSQL_USERNAME;
	}

	if((db->mysqlPassword = configFetch("mysql_password", &db->i)) == NULL) {
		db->mysqlPassword = MYSQL_PASSWORD;
	}

	db->mysqlFlags = 0;

	if((db->mysqlBool = configFetch("mysql_compression", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->mysqlFlags |= CLIENT_COMPRESS;
		}
	}

	if((db->mysqlBool = configFetch("mysql_encryption", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->mysqlFlags |= CLIENT_SSL;
		}
	}

	if(mysql_real_connect(&db->mysqlHandle, db->mysqlHostname, db->mysqlUsername, db->mysqlPassword, db->mysqlDatabase, *db->mysqlPort, db->mysqlSocket, 0) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to establish database connection", NULL);

		return(-1);
	}

	return(0);
}

void mysqlDisconnect(struct threadStorageInfo * db) {
	mysql_close(&db->mysqlHandle);
}

void mysqlEscape(struct threadStorageInfo * db, char *destString, char *srcString) {
	mysql_real_escape_string(&db->mysqlHandle, destString, srcString, strlen(srcString));
}

void mysqlMessage(struct threadStorageInfo * db, int fatalError, char *infoMessage, char *sqlString) {
	if(sqlString != NULL) {
		snprintf(db->errorString, sizeof(db->errorString), "%s: %s: %s%c", infoMessage, sqlString, mysql_error(&db->mysqlHandle), 0);
	}
	else {
		snprintf(db->errorString, sizeof(db->errorString), "%s: %s%c", infoMessage, mysql_error(&db->mysqlHandle), 0);
	}

	warningThread(fatalError, db->errorString, db->errorSpace, sizeof(db->errorSpace), db->a, &db->i);
}

void mysqlPush(struct threadStorageInfo * db, char *thisString) {
	db->r = strlen(thisString);

	if((db->s = mysql_real_query(&db->mysqlHandle, thisString, db->r)) != 0) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to push data to database", thisString);

		return;
	}
}

char *mysqlPull(struct threadStorageInfo * db, char *thisString) {
	db->t = CONFIG_STRING_SIZE * 2;

	if((db->replyBuffer = malloc(db->t)) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", NULL);

		return(NULL);
	}

	if(mysql_real_query(&db->mysqlHandle, thisString, strlen(thisString)) != 0) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", thisString);

		return(NULL);
	}

	if((db->mysqlResult = mysql_use_result(&db->mysqlHandle)) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", NULL);

		return(NULL);
	}

	db->p = 0;
	db->l = mysql_num_fields(db->mysqlResult);

	while((db->mysqlRow = mysql_fetch_row(db->mysqlResult))) {
		for(db->k = 0; db->k < db->l; db->k++) {
			if(db->mysqlRow[db->k] == NULL || db->mysqlRow[db->k][0] == 0) {
				db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%c", ITEM_SEPARATOR);
			}
			else {
				db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%s%c", db->mysqlRow[db->k], ITEM_SEPARATOR);
			}
		}

		db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%c", ITEM_DELIMITER);
	}

	mysql_free_result(db->mysqlResult);

	if(db->p > 0) {
		db->p--;
	}

	db->replyBuffer[db->p] = 0;

	return(db->replyBuffer);
}

void mysqlFree(struct threadStorageInfo * db) {
	if(db->replyBuffer != NULL) {
		free(db->replyBuffer);

		db->replyBuffer = NULL;
	}
}
