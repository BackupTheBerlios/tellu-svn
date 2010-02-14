#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *listUser(struct threadInfo * ti) {
	// List all users
	return(fetchUser(1, QUERY_TYPE_PULL, ti));
}

char *pullUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested user
	return(fetchUser(2, QUERY_TYPE_PULL, ti));
}

char *searchUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Search from users
	return(fetchUser(3, QUERY_TYPE_PULL, ti));
}

char *newUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Create new user
	return(fetchUser(4, QUERY_TYPE_PUSH, ti));
}

char *pushOwnUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Modify own user
	return(fetchUser(5, QUERY_TYPE_PUSH, ti));
}

char *pushUserUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Modify existing user
	return(fetchUser(6, QUERY_TYPE_PUSH, ti));
}

char *deleteUser(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete existing user
	fetchUser(9, QUERY_TYPE_PUSH, ti);
	fetchUser(8, QUERY_TYPE_PUSH, ti);

	return(fetchUser(7, QUERY_TYPE_PUSH, ti));
}

char *fetchUser(int getThis, int getType, struct threadInfo * ti) {
	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	void (*dbEscape)(struct threadStorageInfo *, char *, char *);
	void (*dbPush)(struct threadStorageInfo *, char *);
	char *(*dbPull)(struct threadStorageInfo *, char *);
	char *(*dbRound)(struct threadStorageInfo *, char *);
	void (*dbFree)(struct threadStorageInfo *);

	dbConnect = ti->dbInfo.connect;
	dbDisconnect = ti->dbInfo.disconnect;
	dbEscape = ti->dbInfo.escape;
	dbPush = ti->dbInfo.push;
	dbPull = ti->dbInfo.pull;
	dbRound = ti->dbInfo.round;
	dbFree = ti->dbInfo.free;

	ti->commandInfo.esc1Buffer = NULL;
	ti->commandInfo.esc2Buffer = NULL;
	ti->commandInfo.esc3Buffer = NULL;
	ti->commandInfo.esc4Buffer = NULL;
	ti->commandInfo.esc5Buffer = NULL;

	// Allocate memory for buffers
	ti->commandInfo.s =
		(ti->handlerArrays[HANDLER_ARRAY_UID].size * 10) +
		(ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 10) +
		(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 10) +
		(ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 10) +
		(ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 10) +
		CONFIG_SPACE_SIZE;

	if((ti->commandInfo.statBuffer = malloc(ti->commandInfo.s + 1)) == NULL) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

		return(ti->dataBuffer);
	}

	// Escape parameters received from the client
	if(ti->handlerArrays[HANDLER_ARRAY_UID].buffer != NULL && ti->handlerArrays[HANDLER_ARRAY_UID].buffer[0] != 0) {
		if((ti->commandInfo.esc1Buffer = malloc((ti->handlerArrays[HANDLER_ARRAY_UID].size * 2) + 1)) == NULL) {
			free(ti->commandInfo.statBuffer);

			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

			return(ti->dataBuffer);
		}

		dbEscape(&ti->storageInfo, ti->commandInfo.esc1Buffer, ti->handlerArrays[HANDLER_ARRAY_UID].buffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer != NULL && ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] != 0) {
		if((ti->commandInfo.esc2Buffer = malloc((ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 2) + 1)) == NULL) {
			free(ti->commandInfo.statBuffer);
			free(ti->commandInfo.esc1Buffer);

			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

			return(ti->dataBuffer);
		}

		dbEscape(&ti->storageInfo, ti->commandInfo.esc2Buffer, ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer != NULL && ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] != 0) {
		if((ti->commandInfo.esc3Buffer = malloc((ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 2) + 1)) == NULL) {
			free(ti->commandInfo.statBuffer);
			free(ti->commandInfo.esc1Buffer);
			free(ti->commandInfo.esc2Buffer);

			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

			return(ti->dataBuffer);
		}

		dbEscape(&ti->storageInfo, ti->commandInfo.esc3Buffer, ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer != NULL && ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] != 0) {
		if((ti->commandInfo.esc4Buffer = malloc((ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 2) + 1)) == NULL) {
			free(ti->commandInfo.statBuffer);
			free(ti->commandInfo.esc1Buffer);
			free(ti->commandInfo.esc2Buffer);
			free(ti->commandInfo.esc3Buffer);

			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

			return(ti->dataBuffer);
		}

		dbEscape(&ti->storageInfo, ti->commandInfo.esc4Buffer, ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer != NULL && ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] != 0) {
		if((ti->commandInfo.esc5Buffer = malloc((ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 2) + 1)) == NULL) {
			free(ti->commandInfo.statBuffer);
			free(ti->commandInfo.esc1Buffer);
			free(ti->commandInfo.esc2Buffer);
			free(ti->commandInfo.esc3Buffer);
			free(ti->commandInfo.esc4Buffer);

			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_OUTOFMEMORY, ERROR_MESS_SERVER_OUTOFMEMORY, ti);

			return(ti->dataBuffer);
		}

		dbEscape(&ti->storageInfo, ti->commandInfo.esc5Buffer, ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer);
	}

	// Connect to database
	if(dbConnect(&ti->storageInfo) != 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_DATABASE, ERROR_CODE_DATABASE_CONNECTFAILED, ERROR_MESS_DATABASE_CONNECTFAILED, ti);
	}
	else {
		// Construct SQL statement for requested item
		switch(getThis) {
			case 1:
				// List all users
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_USER_LIST " FROM " TABLE_USERS " ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 2:
				// Get requested user
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_DESCR) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_DESCR " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_GECOS) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_GECOS " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_HOMEPAGE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_HOMEPAGE " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_LOCKED) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_LOCKED " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_NOTE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_NOTE " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_PREFS) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_PREFS " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_USER_UID) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_USER_UID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT '" APPLICATION_NAME " " APPLICATION_VERSION " (c) " APPLICATION_YEAR " " APPLICATION_COPYRIGHT "'%c",
						0
					);
				}

				break;
			case 3:
				// Search from users
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
"SELECT " TABLEKEY_USER_LIST " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " LIKE '%%%s%%' OR " TABLECOL_USER_GECOS " LIKE '%%%s%%' OR " TABLECOL_USER_HOMEPAGE " LIKE '%%%s%%' OR " TABLECOL_USER_DESCR " LIKE '%%%s%%' OR " TABLECOL_USER_NOTE " LIKE '%%%s%%' ORDER BY " TABLECOL_USER_UID "%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 4:
				// Create new user
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_USERS " (" TABLECOL_USER_UID ") VALUES('%s')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 5:
				// Modify own user
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_USERS " SET %s = '%s' WHERE " TABLECOL_USER_UID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc1Buffer,
					0
				);

				break;
			case 6:
				// Modify existing user
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_USERS " SET %s = '%s' WHERE " TABLECOL_USER_UID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 7:
				// Delete existing user
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 8:
				// Delete existing user privileges
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_PERM_NODES " WHERE " TABLECOL_USER_USID " IN (SELECT DISTINCT " TABLECOL_USER_ID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 9:
				// Delete existing user sessions
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_SESSION " WHERE " TABLECOL_SESSION_UID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			default:
				replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_INTERNALERROR, ERROR_MESS_SERVER_INTERNALERROR, ti);

				break;
		}

		// Pull data out from database
		switch(getType) {
			case QUERY_TYPE_PULL:
				if(dbPull(&ti->storageInfo, ti->commandInfo.statBuffer) == NULL) {
					replyPrepare(ERROR_SLIGHT, ERROR_CLASS_DATABASE, ERROR_CODE_DATABASE_PULLFAILED, ERROR_MESS_DATABASE_PULLFAILED, ti);
				}
				else {
					replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.replyBuffer, ti);

					dbFree(&ti->storageInfo);
				}

				break;
			case QUERY_TYPE_PUSH:
				dbPush(&ti->storageInfo, ti->commandInfo.statBuffer);

				if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
					snprintf(
						ti->logSpace,
						sizeof(ti->logSpace),
						"User \"%s\" modified by \"%s\" using command \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
						0
					);
				}
				else {
					snprintf(
						ti->logSpace,
						sizeof(ti->logSpace),
						"User \"%s\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
						ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
						0
					);
				}

				logMessage(ti->logSpace);

				replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.replyBuffer, ti);

				break;
			case QUERY_TYPE_ROUND:
				if(dbRound(&ti->storageInfo, ti->commandInfo.statBuffer) == NULL) {
					replyPrepare(ERROR_SLIGHT, ERROR_CLASS_DATABASE, ERROR_CODE_DATABASE_PULLFAILED, ERROR_MESS_DATABASE_PULLFAILED, ti);
				}
				else {
					snprintf(
						ti->logSpace,
						sizeof(ti->logSpace),
						"User \"%s\" created by \"%s\" using command \"%s\" with param \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
						ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
						0
					);

					logMessage(ti->logSpace);

					replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.replyBuffer, ti);

					dbFree(&ti->storageInfo);
				}

				break;
			default:
				replyPrepare(ERROR_SLIGHT, ERROR_CLASS_SERVER, ERROR_CODE_SERVER_INTERNALERROR, ERROR_MESS_SERVER_INTERNALERROR, ti);

				break;
		}

		dbDisconnect(&ti->storageInfo);
	}

	// Free allocated resources and reply to the client
	if(ti->commandInfo.esc1Buffer != NULL) {
		free(ti->commandInfo.esc1Buffer);
	}

	if(ti->commandInfo.esc2Buffer != NULL) {
		free(ti->commandInfo.esc2Buffer);
	}

	if(ti->commandInfo.esc3Buffer != NULL) {
		free(ti->commandInfo.esc3Buffer);
	}

	if(ti->commandInfo.esc4Buffer != NULL) {
		free(ti->commandInfo.esc4Buffer);
	}

	if(ti->commandInfo.esc5Buffer != NULL) {
		free(ti->commandInfo.esc5Buffer);
	}

	free(ti->commandInfo.statBuffer);

	return(ti->dataBuffer);
}
