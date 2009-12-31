#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"
#include "system.h"



char *sysGetSystem(struct paramInfo * pi) {
	char *newBuffer;

	size_t newBuflen;

	DWORD newLength;
	HKEY newKey;
	TCHAR newString[CONFIG_SPACE_SIZE];

	struct sysStore newStore;

	memset(&newStore, 0, sizeof(newStore));

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\Description\\System\\BIOS", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "BaseBoardManufacturer", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.bbmanufacturer, sizeof(newStore.bbmanufacturer), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "BaseBoardProduct", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.bbproduct, sizeof(newStore.bbproduct), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "BaseBoardVersion", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.bbversion, sizeof(newStore.bbversion), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "SystemFamily", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.sysfamily, sizeof(newStore.sysfamily), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "SystemManufacturer", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.sysmanufacturer, sizeof(newStore.sysmanufacturer), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "SystemProductName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.sysproduct, sizeof(newStore.sysproduct), "%s%c", newString, 0);
		}

		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "SystemVersion", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.sysversion, sizeof(newStore.sysversion), "%s%c", newString, 0);
		}

		RegCloseKey(newKey);
	}

	newBuflen = strlen(newStore.bbmanufacturer) + strlen(newStore.bbproduct) + strlen(newStore.bbversion) + strlen(newStore.sysfamily) + strlen(newStore.sysmanufacturer) + strlen(newStore.sysproduct) + strlen(newStore.sysversion) + 7;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for system info buffer");

		return(NULL);
	}

	_snprintf(newBuffer, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c%s%c", newStore.bbmanufacturer, ITEM_SEPARATOR, newStore.bbproduct, ITEM_SEPARATOR, newStore.bbversion, ITEM_SEPARATOR, newStore.sysfamily, ITEM_SEPARATOR, newStore.sysmanufacturer, ITEM_SEPARATOR, newStore.sysproduct, ITEM_SEPARATOR, newStore.sysversion, 0);

	return(newBuffer);
}

void sysFreeSystem(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
