#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "declarations.h"
#include "processor.h"



char *cpuGetProcessor(struct paramInfo * pi) {
#if defined(__linux__) || (__NetBSD__)
	int i;
	unsigned long long j;

	char *newArg, *newBuffer;
	char newLine[DATA_BLOCK_SIZE];

	const char *newKeys[] = {
		CPU_PHYS_ID, CPU_CORES, CPU_SIBLINGS, CPU_MHZ, CPU_CACHE, CPU_MIPS,
		NULL
	};

	size_t newBuflen;

	FILE *newFile;

	struct cpuStore newStore;

	if((newFile = fopen(CPU_GENERAL, "r")) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");

		return(NULL);
	}

	j = 1;

	memset(&newStore, 0, sizeof(newStore));

	snprintf(newStore.cpus, sizeof(newStore.cpus), "%llu%c", j, 0);

	while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
		if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
			continue;
		}

		for(i = 0; ; i++) {
			if(newKeys[i] == NULL) {
				break;
			}

			if(strncasecmp(newKeys[i], newLine, strlen(newKeys[i])) == 0) {
				if((newArg = cpuParseArg(newLine)) == NULL) {
					continue;
				}

				if(strncasecmp(newKeys[i], CPU_PHYS_ID, strlen(newKeys[i])) == 0) {
					if((atoll(newArg) + 1) >= j) {
						j = atoll(newArg) + 1;
					}

					snprintf(newStore.cpus, sizeof(newStore.cpus), "%llu%c", j, 0);
				}
				else if(strncasecmp(newKeys[i], CPU_CORES, strlen(newKeys[i])) == 0) {
					cpuCopyArg(newArg, newStore.cores);
				}
				else if(strncasecmp(newKeys[i], CPU_SIBLINGS, strlen(newKeys[i])) == 0) {
					cpuCopyArg(newArg, newStore.siblings);
				}
				else if(strncasecmp(newKeys[i], CPU_MHZ, strlen(newKeys[i])) == 0) {
					cpuCopyArg(newArg, newStore.mhz);
				}
				else if(strncasecmp(newKeys[i], CPU_CACHE, strlen(newKeys[i])) == 0) {
					cpuCopyArg(newArg, newStore.cache);
				}
				else if(strncasecmp(newKeys[i], CPU_MIPS, strlen(newKeys[i])) == 0) {
					cpuCopyArg(newArg, newStore.mips);
				}

				break;
			}
		}
	}

	if(fclose(newFile) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
	}

	newBuflen = strlen(newStore.cpus) + strlen(newStore.cores) + strlen(newStore.siblings) + strlen(newStore.mhz) + strlen(newStore.cache) + strlen(newStore.mips) + 6;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for processor info buffer");

		return(NULL);
	}

	snprintf(newBuffer, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c", newStore.cpus, ITEM_SEPARATOR, newStore.cores, ITEM_SEPARATOR, newStore.siblings, ITEM_SEPARATOR, newStore.mhz, ITEM_SEPARATOR, newStore.cache, ITEM_SEPARATOR, newStore.mips, 0);

	return(newBuffer);
#endif
	return(NULL);
}

void cpuFreeProcessor(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *cpuParseArg(char *confKeyword) {
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

void cpuCopyArg(char *confArgument, char *confStore) {
	size_t i;

	i = strlen(confArgument);

	if(i > DATA_BLOCK_SIZE - 1) {
		i = DATA_BLOCK_SIZE - 1;
	}

	strncpy(confStore, confArgument, i);

	confStore[i] = 0;
}
