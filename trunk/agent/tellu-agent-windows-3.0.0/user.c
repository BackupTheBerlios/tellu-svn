#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



char *userGetInfo(struct paramInfo * pi) {
	int k;

	char *newBuffer;

	if((newBuffer = malloc(DATA_BLOCK_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for user info buffer");

		return(NULL);
	}

	k = _snprintf(newBuffer, DATA_BLOCK_SIZE, "%s%c", nodeFetchUserLogin(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchUserGroup(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchUserName(), ITEM_SEPARATOR);
	k += _snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%s%c", nodeFetchUserHome(), 0);

	return(newBuffer);
}

void userFreeInfo(char *intBuffer) {
	if(intBuffer != NULL) {                                            
		free(intBuffer);                                           
	}                                                                  
}                                                                          
