#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"
#include "software.h"



char *softGetInstalled(struct paramInfo * pi) {
	unsigned int i, k;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	struct softwareStore newStore;

	DWORD newLength, newValue, newIndex;
	HKEY newKey, newSub;
	FILETIME newTime;
	TCHAR newString[CONFIG_SPACE_SIZE], newSubkey[CONFIG_SPACE_SIZE], newSubstring[CONFIG_SPACE_SIZE];

	memset(&newStore, 0, sizeof(newStore));

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for software info buffer");

		return(NULL);
	}

	k = 0;
	newIndex = 0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_ENUMERATE_SUB_KEYS, &newKey) == ERROR_SUCCESS) {
		for(i = 0; i < 10240; i++) {
			newLength = sizeof(newSubkey);

			if(RegEnumKeyEx(newKey, newIndex, (LPBYTE) &newSubkey, &newLength, NULL, NULL, NULL, &newTime) == ERROR_SUCCESS) {
				_snprintf(newSubstring, sizeof(newSubstring), "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s%c", newSubkey, 0);

				if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, newSubstring, 0, KEY_QUERY_VALUE, &newSub) == ERROR_SUCCESS) {
					newLength = sizeof(newString);

					if(RegQueryValueEx(newSub, "DisplayName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
						_snprintf(newStore.name, sizeof(newStore.name), "%s%c", newString, 0);

						newLength = sizeof(newString);

						if(RegQueryValueEx(newSub, "DisplayVersion", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							_snprintf(newStore.version, sizeof(newStore.version), "%s%c", newString, 0);
						}

						newLength = sizeof(newValue);

						if(RegQueryValueEx(newSub, "Size", NULL, NULL, (LPDWORD) &newValue, &newLength) == ERROR_SUCCESS) {
							newValue /= 1000;

							_snprintf(newStore.size, sizeof(newStore.size), "%lu%c", newValue, 0);
						}

						newLength = sizeof(newString);

						if(RegQueryValueEx(newSub, "HelpLink", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							_snprintf(newStore.url, sizeof(newStore.url), "%s%c", newString, 0);
						}

						newBufcur = strlen(newStore.name) + strlen(newStore.version) + strlen(newStore.size) + strlen(newStore.url) + 64;

						if(newBuflen - newBuffil <= newBufcur) {
							newBuflen += DATA_BLOCK_SIZE;

							if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
								free(newBuffer);

								warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for software info buffer");

								return(NULL);
							}

							newBuffer = tmpBuffer;
						}

						k += _snprintf(newBuffer + k, newBuflen, "%d%c%s%c%s%c%s%c%s%c", PACK_TYPE_MSI, ITEM_SEPARATOR, newStore.name, ITEM_SEPARATOR, newStore.version, ITEM_SEPARATOR, newStore.size, ITEM_SEPARATOR, newStore.url, ITEM_DELIMITER);

						newBuffil += newBufcur;
 					}

					RegCloseKey(newSub);
				}

				newIndex++;
 			}
			else {
				break;
			}
		}

		RegCloseKey(newKey);
	}

	if(k > 0) {
		k--;
	}

	newBuffer[k] = 0;

	return(newBuffer);
}

void softFreeInstalled(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
