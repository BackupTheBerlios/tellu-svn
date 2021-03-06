#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *listPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// List all peripherals
		return(fetchPeripheral(1, QUERY_TYPE_PULL, ti));
	}
	else {
		// List requested peripherals by category
		return(fetchPeripheral(2, QUERY_TYPE_PULL, ti));
	}
}

char *pullPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Get requested peripheral
	return(fetchPeripheral(3, QUERY_TYPE_PULL, ti));
}

char *newPeripheral(struct threadInfo * ti) {
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

	// Create new peripheral
	return(fetchPeripheral(5, QUERY_TYPE_ROUND, ti));
}

char *clonePeripheralAttachmentsForMachine(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_DOMAIN].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_DOMAIN].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Clone peripheral attachments for machine
	return(fetchPeripheral(32, QUERY_TYPE_PUSH, ti));
}

char *pushPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Modify existing peripheral
	fetchPeripheral(6, QUERY_TYPE_PUSH, ti);

	return(fetchPeripheral(7, QUERY_TYPE_PUSH, ti));
}

char *notePullPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Pull notes from requested peripheral
	return(fetchPeripheral(34, QUERY_TYPE_PULL, ti));
}

char *notePullPeripheralByID(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Pull note from requested peripheral by id
	return(fetchPeripheral(37, QUERY_TYPE_PULL, ti));
}

char *noteAddPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Add note to requested peripheral
	return(fetchPeripheral(33, QUERY_TYPE_PUSH, ti));
}

char *noteModifyPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Update note for requested peripheral
	return(fetchPeripheral(35, QUERY_TYPE_PUSH, ti));
}

char *noteDeletePeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete note for requested peripheral
	return(fetchPeripheral(36, QUERY_TYPE_PUSH, ti));
}

char *searchPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Search from peripherals
	return(fetchPeripheral(4, QUERY_TYPE_PULL, ti));
}

char *deletePeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Delete existing peripheral
	fetchPeripheral(8, QUERY_TYPE_PUSH, ti);

	return(fetchPeripheral(7, QUERY_TYPE_PUSH, ti));
}

char *restorePeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Restore disposed peripheral
	fetchPeripheral(9, QUERY_TYPE_PUSH, ti);

	return(fetchPeripheral(7, QUERY_TYPE_PUSH, ti));
}

char *attachPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral to requested machine
	return(fetchPeripheral(10, QUERY_TYPE_PUSH, ti));
}

char *attachDomainPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral to requested domain
	return(fetchPeripheral(16, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral globally
	return(fetchPeripheral(17, QUERY_TYPE_PUSH, ti));
}

char *attachPeripheralToDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral to requested device
	return(fetchPeripheral(20, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalPeripheralToDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral globally
	return(fetchPeripheral(21, QUERY_TYPE_PUSH, ti));
}

char *attachPeripheralToPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral to requested peripheral
	return(fetchPeripheral(26, QUERY_TYPE_PUSH, ti));
}

char *attachGlobalPeripheralToPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Attach peripheral globally
	return(fetchPeripheral(27, QUERY_TYPE_PUSH, ti));
}

char *removePeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral from requested machine
	return(fetchPeripheral(11, QUERY_TYPE_PUSH, ti));
}

char *removeDomainPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral to requested domain
	return(fetchPeripheral(18, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral globally
	return(fetchPeripheral(19, QUERY_TYPE_PUSH, ti));
}

char *removePeripheralFromDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral from requested device
	return(fetchPeripheral(24, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalPeripheralFromDevice(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral globally
	return(fetchPeripheral(25, QUERY_TYPE_PUSH, ti));
}

char *removePeripheralFromPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_PARAM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral from requested peripheral
	return(fetchPeripheral(30, QUERY_TYPE_PUSH, ti));
}

char *removeGlobalPeripheralFromPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		replyPrepare(ERROR_SLIGHT, ERROR_CLASS_GENERAL, ERROR_CODE_GENERAL_PARAMETERNEEDED, ERROR_MESS_GENERAL_PARAMETERNEEDED, ti);

		return(ti->dataBuffer);
	}

	// Remove peripheral globally
	return(fetchPeripheral(31, QUERY_TYPE_PUSH, ti));
}

char *attachedPeripheral(struct threadInfo * ti) {
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
		// Get peripherals attached in machine
		return(fetchPeripheral(12, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get machines attached in peripheral
		return(fetchPeripheral(13, QUERY_TYPE_PULL, ti));
	}
}

char *attachedPeripheralDevice(struct threadInfo * ti) {
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
		// Get peripherals attached in device
		return(fetchPeripheral(22, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get peripherals attached in peripheral
		return(fetchPeripheral(23, QUERY_TYPE_PULL, ti));
	}
}

char *attachedPeripheralPeripheral(struct threadInfo * ti) {
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
		// Get peripherals attached in peripheral
		return(fetchPeripheral(28, QUERY_TYPE_PULL, ti));
	}
	else {
		// Get peripherals attached in peripheral
		return(fetchPeripheral(29, QUERY_TYPE_PULL, ti));
	}
}

char *listDisposedPeripheral(struct threadInfo * ti) {
	if(ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer == NULL ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer[0] == 0 ||
	ti->handlerArrays[HANDLER_ARRAY_ITEM].size == 0) {
		// List all disposed peripherals
		return(fetchPeripheral(14, QUERY_TYPE_PULL, ti));
	}
	else {
		// List requested disposed peripherals by type
		return(fetchPeripheral(15, QUERY_TYPE_PULL, ti));
	}
}

char *fetchPeripheral(int getThis, int getType, struct threadInfo * ti) {
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
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_ID ",%s FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0' ORDER BY %s%c",
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
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_ID ",%s FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '0' AND " TABLECOL_PERIPHERAL_CATEGORY " = '%s' ORDER BY %s%c",
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
					"SELECT DISTINCT " TABLEKEY_PERIPHERAL_DATA " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 4:
				// Search from devices
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLEKEY_PERIPHERAL_SEARCH " FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_MODEL " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_CATEGORY " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_MANUFACTURER " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_SIZE " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_IPADDRESS " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_SERNUM " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_SECNUM " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_LOCATION " LIKE '%%%s%%' OR " TABLECOL_PERIPHERAL_MOSD " LIKE '%%%s%%' ORDER BY " TABLEORD_PERIPHERAL_NAME "%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 5:
				// Create new device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PERIPHERAL " (" TABLEKEY_PERIPHERAL_NEW ") VALUES('%s', '%s', '%s', '%s')%c",
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
					"UPDATE " TABLE_PERIPHERAL " SET %s = '%s' WHERE " TABLECOL_PERIPHERAL_ID " = '%s'%c",
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
					"UPDATE " TABLE_PERIPHERAL " SET " TABLECOL_PERIPHERAL_MODIFIED " = NOW(), " TABLECOL_PERIPHERAL_MODIFIER " = '%s' WHERE " TABLECOL_PERIPHERAL_ID " = '%s'%c",
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
					"UPDATE " TABLE_PERIPHERAL " SET " TABLECOL_PERIPHERAL_DISPOSED " = " TABLECOL_PERIPHERAL_DISPOSED " + 1 WHERE " TABLECOL_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 9:
				// Restore disposed device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_PERIPHERAL " SET " TABLECOL_PERIPHERAL_DISPOSED " = '0' WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '1' AND " TABLECOL_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 10:
				// Attach device to requested machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ", " TABLECOL_PERIPHERAL_MAP_MACHINE_ID ") VALUES('%s', '%s')%c",
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
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " = '%s'%c",
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
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 13:
				// Get machines attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 14:
				// List all disposed devices
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_ID ",%s FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '1' ORDER BY %s%c",
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
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_ID ",%s FROM " TABLE_PERIPHERAL " WHERE " TABLECOL_PERIPHERAL_DISPOSED " = '1' AND " TABLECOL_PERIPHERAL_CATEGORY " = '%s' ORDER BY %s%c",
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
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ", " TABLECOL_PERIPHERAL_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
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
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ", " TABLECOL_PERIPHERAL_MAP_MACHINE_ID ") (SELECT '%s', " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 18:
				// Remove device to requested domain
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
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
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 20:
				// Attach device to requested device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ", " TABLECOL_PERIPHERAL_MAP_DEVICES_ID ") VALUES('%s', '%s')%c",
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
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_DEVICES_ID ", " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ") (SELECT '%s', " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 22:
				// Get devices attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_DEVICES_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 23:
				// Get peripherals attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 24:
				// Remove device from requested device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_DEVICES_ID " = '%s'%c",
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
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_DEVICES_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " IN (SELECT " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 26:
				// Attach device to requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ", " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID ") VALUES('%s', '%s')%c",
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
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID ", " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ") (SELECT '%s', " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 28:
				// Get devices attached in peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 29:
				// Get peripherals attached in device
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT DISTINCT " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID " FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s'%c",
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 30:
				// Remove device from requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID " = '%s'%c",
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
					"DELETE FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_PERIPHERALS_ID " = '%s' AND " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID " IN (SELECT " TABLECOL_PERIPHERAL_ID " FROM " TABLE_PERIPHERAL ")%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 32:
				// Clone peripheral attachments for machine
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_PERIPHERAL_MAP " (" TABLECOL_PERIPHERAL_MAP_PERIPHERALS ") SELECT " TABLECOL_PERIPHERAL_MAP_PERIPHERAL_ID ",'%s','0','0' FROM " TABLE_PERIPHERAL_MAP " WHERE " TABLECOL_PERIPHERAL_MAP_MACHINE_ID " IN (SELECT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_NODE " = '%s' AND " TABLECOL_MACHINE_DOMAIN " = '%s' AND " TABLECOL_MACHINE_DISPOSED " = '0')%c",
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc3Buffer,
					0
				);

				break;
			case 33:
				// Add note to requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"INSERT INTO " TABLE_NOTES " (" TABLEKEY_NOTES_PERIPHERAL ") VALUES('%s', '%s', '%s')%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					0
				);

				break;
			case 34:
				// Pull notes from requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT " TABLEKEY_NOTES_DATA " FROM " TABLE_NOTES " WHERE " TABLECOL_NOTES_PERIPHERAL " = '%s' ORDER BY " TABLEORD_NOTES_CREATED "%c",
					ti->commandInfo.esc2Buffer,
					0
				);

				break;
			case 35:
				// Update note for requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"UPDATE " TABLE_NOTES " SET " TABLECOL_NOTES_MODIFIED " = NOW(), " TABLECOL_NOTES_MODIFIER " = '%s', " TABLECOL_NOTES_NOTE " = '%s' WHERE " TABLECOL_NOTES_ID " = '%s' AND " TABLECOL_NOTES_CREATOR " = '%s'%c",
					ti->commandInfo.esc1Buffer,
					ti->commandInfo.esc4Buffer,
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc1Buffer,
					0
				);

				break;
			case 36:
				// Delete note for requested peripheral
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"DELETE FROM " TABLE_NOTES " WHERE " TABLECOL_NOTES_ID " = '%s' AND " TABLECOL_NOTES_CREATOR " = '%s'%c",
					ti->commandInfo.esc2Buffer,
					ti->commandInfo.esc1Buffer,
					0
				);

				break;
			case 37:
				// Pull note from requested peripheral by id
				snprintf(
					ti->commandInfo.statBuffer,
					ti->commandInfo.s,
					"SELECT " TABLEKEY_NOTES_DATA " FROM " TABLE_NOTES " WHERE " TABLECOL_NOTES_PERIPHERAL " = '%s' AND " TABLECOL_NOTES_ID " = '%s'%c",
					ti->commandInfo.esc2Buffer,
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
						"Device \"%s\" modified by \"%s\" using command \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
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
						"Device \"%s\" created by \"%s\" using command \"%s\"%c",
						ti->handlerArrays[HANDLER_ARRAY_ITEM].buffer,
						ti->handlerArrays[HANDLER_ARRAY_UID].buffer,
						ti->handlerArrays[HANDLER_ARRAY_COMMAND].buffer,
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
