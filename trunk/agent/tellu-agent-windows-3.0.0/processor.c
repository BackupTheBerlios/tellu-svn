#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"
#include "processor.h"



char *cpuGetProcessor(struct paramInfo * pi) {
	unsigned int k, l;

	char *newBuffer;

	size_t newBuflen;

	DWORD newLength, newOffset, newValue;
	FARPROC cpuInfo;
	HKEY newKey;
	HMODULE modKernel;
	PCACHE_DESCRIPTOR newCache;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION newPointer;
	SYSTEM_INFO newInfo;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION newCpu[1024];
	TCHAR newString[CONFIG_SPACE_SIZE];

	struct cpuStore newStore;

	memset(&newStore, 0, sizeof(newStore));

	GetSystemInfo(&newInfo);

	if(newInfo.dwNumberOfProcessors < 1) {
		newInfo.dwNumberOfProcessors = 1;
	}

	_snprintf(newStore.cpus, sizeof(newStore.cpus), "%lu%c", newInfo.dwNumberOfProcessors, 0);

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
		newLength = sizeof(newString);

		if(RegQueryValueEx(newKey, "~MHZ", NULL, NULL, (LPDWORD) &newValue, &newLength) == ERROR_SUCCESS) {
			_snprintf(newStore.mhz, sizeof(newStore.mhz), "%lu%c", newValue, 0);
		}

		RegCloseKey(newKey);
	}

	k = 0;
	l = 0;

	if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
		if((cpuInfo = GetProcAddress(modKernel, "GetLogicalProcessorInformation")) != NULL) {
			newLength = sizeof(newCpu);

			if((cpuInfo)(&newCpu, &newLength) == TRUE) {
				newOffset = 0;
				newPointer = newCpu;

				while(newOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= newLength) {
					switch(newPointer->Relationship) {
						case RelationCache:
							newCache = &newPointer->Cache;

							if(newCache->Level == 1 || newCache->Level == 2 || newCache->Level == 3) {
								l += newCache->Size;
							}

							break;
						case RelationProcessorCore:
							k++;

							break;
						default:
							break;
					}

					newOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
					newPointer++;
				}

				if(l > 0) {
					l /= 1000;
				}

				_snprintf(newStore.cores, sizeof(newStore.cores), "%lu%c", k, 0);
				_snprintf(newStore.cache, sizeof(newStore.cores), "%lu%c", l, 0);
			}
		}

		FreeLibrary(modKernel);
	}

	newBuflen = strlen(newStore.cpus) + strlen(newStore.cores) + strlen(newStore.siblings) + strlen(newStore.mhz) + strlen(newStore.cache) + strlen(newStore.mips) + 6;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for processor info buffer");

		return(NULL);
	}

	_snprintf(newBuffer, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c", newStore.cpus, ITEM_SEPARATOR, newStore.cores, ITEM_SEPARATOR, newStore.siblings, ITEM_SEPARATOR, newStore.mhz, ITEM_SEPARATOR, newStore.cache, ITEM_SEPARATOR, newStore.mips, 0);

	return(newBuffer);
}

void cpuFreeProcessor(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
