#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *listDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// List all devices
		return(fetchDevice(1, QUERY_TYPE_PULL, ti));
	}
	else {
		// List requested devices by category
		return(fetchDevice(2, QUERY_TYPE_PULL, ti));
	}
}

char *pullDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested device
	return(fetchDevice(3, QUERY_TYPE_PULL, ti));
}

char *newDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_OPTION].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_UID].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_UID].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_UID].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Create new device
	return(fetchDevice(5, QUERY_TYPE_ROUND, ti));
}

char *pushDevice(struct threadInfo * ti) {
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

	// Modify existing device
	fetchDevice(6, QUERY_TYPE_PUSH, ti);

	return(fetchDevice(7, QUERY_TYPE_PUSH, ti));
}

char *searchDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Search from devices
	return(fetchDevice(4, QUERY_TYPE_PULL, ti));
}

char *deleteDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete existing device
	fetchDevice(8, QUERY_TYPE_PUSH, ti);

	return(fetchDevice(7, QUERY_TYPE_PUSH, ti));
}

char *restoreDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Restore disposed device
	fetchDevice(9, QUERY_TYPE_PUSH, ti);

	return(fetchDevice(7, QUERY_TYPE_PUSH, ti));
}

char *attachDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device to requested machine
	return(fetchDevice(10, QUERY_TYPE_PUSH, ti));
}

char *attachDomainDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device to requested domain
	return(fetchDevice(16, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device globally
	return(fetchDevice(17, QUERY_TYPE_PUSH, ti));
}

char *attachDeviceToDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device to requested device
	return(fetchDevice(20, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalDeviceToDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device globally
	return(fetchDevice(21, QUERY_TYPE_PUSH, ti));
}

char *attachDeviceToPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device to requested peripheral
	return(fetchDevice(26, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalDeviceToPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach device globally
	return(fetchDevice(27, QUERY_TYPE_PUSH, ti));
}

char *removeDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device from requested machine
	return(fetchDevice(11, QUERY_TYPE_PUSH, ti));
}

char *removeDomainDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device to requested domain
	return(fetchDevice(18, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device globally
	return(fetchDevice(19, QUERY_TYPE_PUSH, ti));
}

char *removeDeviceFromDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device from requested device
	return(fetchDevice(24, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalDeviceFromDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device globally
	return(fetchDevice(25, QUERY_TYPE_PUSH, ti));
}

char *removeDeviceFromPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device from requested peripheral
	return(fetchDevice(30, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalDeviceFromPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove device globally
	return(fetchDevice(31, QUERY_TYPE_PUSH, ti));
}

char *attachedDevice(struct threadInfo * ti) {
	if((ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) &&
	(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0)) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// Get devices attached in machine
		return(fetchDevice(12, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get machines attached in device
		return(fetchDevice(13, QUERY_TYPE_PULL, ti));
	}
}

char *attachedDeviceDevice(struct threadInfo * ti) {
	if((ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) &&
	(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0)) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// Get devices attached in device
		return(fetchDevice(22, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get peripherals attached in device
		return(fetchDevice(23, QUERY_TYPE_PULL, ti));
	}
}

char *attachedDevicePeripheral(struct threadInfo * ti) {
	if((ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) &&
	(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0)) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL || ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 || ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// Get devices attached in peripheral
		return(fetchDevice(28, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get peripherals attached in device
		return(fetchDevice(29, QUERY_TYPE_PULL, ti));
	}
}

char *listDisposedDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// List all disposed devices
		return(fetchDevice(14, QUERY_TYPE_PULL, ti));
	}
	else {
		// List requested disposed devices by type
		return(fetchDevice(15, QUERY_TYPE_PULL, ti));
	}
}

char *fetchDevice(int getThis, int getType, struct threadInfo * ti) {
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
		(ti->handlerArrays[HANDLER_ARRAY_UID].size * 18) +
		(ti->handlerArrays[HANDLER_ARRAY_ITEM].size * 18) +
		(ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size * 18) +
		(ti->handlerArrays[HANDLER_ARRAY_PARAM].size * 18) +
		(ti->handlerArrays[HANDLER_ARRAY_OPTION].size * 18) +
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
		// Construct SQL statement for requested machine
		switch(getThis) {
			case 1:
				// List all devices
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_ID ",%s FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 2:
				// List requested devices by category
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_ID ",%s FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '0' AND " TABLECOL_DEVICE_CATEGORY " = '%s' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 3:
				// Get requested device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_DEVICE_DATA " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 4:
				// Search from devices
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_DEVICE_DATA " FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_MODEL " LIKE '%%%s%%' OR " TABLECOL_DEVICE_CATEGORY " LIKE '%%%s%%' OR " TABLECOL_DEVICE_MANUFACTURER " LIKE '%%%s%%' OR " TABLECOL_DEVICE_SIZE " LIKE '%%%s%%' OR " TABLECOL_DEVICE_IPADDRESS " LIKE '%%%s%%' OR " TABLECOL_DEVICE_SERNUM " LIKE '%%%s%%' OR " TABLECOL_DEVICE_SECNUM " LIKE '%%%s%%' OR " TABLECOL_DEVICE_LOCATION " LIKE '%%%s%%' OR " TABLECOL_DEVICE_MOSD " LIKE '%%%s%%' ORDER BY " TABLEORD_DEVICE_NAME "%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 5:
				// Create new device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE " (" TABLEKEY_DEVICE_NEW ") VALUES('%s', '%s', '%s', '%s')%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc5Buffer,
					0
				);

				break;
			case 6:
				// Modify existing device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_DEVICE " SET %s = '%s' WHERE " TABLECOL_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc5Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 7:
				// Modify existing device timestamp
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_DEVICE " SET " TABLECOL_DEVICE_MODIFIED " = NOW(), " TABLECOL_DEVICE_MODIFIER " = '%s' WHERE " TABLECOL_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 8:
				// Delete existing device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_DEVICE " SET " TABLECOL_DEVICE_DISPOSED " = " TABLECOL_DEVICE_DISPOSED " + 1 WHERE " TABLECOL_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 9:
				// Restore disposed device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_DEVICE " SET " TABLECOL_DEVICE_DISPOSED " = '0' WHERE " TABLECOL_DEVICE_DISPOSED " = '1' AND " TABLECOL_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 10:
				// Attach device to requested machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICE_ID ", " TABLECOL_DEVICE_MAP_MACHINE_ID ") VALUES('%s', '%s')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 11:
				// Remove device from requested machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s' AND " TABLECOL_DEVICE_MAP_MACHINE_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 12:
				// Get devices attached in machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_DEVICE_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_MACHINE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 13:
				// Get machines attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_MACHINE_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 14:
				// List all disposed devices
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_ID ",%s FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '1' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 15:
				// List requested disposed devices by type
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_ID ",%s FROM " TABLE_DEVICE " WHERE " TABLECOL_DEVICE_DISPOSED " = '1' AND " TABLECOL_DEVICE_CATEGORY " = '%s' ORDER BY %s%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 16:
				// Attach device to requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICE_ID ", " TABLECOL_DEVICE_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 17:
				// Attach device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICE_ID ", " TABLECOL_DEVICE_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 18:
				// Remove device to requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s' AND " TABLECOL_DEVICE_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 19:
				// Remove device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s' AND " TABLECOL_DEVICE_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 20:
				// Attach device to requested device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICE_ID ", " TABLECOL_DEVICE_MAP_DEVICES_ID ") VALUES('%s', '%s')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 21:
				// Attach device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICES_ID ", " TABLECOL_DEVICE_MAP_DEVICE_ID ") (SELECT '%s', " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 22:
				// Get devices attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_DEVICES_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 23:
				// Get peripherals attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_PERIPHERALS_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 24:
				// Remove device from requested device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s' AND " TABLECOL_DEVICE_MAP_DEVICES_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 25:
				// Remove device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICES_ID " = '%s' AND " TABLECOL_DEVICE_MAP_DEVICE_ID " IN (SELECT " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 26:
				// Attach device to requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_DEVICE_ID ", " TABLECOL_DEVICE_MAP_PERIPHERALS_ID ") VALUES('%s', '%s')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 27:
				// Attach device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_DEVICE_MAP " (" TABLECOL_DEVICE_MAP_PERIPHERALS_ID ", " TABLECOL_DEVICE_MAP_DEVICE_ID ") (SELECT '%s', " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 28:
				// Get devices attached in peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_PERIPHERALS_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 29:
				// Get peripherals attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_DEVICE_MAP_DEVICES_ID " FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 30:
				// Remove device from requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_DEVICE_ID " = '%s' AND " TABLECOL_DEVICE_MAP_PERIPHERALS_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 31:
				// Remove device globally
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_DEVICE_MAP " WHERE " TABLECOL_DEVICE_MAP_PERIPHERALS_ID " = '%s' AND " TABLECOL_DEVICE_MAP_DEVICE_ID " IN (SELECT " TABLECOL_DEVICE_ID " FROM " TABLE_DEVICE ")%c",
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
						"Device \"%s\" modified by \"%s\" using command \"%s\"%c",
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
						"Device \"%s\" modified by \"%s\" using command \"%s\" with param \"%s\"%c",
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
						"Device \"%s\" created by \"%s\" using command \"%s\" with param \"%s\"%c",
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
