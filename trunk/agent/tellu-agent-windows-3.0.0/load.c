#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



char *loadGetLoad(struct paramInfo * pi) {
	unsigned int k;

	char *newBuffer;

	DWORD newTick;
	FARPROC idleTime, tickCount;
	HMODULE modKernel;
	ULONGLONG newPick;

	if((newBuffer = malloc(DATA_STRING_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for load info buffer");

		return(NULL);
	}

	newPick = 0;

	k = _snprintf(newBuffer, DATA_STRING_SIZE, "0%c0%c0%c", ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR);

	if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
		if((tickCount = GetProcAddress(modKernel, "GetTickCount64")) != NULL) {
			newPick = (tickCount)();
			newPick /= 1000;

			k += _snprintf(newBuffer + k, DATA_STRING_SIZE - k, "%llu%c", newPick, ITEM_SEPARATOR);
		}

		FreeLibrary(modKernel);
	}

	if(newPick == 0) {
		newTick = GetTickCount();
		newTick /= 1000;

		k += _snprintf(newBuffer + k, DATA_STRING_SIZE - k, "%lu%c", newTick, ITEM_SEPARATOR);
	}

	newPick = 0;

	if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
		if((idleTime = GetProcAddress(modKernel, "QueryUnbiasedInterruptTime")) != NULL) {
			if((idleTime)(&newPick) != 0) {
				newPick /= 10000000;

				k += _snprintf(newBuffer + k, DATA_STRING_SIZE - k, "%llu%c", newPick, 0);
			}
		}

		FreeLibrary(modKernel);
	}

	if(newPick == 0) {
		k += _snprintf(newBuffer + k, DATA_STRING_SIZE - k, "0%c", 0);
	}

	return(newBuffer);
}

void loadFreeLoad(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
