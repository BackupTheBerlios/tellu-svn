#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "declarations.h"
#include "memory.h"



char *memGetMemory(struct paramInfo * pi) {
#if defined(__linux__)
	int k;

	char *newBuffer;

	if((newBuffer = malloc(DATA_BLOCK_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for memory info buffer");

		return(NULL);
	}

	k = snprintf(newBuffer, DATA_BLOCK_SIZE, "%lld%c", memGetThis(MEM_RAM_TOTAL), ITEM_SEPARATOR);
	k += snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lld%c", memGetThis(MEM_RAM_AVAIL), ITEM_SEPARATOR);
	k += snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lld%c", memGetThis(MEM_SWAP_TOTAL), ITEM_SEPARATOR);
	k += snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lld%c", memGetThis(MEM_SWAP_AVAIL), ITEM_SEPARATOR);
	k += snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lld%c", memGetThis(MEM_BUFFERS), ITEM_SEPARATOR);
	k += snprintf(newBuffer + k, DATA_BLOCK_SIZE - k, "%lld%c", memGetThis(MEM_CACHED), 0);

	return(newBuffer);
#endif
	return(NULL);
}

void memFreeMemory(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

long long memGetThis(char *getThis) {
	long long r;

	char *newArg;
	char newLine[DATA_BLOCK_SIZE];

	FILE *newFile;

	r = 0;

	if((newFile = fopen(MEM_GENERAL, "r")) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
	}
	else {
		while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
			if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
				continue;
			}

			if(strncasecmp(getThis, newLine, strlen(getThis)) == 0) {
				if((newArg = memParseArg(newLine)) == NULL) {
					continue;
				}

				r = atoll(newArg);

				break;
			}
		}

		if(fclose(newFile) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
		}
	}

	return(r);
}

char *memParseArg(char *confKeyword) {
	char *endLine, *endSpace;

	if((endLine = strchr(confKeyword, ':')) == NULL) {
		return(NULL);
	}

	endLine++;

	if(endLine[strlen(endLine) - 2] == '\r') {
		endLine[strlen(endLine) - 2] = 0;
	}
	else {
		endLine[strlen(endLine) - 1] = 0;
	}

	while(*endLine == ' ' || *endLine == '\t') {
		endLine++;
	}

	while((endSpace = strrchr(endLine, ' ')) != NULL) {
		*endSpace = 0;
	}

	if(*endLine == '\r' || *endLine == '\n' || *endLine == 0 || *endLine == EOF || strlen(endLine) < 1) {
		return(NULL);
	}

	return(endLine);
}
