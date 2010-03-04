#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "declarations.h"
#include "load.h"



char *loadGetLoad(struct paramInfo * pi) {
#if defined(__linux__) || (__NetBSD__)
	int i;

	char *newBuffer;
	char *endLine, *thisLine;
	char newLine[DATA_BLOCK_SIZE];

	const char *newKeys[] = {
		LOAD_AVERAGE, LOAD_UPTIME,
		NULL
	};

	size_t t;
	size_t newBuflen;

	FILE *newFile;

	struct loadStore newStore;

	memset(&newStore, 0, sizeof(newStore));

	for(i = 0; ; i++) {
		if(newKeys[i] == NULL) {
			break;
		}

		if((newFile = fopen(newKeys[i], "r")) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
		}
		else {
			while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
				if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
					continue;
				}

				if(strncasecmp(newKeys[i], LOAD_AVERAGE, strlen(newKeys[i])) == 0) {
					t = 0;
					thisLine = newLine;

					while(*thisLine != ' ' && *thisLine != '\t') {
						thisLine++;
						t++;
					}

					if(t > (sizeof(newStore.load1) - 1)) {
						t = sizeof(newStore.load1) - 1;
					}

					strncpy(newStore.load1, newLine, t);

					endLine = strchr(newLine, ' ');
					endLine++;

					t = 0;
					thisLine = endLine;

					while(*thisLine != ' ' && *thisLine != '\t') {
						thisLine++;
						t++;
					}

					if(t > (sizeof(newStore.load2) - 1)) {
						t = sizeof(newStore.load2) - 1;
					}

					strncpy(newStore.load2, endLine, t);

					endLine = strchr(endLine, ' ');
					endLine++;

					t = 0;
					thisLine = endLine;

					while(*thisLine != ' ' && *thisLine != '\t' && *thisLine != 10 && *thisLine != 0) {
						thisLine++;
						t++;
					}

					if(t > (sizeof(newStore.load3) - 1)) {
						t = sizeof(newStore.load3) - 1;
					}

					strncpy(newStore.load3, endLine, t);
				}
				else if(strncasecmp(newKeys[i], LOAD_UPTIME, strlen(newKeys[i])) == 0) {
					t = 0;
					thisLine = newLine;

					while(*thisLine != ' ' && *thisLine != '\t') {
						thisLine++;
						t++;
					}

					if(t > (sizeof(newStore.uptime1) - 1)) {
						t = sizeof(newStore.uptime1) - 1;
					}

					strncpy(newStore.uptime1, newLine, t);

					endLine = strchr(newLine, ' ');
					endLine++;

					t = 0;
					thisLine = endLine;

					while(*thisLine != ' ' && *thisLine != '\t' && *thisLine != 10 && *thisLine != 0) {
						thisLine++;
						t++;
					}

					if(t > (sizeof(newStore.uptime2) - 1)) {
						t = sizeof(newStore.uptime2) - 1;
					}

					strncpy(newStore.uptime2, endLine, t);
				}

				break;
			}

			if(fclose(newFile) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
			}
		}
	}

	newBuflen = strlen(newStore.load1) + strlen(newStore.load2) + strlen(newStore.load3) + strlen(newStore.uptime1) + strlen(newStore.uptime2) + 5;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for load average buffer");

		return(NULL);
	}

	snprintf(newBuffer, newBuflen, "%s%c%s%c%s%c%s%c%s%c", newStore.load1, ITEM_SEPARATOR, newStore.load2, ITEM_SEPARATOR, newStore.load3, ITEM_SEPARATOR, newStore.uptime1, ITEM_SEPARATOR, newStore.uptime2, 0);

	return(newBuffer);
#endif
	return(NULL);
}

void loadFreeLoad(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
