#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



char *listMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// List all domains
		return(fetchMachine(1, QUERY_TYPE_PULL, ti));
	}
	else {
		// List all machines in requested domain
		return(fetchMachine(2, QUERY_TYPE_PULL, ti));
	}
}

char *pullMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Brief all machines in all domains
		return(fetchMachine(3, QUERY_TYPE_PULL, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Brief all machines in requested domain
			return(fetchMachine(4, QUERY_TYPE_PULL, ti));
		}
		else {
			// Get requested machine
			return(fetchMachine(5, QUERY_TYPE_PULL, ti));
		}
	}
}

char *pullMachineByID(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested machine by id
	return(fetchMachine(30, QUERY_TYPE_PULL, ti));
}

char *pushMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Modify all machines in all domains
		return(fetchMachine(6, QUERY_TYPE_PUSH, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Modify all machines in requested domain
			return(fetchMachine(7, QUERY_TYPE_PUSH, ti));
		}
		else {
			// Modify requested machine
			return(fetchMachine(8, QUERY_TYPE_PUSH, ti));
		}
	}
}

char *searchMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Search from all machines in all domains
		return(fetchMachine(9, QUERY_TYPE_PULL, ti));
	}
	else {
		// Search from all machines in requested domain
		return(fetchMachine(10, QUERY_TYPE_PULL, ti));
	}
}

char *deleteMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Delete all machines in all domains
		return(fetchMachine(11, QUERY_TYPE_PUSH, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Delete all machines in requested domain
			return(fetchMachine(12, QUERY_TYPE_PUSH, ti));
		}
		else {
			// Delete requested machine
			return(fetchMachine(13, QUERY_TYPE_PUSH, ti));
		}
	}
}

char *listDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// List all disposed domains
		return(fetchMachine(14, QUERY_TYPE_PULL, ti));
	}
	else {
		// List all disposed machines in requested domain
		return(fetchMachine(15, QUERY_TYPE_PULL, ti));
	}
}

char *restoreDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Restore all disposed machines in all domains
		return(fetchMachine(16, QUERY_TYPE_PUSH, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Restore all disposed machines in requested domain
			return(fetchMachine(17, QUERY_TYPE_PUSH, ti));
		}
		else {
			// Restore requested disposed machine
			return(fetchMachine(18, QUERY_TYPE_PUSH, ti));
		}
	}
}

char *pullDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Brief all disposed machines in all domains
		return(fetchMachine(19, QUERY_TYPE_PULL, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Brief all disposed machines in requested domain
			return(fetchMachine(20, QUERY_TYPE_PULL, ti));
		}
		else {
			// Get requested disposed machine
			return(fetchMachine(21, QUERY_TYPE_PULL, ti));
		}
	}
}

char *pullDisposedMachineByID(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested disposed machine by id
	return(fetchMachine(31, QUERY_TYPE_PULL, ti));
}

char *pushDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Modify all disposed machines in all domains
		return(fetchMachine(22, QUERY_TYPE_PUSH, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Modify all disposed machines in requested domain
			return(fetchMachine(23, QUERY_TYPE_PUSH, ti));
		}
		else {
			// Modify requested disposed machine
			return(fetchMachine(24, QUERY_TYPE_PUSH, ti));
		}
	}
}

char *searchDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Search from all disposed machines in all domains
		return(fetchMachine(25, QUERY_TYPE_PULL, ti));
	}
	else {
		// Search from all disposed machines in requested domain
		return(fetchMachine(26, QUERY_TYPE_PULL, ti));
	}
}

char *deleteDisposedMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
		// Delete all disposed machines in all domains
		return(fetchMachine(27, QUERY_TYPE_PUSH, ti));
	}
	else {
		if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
			// Delete all disposed machines in requested domain
			return(fetchMachine(28, QUERY_TYPE_PUSH, ti));
		}
		else {
			// Delete requested disposed machine
			return(fetchMachine(29, QUERY_TYPE_PUSH, ti));
		}
	}
}

char *fetchMachine(int getThis, int getType, struct threadInfo * ti) {
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
		(ti->handlerArrays[HANDLER_ARRAY_UID].size * 14) +
		(ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 14) +
		(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 14) +
		(ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 14) +
		(ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 14) +
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
				// List all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT %s FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 2:
				// List all machines in requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT %s FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0' AND " TABLECOL_MACHINE_DOMAIN " = '%s' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc3Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 3:
				// Brief all machines in all domains
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
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
			case 4:
				// Brief all machines in requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
						ti->commandInfo.esc3Buffer,
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
			case 5:
				// Get data from requested machine
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
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
			case 6:
				// Modify all machines in all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					0
				);

				break;
			case 7:
				// Modify all machines in requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
					0
				);

				break;
			case 8:
				// Modify requested machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
					0
				);

				break;
			case 9:
				// Search from all machines in all domains
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DAEMON " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DEV " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DISK " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NIC " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NODE " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PORT " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PROC " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SOFTWARE " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SYSTEM " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_USER) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_USER " AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
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
			case 10:
				// Search from all machines in requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DAEMON ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DEV ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DISK ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NIC ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NODE ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PORT ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PROC ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SOFTWARE ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SYSTEM ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_USER) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_USER ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
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
				// Delete all machines in all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					0
				);

				break;
			case 12:
				// Delete all machines in domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					ti->commandInfo.esc3Buffer,
					0
				);

				break;
			case 13:
				// Delete machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0'%c",
					ti->commandInfo.esc3Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 14:
				// List all disposed domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT %s FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 15:
				// List all disposed machines in requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT %s FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1' AND " TABLECOL_MACHINE_DOMAIN " = '%s' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc3Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 16:
				// Restore all disposed machines in all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = 0 WHERE " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					0
				);

				break;
			case 17:
				// Restore all disposed machines in domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = 0 WHERE " TABLECOL_MACHINE_DISPOSED " = '1' AND " TABLECOL_MACHINE_DOMAIN " = '%s'%c",
					ti->commandInfo.esc3Buffer,
					0
				);

				break;
			case 18:
				// Restore requested disposed machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = 0 WHERE " TABLECOL_MACHINE_DISPOSED " = '1' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_NODE " = '%s'%c",
					ti->commandInfo.esc3Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 19:
				// Brief all disposed machines in all domains
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
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
			case 20:
				// Brief all disposed machines in requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
						ti->commandInfo.esc3Buffer,
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
			case 21:
				// Get requested disposed machine
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1') ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
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
			case 22:
				// Modify all disposed machines in all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					0
				);

				break;
			case 23:
				// Modify all disposed machines in requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
					0
				);

				break;
			case 24:
				// Modify requested disposed machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET %s = '%s' WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer,
					ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
					ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
					0
				);

				break;
			case 25:
				// Search from all disposed machines in all domains
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DAEMON " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DEV " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DISK " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NIC " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NODE " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PORT " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PROC " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SOFTWARE " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SYSTEM " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_USER) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_USER " AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
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
			case 26:
				// Search from all disposed machines in requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DAEMON ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DEV ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_DISK ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NIC ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_NODE ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PORT ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_PROC ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SOFTWARE ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_SYSTEM ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_USER) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM %s " TABLESRC_MACHINE_USER ") AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
						ti->commandInfo.esc4Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc3Buffer,
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
			case 27:
				// Delete all disposed machines in all domains
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					0
				);

				break;
			case 28:
				// Delete all disposed machines in requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					ti->commandInfo.esc3Buffer,
					0
				);

				break;
			case 29:
				// Delete requested disposed machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLECOL_MACHINE_NODE " SET " TABLECOL_MACHINE_DISPOSED " = " TABLECOL_MACHINE_DISPOSED " + 1 WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '1'%c",
					ti->commandInfo.esc3Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 30:
				// Get data from requested machine by id
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NAME) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NAME " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
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
			case 31:
				// Get data from requested disposed machine by id
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_CPU) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_CPU " FROM " TABLECOL_MACHINE_CPU " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DAEMON) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DAEMON " FROM " TABLECOL_MACHINE_DAEMON " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DAEMON "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DEV) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DEV " FROM " TABLECOL_MACHINE_DEV " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DEV "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_DISK) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_DISK " FROM " TABLECOL_MACHINE_DISK " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_DISK "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_MEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_MEM " FROM " TABLECOL_MACHINE_MEM " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NAME) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NAME " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NIC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_NIC " FROM " TABLECOL_MACHINE_NIC " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_NIC "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_NODE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_NODE " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PORT) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_PORT " FROM " TABLECOL_MACHINE_PORT " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_PROC) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_PROC " FROM " TABLECOL_MACHINE_PROC " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_PROC "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_RUN) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_RUN " FROM " TABLECOL_MACHINE_RUN " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_UTIL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLEKEY_MACHINE_UTIL " FROM " TABLECOL_MACHINE_UTIL " WHERE " TABLECOL_MACHINE_NID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SOFTWARE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SOFTWARE " FROM " TABLECOL_MACHINE_SOFTWARE " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_SOFTWARE "%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer, TABLECOL_MACHINE_SYSTEM) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT " TABLEKEY_MACHINE_SYSTEM " FROM " TABLECOL_MACHINE_SYSTEM " WHERE " TABLECOL_MACHINE_NID " = '%s' ORDER BY " TABLEORD_MACHINE_SYSTEM "%c",
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
			default:
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT '" APPLICATION_NAME " " APPLICATION_VERSION " (c) " APPLICATION_YEAR " " APPLICATION_COPYRIGHT "'%c",
					0
				);

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

				if(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0) {
					snprintf(
						ti->logSpace,
						sizeof(ti->logSpace),
						"Machine \"*/*\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
						ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
						0
					);
				}
				else {
					if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
						snprintf(
							ti->logSpace,
							sizeof(ti->logSpace),
							"Machine \"*/%s\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
							ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
							ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
							ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
							ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
							0
						);
					}
					else {
						snprintf(
							ti->logSpace,
							sizeof(ti->logSpace),
							"Machine \"%s/%s\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
							ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
							ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer,
							ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
							ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
							ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer,
							0
						);
					}
				}

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
