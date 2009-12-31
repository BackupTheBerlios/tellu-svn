#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



char *machGetInfo(struct paramInfo * pi) {
	int k;

	char *newBuffer;

	if((newBuffer = malloc(DATA_BLOCK_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for machine info buffer");

		return(NULL);
	}

	k = _snprintf(newBuffer, DATA_BLOCK_SIZE, "%s%c", nodeFetchNode(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchDomain(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchSystem(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchRelease(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchDistribution(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchMachine(), 0);

	return(newBuffer);
}

void machFreeInfo(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
