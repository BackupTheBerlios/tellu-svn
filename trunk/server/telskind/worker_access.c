#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *needLogin(struct threadInfo * ti) {
	replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGINNEEDED, ERROR_MESS_AUTH_LOGINNEEDED, ti);

	return(ti->dataBuffer);
}

char *needPerms(struct threadInfo * ti) {
	replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_PERMISSIONDENIED, ERROR_MESS_AUTH_PERMISSIONDENIED, ti);

	return(ti->dataBuffer);
}

char *tryLogin(struct threadInfo * ti) {
	int (*dbLogin)(char *, char *, int, int, struct threadStorageInfo *);

	dbLogin = ti->dbInfo.login;

	// Try authenticate against ldap
	if((ti->storageInfo.mysqlBool = configFetch("auth_ldap", &ti->storageInfo.i)) != NULL) {
		if(*ti->storageInfo.mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(ldapLogin(ti->handlerArrays[HANDLER_ARRAY_UID].buffer, ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer, ti) != 0) {
				replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGINFAILED, ERROR_MESS_AUTH_LOGINFAILED, ti);

				return(ti->dataBuffer);
			}

			replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.cookieSpace, ti);

			return(ti->dataBuffer);
		}
	}

	// Try authenticate against local database
	if((ti->storageInfo.mysqlBool = configFetch("auth_internal", &ti->storageInfo.i)) != NULL) {
		if(*ti->storageInfo.mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(dbLogin(ti->handlerArrays[HANDLER_ARRAY_UID].buffer, ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer, ti->handlerArrays[HANDLER_ARRAY_UID].size, ti->handlerArrays[HANDLER_ARRAY_ITEM].size, &ti->storageInfo) != 0) {
				replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGINFAILED, ERROR_MESS_AUTH_LOGINFAILED, ti);

				return(ti->dataBuffer);
			}
		}
		else {
			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGINNOTNEEDED, ERROR_MESS_AUTH_LOGINNOTNEEDED, ti);

			return(ti->dataBuffer);
		}
	}

	// Login was successful
	replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.cookieSpace, ti);

	return(ti->dataBuffer);
}

char *tryLogout(struct threadInfo * ti) {
	int (*dbLogout)(char *, int, struct threadStorageInfo *);

	dbLogout = ti->dbInfo.logout;

	if((ti->storageInfo.mysqlBool = configFetch("auth_internal", &ti->storageInfo.i)) != NULL) {
		if(*ti->storageInfo.mysqlBool == CONFIG_TYPE_BOOLEAN_NO) {
			replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGOUTNOTNEEDED, ERROR_MESS_AUTH_LOGOUTNOTNEEDED, ti);

			return(ti->dataBuffer);
		}
	}

	if(dbLogout(ti->handlerArrays[HANDLER_ARRAY_UID].buffer, ti->handlerArrays[HANDLER_ARRAY_UID].size, &ti->storageInfo) != 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_AUTH, ERROR_CODE_AUTH_LOGOUTFAILED, ERROR_MESS_AUTH_LOGOUTFAILED, ti);

		return(ti->dataBuffer);
	}

	replyPrepare(ERROR_NOERROR, 0, 0, NULL, ti);

	return(ti->dataBuffer);
}

char *changeOwnPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	return(fetchAccess(1, QUERY_TYPE_PUSH, ti));
}

char *changeUserPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	return(fetchAccess(2, QUERY_TYPE_PUSH, ti));
}

char *isAuthLDAP(struct threadInfo * ti) {
	// Check if authenticating against ldap
	if((ti->storageInfo.mysqlBool = configFetch("auth_ldap", &ti->storageInfo.i)) != NULL) {
		if(*ti->storageInfo.mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			replyPrepare(ERROR_NOERROR, 0, 0, "yes", ti);

			return(ti->dataBuffer);
		}
	}

	replyPrepare(ERROR_NOERROR, 0, 0, "no", ti);

	return(ti->dataBuffer);
}

char *isUserAdmin(struct threadInfo * ti) {
	return(fetchAccess(3, QUERY_TYPE_PULL, ti));
}

char *fetchAccess(int getThis, int getType, struct threadInfo * ti) {
	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	void (*dbEscape)(struct threadStorageInfo *, char *, char *);
	void (*dbPush)(struct threadStorageInfo *, char *);
	char *(*dbPull)(struct threadStorageInfo *, char *);
	void (*dbFree)(struct threadStorageInfo *);

	dbConnect = ti->dbInfo.connect;
	dbDisconnect = ti->dbInfo.disconnect;
	dbEscape = ti->dbInfo.escape;
	dbPush = ti->dbInfo.push;
	dbPull = ti->dbInfo.pull;
	dbFree = ti->dbInfo.free;

	ti->commandInfo.esc1Buffer = NULL;
	ti->commandInfo.esc2Buffer = NULL;
	ti->commandInfo.esc3Buffer = NULL;
	ti->commandInfo.esc4Buffer = NULL;
	ti->commandInfo.esc5Buffer = NULL;

	// Allocate memory for buffers
	ti->commandInfo.s =
		(ti->handlerArrays[HANDLER_ARRAY_UID].size * 2) +
		(ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 2) +
		(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 2) +
		(ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 2) +
		(ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 2) +
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
				// Change own password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_USERS " SET " TABLECOL_USER_PWD " = " TABLE_PWD_HASH "('%s') WHERE " TABLECOL_USER_UID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc1Buffer,
					0
				);

				break;
			case 2:
				// Change user's password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_USERS " SET " TABLECOL_USER_PWD " = " TABLE_PWD_HASH "('%s') WHERE " TABLECOL_USER_UID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 3:
				// Check if requestor is admin or not
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
"SELECT DISTINCT " TABLECOL_USER_PERM " FROM " TABLE_PERM_NODES " WHERE " TABLECOL_USER_USID " IN (SELECT " TABLECOL_USER_ID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s') AND " TABLECOL_USER_DOMAIN " = '' AND " TABLECOL_USER_GRP " = '' AND " TABLECOL_USER_PERM " = '" PRIVILEGE_LEVEL_ADMIN_S "'%c",
					ti->commandInfo.esc1Buffer,
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

				snprintf(
					ti->logSpace,
					sizeof(ti->logSpace),
					"User \"%s\" modified by \"%s\" using command \"%s\"%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
					ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
					0
				);

				logMessage(ti->logSpace);

				replyPrepare(ERROR_NOERROR, 0, 0, ti->storageInfo.replyBuffer, ti);

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
