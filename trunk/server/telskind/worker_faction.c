#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *listFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// List all factions
	return(fetchFaction(1, QUERY_TYPE_PULL, ti));
}

char *listMyFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// List my factions
	return(fetchFaction(15, QUERY_TYPE_PULL, ti));
}

char *pullFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested faction
	return(fetchFaction(2, QUERY_TYPE_PULL, ti));
}

char *newFaction(struct threadInfo * ti) {
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

	// Create new faction
	return(fetchFaction(3, QUERY_TYPE_PUSH, ti));
}

char *pushFaction(struct threadInfo * ti) {
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

	// Modify faction
	return(fetchFaction(4, QUERY_TYPE_PUSH, ti));
}

char *searchFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Search from factions
	return(fetchFaction(5, QUERY_TYPE_PULL, ti));
}

char *deleteFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete faction
	return(fetchFaction(6, QUERY_TYPE_PUSH, ti));
}

char *attachFaction(struct threadInfo * ti) {
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

	// Attach faction to requested item
	return(fetchFaction(7, QUERY_TYPE_PUSH, ti));
}

char *attachDomainFaction(struct threadInfo * ti) {
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

	// Attach faction to requested domain
	return(fetchFaction(11, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach faction globally
	return(fetchFaction(12, QUERY_TYPE_PUSH, ti));
}

char *removeFaction(struct threadInfo * ti) {
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

	// Remove faction from requested item
	return(fetchFaction(8, QUERY_TYPE_PUSH, ti));
}

char *removeDomainFaction(struct threadInfo * ti) {
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

	// Remove faction from requested domain
	return(fetchFaction(13, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalFaction(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove faction globally
	return(fetchFaction(14, QUERY_TYPE_PUSH, ti));
}

char *attachedFaction(struct threadInfo * ti) {
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
		// Get factions attached in item
		return(fetchFaction(9, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get items attached in faction
		return(fetchFaction(10, QUERY_TYPE_PULL, ti));
	}
}

char *fetchFaction(int getThis, int getType, struct threadInfo * ti) {
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
				// List all factions
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_FACTIONS_LIST " FROM " TABLE_FACTIONS " WHERE " TABLECOL_FACTIONS_OWNER " = '%s' OR " TABLECOL_FACTIONS_PUBLIC " = '1' ORDER BY %s%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 2:
				// Get requested faction
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_FACTIONS_LIST " FROM " TABLE_FACTIONS " WHERE (" TABLECOL_FACTIONS_OWNER " = '%s' OR " TABLECOL_FACTIONS_PUBLIC " = '1') AND %s = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 3:
				// Create new faction
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_FACTIONS " (" TABLEKEY_FACTIONS_FACTIONS ") VALUES('%s', '%s', '%s', '%s')%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					0
				);

				break;
			case 4:
				// Modify faction
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_FACTIONS " SET %s = '%s' WHERE " TABLECOL_FACTIONS_OWNER " = '%s' AND " TABLECOL_FACTIONS_NAME " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 5:
				// Search from factions
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_FACTIONS_LIST " FROM " TABLE_FACTIONS " WHERE (" TABLECOL_FACTIONS_OWNER " = '%s' OR " TABLECOL_FACTIONS_PUBLIC " = '1') AND %s LIKE '%%%s%%' ORDER BY %s%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 6:
				// Delete faction
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_FACTIONS " WHERE " TABLECOL_FACTIONS_OWNER " = '%s' AND " TABLECOL_FACTIONS_NAME " = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 7:
				// Attach faction to requested item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_MACHINE_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_DEVICES_ID ") VALUES('%s', '%s')%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_SERVICES_ID ") VALUES('%s', '%s')%c",
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
			case 8:
				// Remove faction from requested item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_MACHINE_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_DEVICES_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_SERVICES_ID " = '%s'%c",
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
			case 9:
				// Get factions attached in item
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_FACTION_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_MACHINE_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_FACTION_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_FACTION_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_DEVICES_ID " = '%s'%c",
						ti->commandInfo.esc4Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_FACTION_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_SERVICES_ID " = '%s'%c",
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
				// Get items attached in faction
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_MACHINE_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_DEVICES_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s'%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"SELECT DISTINCT " TABLECOL_FACTIONS_MAP_SERVICES_ID " FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s'%c",
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
			case 11:
				// Attach faction to requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
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
			case 12:
				// Attach faction globally
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID ") (SELECT '%s', " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_DEVICES_ID ") (SELECT '%s', " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"INSERT INTO " TABLE_FACTIONS_MAP " (" TABLECOL_FACTIONS_MAP_FACTION_ID ", " TABLECOL_FACTIONS_MAP_SERVICES_ID ") (SELECT '%s', " TABLECOL_SERVICE_ID " FROM " TABLE_SERVICE_DATA " WHERE " TABLECOL_SERVICE_DISPOSED " = '0')%c",
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
				// Remove faction from requested domain
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
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
				// Remove faction globally
				if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_MACHINE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_PERIPHERAL) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_PERIPHERALS_ID " IN (SELECT " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_DEVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_DEVICES_ID " IN (SELECT " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0')%c",
						ti->commandInfo.esc2Buffer,
						0
					);
				}
				else if(strcmp(ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer, TABLECOL_FACTIONS_MAP_SERVICE) == 0) {
					snprintf(
						ti->commandInfo.statBuffer,
						ti->commandInfo.s,
						"DELETE FROM " TABLE_FACTIONS_MAP " WHERE " TABLECOL_FACTIONS_MAP_FACTION_ID " = '%s' AND " TABLECOL_FACTIONS_MAP_SERVICES_ID " IN (SELECT " TABLECOL_SERVICE_ID " FROM " TABLE_SERVICE_DATA " WHERE " TABLECOL_SERVICE_DISPOSED " = '0')%c",
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
				// List my factions
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_FACTIONS_LIST " FROM " TABLE_FACTIONS " WHERE " TABLECOL_FACTIONS_OWNER " = '%s' ORDER BY %s%c",
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

				if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
					snprintf(
						ti->logSpace,
						sizeof(ti->logSpace),
						"Faction \"%s\" modified by \"%s\" using command \"%s\"%c",
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
						"Faction \"%s\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
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
