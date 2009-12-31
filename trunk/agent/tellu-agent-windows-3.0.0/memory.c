#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>

#include "declarations.h"
#include "defines.h"



char *memGetMemory(struct paramInfo * pi) {
	unsigned int k;

	char *newBuffer;

	FARPROC globalMemoryStatus, memInfo;
	HMODULE modKernel, modPsapi;
	MEMORYSTATUS newStatus;
	MEMORYSTATUSEX newStatusEx;
	PERFORMANCE_INFORMATION newPerf;
	SIZE_T newCache;

	if((newBuffer = malloc(DATA_BLOCK_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for memory info buffer");

		return(NULL);
	}

	modPsapi = NULL;
	memInfo = NULL;

	if((modPsapi = LoadLibrary("psapi.dll")) != NULL) {
		if((memInfo = GetProcAddress(modPsapi, "GetPerformanceInfo")) == NULL) {
			memInfo = GetProcAddress(modPsapi, "K32GetPerformanceInfo");
		}

		if(memInfo == NULL) {
			FreeLibrary(modPsapi);

			if((modPsapi = LoadLibrary("kernel32.dll")) != NULL) {
				if((memInfo = GetProcAddress(modPsapi, "GetPerformanceInfo")) == NULL) {
					memInfo = GetProcAddress(modPsapi, "K32GetPerformanceInfo");
				}
			}
		}
	}
	else {
		if((modPsapi = LoadLibrary("kernel32.dll")) != NULL) {
			if((memInfo = GetProcAddress(modPsapi, "GetPerformanceInfo")) == NULL) {
				memInfo = GetProcAddress(modPsapi, "K32GetPerformanceInfo");
			}
		}
	}

	memset(newBuffer, 0, DATA_BLOCK_SIZE);

	newCache = 0;

	if(memInfo != NULL) {
		if((memInfo)(&newPerf, sizeof(newPerf)) == TRUE) {
			newCache = newPerf.SystemCache * newPerf.PageSize;
			newCache /= 1000;
		}
	}

	if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
		if((globalMemoryStatus = GetProcAddress(modKernel, "GlobalMemoryStatusEx")) != NULL) {
			newStatusEx.dwLength = sizeof(newStatusEx);

			if((globalMemoryStatus)(&newStatusEx) != 0) {
				newStatusEx.ullTotalPhys /= 1000;
				newStatusEx.ullAvailPhys /= 1000;
				newStatusEx.ullTotalPageFile /= 1000;
				newStatusEx.ullAvailPageFile /= 1000;

				k = _snprintf(newBuffer, DATA_BLOCK_SIZE, "%llu%c", newStatusEx.ullTotalPhys, ITEM_SEPARATOR);
				k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%llu%c", newStatusEx.ullAvailPhys, ITEM_SEPARATOR);
				k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%llu%c", newStatusEx.ullTotalPageFile, ITEM_SEPARATOR);
				k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%llu%c", newStatusEx.ullAvailPageFile, ITEM_SEPARATOR);
				k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "0%c", ITEM_SEPARATOR);
				k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%llu%c", newCache, 0);
			}
		}

		FreeLibrary(modKernel);
	}

	if(newBuffer[0] == 0) {
		GlobalMemoryStatus(&newStatus);

		newStatus.dwTotalPhys /= 1000;
		newStatus.dwAvailPhys /= 1000;
		newStatus.dwTotalPageFile /= 1000;
		newStatus.dwAvailPageFile /= 1000;

		k = _snprintf(newBuffer, DATA_BLOCK_SIZE, "%lu%c", newStatus.dwTotalPhys, ITEM_SEPARATOR);
		k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lu%c", newStatus.dwAvailPhys, ITEM_SEPARATOR);
		k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lu%c", newStatus.dwTotalPageFile, ITEM_SEPARATOR);
		k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lu%c", newStatus.dwAvailPageFile, ITEM_SEPARATOR);
		k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "0%c", ITEM_SEPARATOR);
		k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%llu%c", newCache, 0);
	}

	if(modPsapi != NULL) {
		FreeLibrary(modPsapi);
	}

	return(newBuffer);
}

void memFreeMemory(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
