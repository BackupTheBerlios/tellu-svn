#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"
#include "hal.h"



char *halGetDevices(struct paramInfo * pi) {
	unsigned int i, j, k;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	struct halStore newStore;

	DWORD newLength, newIndex, newSubindex;
	HKEY newKey, newSub, newSubsub, newSubsubsub;
	FILETIME newTime;
	TCHAR newString[CONFIG_SPACE_SIZE];
	TCHAR newSubkey[CONFIG_SPACE_SIZE], newSubsubkey[CONFIG_SPACE_SIZE];
	TCHAR newSubstring[CONFIG_SPACE_SIZE], newSubsubstring[CONFIG_SPACE_SIZE];

	memset(&newStore, 0, sizeof(newStore));

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for device info buffer");

		return(NULL);
	}

	k = 0;
	newIndex = 0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Class", 0, KEY_ENUMERATE_SUB_KEYS, &newKey) == ERROR_SUCCESS) {
		for(i = 0; i < 10240; i++) {
			newLength = sizeof(newSubkey);

			if(RegEnumKeyEx(newKey, newIndex, (LPBYTE) &newSubkey, &newLength, NULL, NULL, NULL, &newTime) == ERROR_SUCCESS) {
				_snprintf(newSubstring, sizeof(newSubstring), "SYSTEM\\CurrentControlSet\\Control\\Class\\%s%c", newSubkey, 0);

				if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, newSubstring, 0, KEY_QUERY_VALUE, &newSub) == ERROR_SUCCESS) {
					newLength = sizeof(newString);

					memset(&newString, 0, sizeof(newString));

					if(RegQueryValueEx(newSub, "Class", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
						if(newString[0] != 0) {
							_snprintf(newStore.category, sizeof(newStore.category), "%s%c", newString, 0);

							newSubindex = 0;

							if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, newSubstring, 0, KEY_ENUMERATE_SUB_KEYS, &newSubsub) == ERROR_SUCCESS) {
								for(j = 0; j < 10240; j++) {
									newLength = sizeof(newSubsubkey);

									if(RegEnumKeyEx(newSubsub, newSubindex, (LPBYTE) &newSubsubkey, &newLength, NULL, NULL, NULL, &newTime) == ERROR_SUCCESS) {
										_snprintf(newSubsubstring, sizeof(newSubsubstring), "SYSTEM\\CurrentControlSet\\Control\\Class\\%s\\%s%c", newSubkey, newSubsubkey, 0);

										if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, newSubsubstring, 0, KEY_QUERY_VALUE, &newSubsubsub) == ERROR_SUCCESS) {
											newLength = sizeof(newString);

											memset(&newStore.capabilities, 0, sizeof(newStore.capabilities));
											memset(&newStore.product, 0, sizeof(newStore.product));
											memset(&newStore.vendor, 0, sizeof(newStore.vendor));

											if(RegQueryValueEx(newSubsubsub, "DriverDesc", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
												_snprintf(newStore.product, sizeof(newStore.product), "%s%c", newString, 0);

												newLength = sizeof(newString);

												if(RegQueryValueEx(newSubsubsub, "MatchingDeviceId", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
													_snprintf(newStore.capabilities, sizeof(newStore.capabilities), "%s%c", newString, 0);
												}

												newLength = sizeof(newString);

												if(RegQueryValueEx(newSubsubsub, "ProviderName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
													_snprintf(newStore.vendor, sizeof(newStore.vendor), " %s%c", newString, 0);
												}
											}

											RegCloseKey(newSubsubsub);

											newBufcur = strlen(newStore.category) + strlen(newStore.product) + strlen(newStore.subsystem) + strlen(newStore.capabilities) + strlen(newStore.vendor) + strlen(newStore.opt) + 64;

											if(newBuflen - newBuffil <= newBufcur) {
												newBuflen += DATA_BLOCK_SIZE;

												if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
													free(newBuffer);

													warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for device info buffer");

													return(NULL);
												}

												newBuffer = tmpBuffer;
											}

											k += _snprintf(newBuffer + k, newBuflen - k, "%s%c%s%c%s%c%s%c%s%c%s%c", newStore.category, ITEM_SEPARATOR, newStore.product, ITEM_SEPARATOR, newStore.subsystem, ITEM_SEPARATOR, newStore.capabilities, ITEM_SEPARATOR, newStore.vendor, ITEM_SEPARATOR, newStore.opt, ITEM_DELIMITER);

											newBuffil += newBufcur;
										}

										newSubindex++;
									}
									else {
										break;
									}
								}

								RegCloseKey(newSubsub);
							}
						}
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

void halFreeDevices(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
