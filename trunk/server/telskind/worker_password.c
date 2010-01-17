#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *listPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// List all passwords
	return(fetchPassword(1, QUERY_TYPE_PULL, ti));
}

char *listMyPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// List my passwords
	return(fetchPassword(17, QUERY_TYPE_PULL, ti));
}

char *pullPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested password
	return(fetchPassword(2, QUERY_TYPE_PULL, ti));
}

char *newPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Create new password
	return(fetchPassword(3, QUERY_TYPE_PUSH, ti));
}

char *pushPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Modify password
	return(fetchPassword(4, QUERY_TYPE_PUSH, ti));
}

char *encryptPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Encrypt password
	return(fetchPassword(7, QUERY_TYPE_PUSH, ti));
}

char *decryptPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Decrypt password
	return(fetchPassword(8, QUERY_TYPE_PULL, ti));
}

char *searchPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Search from passwords
	return(fetchPassword(5, QUERY_TYPE_PULL, ti));
}

char *deletePassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete password
	return(fetchPassword(6, QUERY_TYPE_PUSH, ti));
}

char *attachPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach password to requested item
	return(fetchPassword(9, QUERY_TYPE_PUSH, ti));
}

char *attachDomainPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach password to requested domain
	return(fetchPassword(13, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach password globally
	return(fetchPassword(14, QUERY_TYPE_PUSH, ti));
}

char *removePassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove password from requested item
	return(fetchPassword(10, QUERY_TYPE_PUSH, ti));
}

char *removeDomainPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove password from requested domain
	return(fetchPassword(15, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalPassword(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove password globally
	return(fetchPassword(16, QUERY_TYPE_PUSH, ti));
}

char *attachedPassword(struct threadInfo * ti) {
	if(((ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) &&
	(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0)) ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// Get passwords attached in item
		return(fetchPassword(11, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get items attached in password
		return(fetchPassword(12, QUERY_TYPE_PULL, ti));
	}
}

char *fetchPassword(int getThis, int getType, struct threadInfo * ti) {
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
		(ti->handlerArrays[HANDLER_ARRAY_UID].size * 4) +
		(ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 4) +
		(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 4) +
		(ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 4) +
		(ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 4) +
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
				// List all passwords
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_PWD_LIST " FROM " TABLE_PWD " WHERE " TABLECOL_PWD_OWNER " = '%s' OR " TABLECOL_PWD_PUBLIC " = '1' ORDER BY %s%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 2:
				// Get requested password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_PWD_LIST " FROM " TABLE_PWD " WHERE (" TABLECOL_PWD_OWNER " = '%s' OR " TABLECOL_PWD_PUBLIC " = '1') AND %s = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 3:
				// Create new password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PWD " (" TABLEKEY_PWD_PWDS ") VALUES('%s', '%s', '%s', '%s')%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					0
				);

				break;
			case 4:
				// Modify password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_PWD " SET %s = '%s' WHERE " TABLECOL_PWD_OWNER " = '%s' AND " TABLECOL_PWD_NAME " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 5:
				// Search from passwords
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_PWD_LIST " FROM " TABLE_PWD " WHERE (" TABLECOL_PWD_OWNER " = '%s' OR " TABLECOL_PWD_PUBLIC " = '1') AND %s LIKE '%%%s%%' ORDER BY %s%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 6:
				// Delete password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_PWD " WHERE " TABLECOL_PWD_OWNER " = '%s' AND " TABLECOL_PWD_NAME " = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 7:
				// Encrypt password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_PWD " SET " TABLECOL_PWD_PASSWORD " = HEX(" TABLE_SECRET_HASH "_ENCRYPT('%s', '%s')) WHERE " TABLECOL_PWD_OWNER " = '%s' AND " TABLECOL_PWD_NAME " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 8:
				// Decrypt password
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLE_SECRET_HASH "_DECRYPT(UNHEX('%s'), '%s')%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					0
				);

				break;
			case 9:
				// Attach password to requested item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_MACHINE_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_PERIPHERALS_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_DEVICES_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
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
			case 10:
				// Remove password from requested item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_MACHINE_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_PERIPHERALS_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_DEVICES_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
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
			case 11:
				// Get passwords attached in item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_PWD_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_MACHINE_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_PWD_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PERIPHERALS_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_PWD_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_DEVICES_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
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
			case 12:
				// Get items attached in password
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_MACHINE_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_PERIPHERALS_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_PWD_MAP_DEVICES_ID " FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s'%c",
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
			case 13:
				// Attach password to requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
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
			case 14:
				// Attach password globally
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_PERIPHERALS_ID ") (SELECT '%s', " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_PWD_MAP " (" TABLECOL_PWD_MAP_PWD_ID ", " TABLECOL_PWD_MAP_DEVICES_ID ") (SELECT '%s', " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0')%c",
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
			case 15:
				// Remove password from requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
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
			case 16:
				// Remove password globally
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_PERIPHERALS_ID " IN (SELECT " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_PWD_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_PWD_MAP " WHERE " TABLECOL_PWD_MAP_PWD_ID " = '%s' AND " TABLECOL_PWD_MAP_DEVICES_ID " IN (SELECT " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0')%c",
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
			case 17:
				// List my passwords
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_PWD_LIST " FROM " TABLE_PWD " WHERE " TABLECOL_PWD_OWNER " = '%s' ORDER BY %s%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
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
					"Password \"%s\" modified by \"%s\" using command \"%s\"%c",
					ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
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
