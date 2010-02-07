#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "declarations.h"
#include "software.h"



char *softGetInstalled(struct paramInfo * pi) {
	int i, l, r, o;
	unsigned long long p;

	char *newBuffer, *tmpBuffer;
	char *endLine, *thisLine;
	char newLine[DATA_BLOCK_SIZE];
	char newTemp[DATA_STRING_SIZE];

	const char *newBins[] = {
		PACK_DPKG_1, PACK_DPKG_2, PACK_RPM_1, PACK_RPM_2, PACK_PKG_1, PACK_PKG_2,
		NULL
	};

	unsigned int newTypes[] = {
		PACK_TYPE_DPKG, PACK_TYPE_DPKG, PACK_TYPE_RPM, PACK_TYPE_RPM, PACK_TYPE_PKG, PACK_TYPE_PKG
	};

	size_t t;
	size_t newBuflen, newBufcur, newBuffil;

	FILE *newFile;

	struct softStore newStore;
	struct stat newStat;

	snprintf(newTemp, sizeof(newTemp), PACK_TEMP "%u.tmp%c", (int) getpid(), 0);

	unlink(newTemp);

	newBuffer = NULL;

	for(i = 0; ; i++) {
		if(newBins[i] == NULL) {
			break;
		}

		snprintf(newLine, sizeof(newLine), "%s >%s%c", newBins[i], newTemp, 0);

		o = newTypes[i];
		r = system(newLine);

		if(WEXITSTATUS(r) == 0) {
			if(stat(newTemp, &newStat) == 0) {
				if(newStat.st_size > 0) {
					if((newFile = fopen(newTemp, "r")) == NULL) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");

						break;
					}

					newBuffil = 0;
					newBuflen = DATA_BLOCK_SIZE;

					if((newBuffer = malloc(newBuflen)) == NULL) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for installed software buffer");

						return(NULL);
					}

					l = 0;

					memset(&newStore, 0, sizeof(newStore));

					while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
						if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
							continue;
						}

						endLine = newLine;

						i = 0;

						while((endLine = strchr(endLine, '\t')) != NULL) {
							endLine++;
							i++;
						}

						if(i == PACK_TABS_LINE) {
							if(newStore.name[0] != 0) {
								newBufcur = strlen(newStore.name) + strlen(newStore.version) + strlen(newStore.size) + strlen(newStore.url) + CONFIG_SPACE_SIZE;

								if(newBuflen - newBuffil <= newBufcur) {
									newBuflen += DATA_BLOCK_SIZE * 20;

									if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
										free(newBuffer);

										warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for installed software buffer");

										return(NULL);
									}

									newBuffer = tmpBuffer;
								}

								l += snprintf(newBuffer + l, newBuflen, "%d%c%s%c%s%c%s%c%s%c", newStore.type, ITEM_SEPARATOR, newStore.name, ITEM_SEPARATOR, newStore.version, ITEM_SEPARATOR, newStore.size, ITEM_SEPARATOR, newStore.url, ITEM_DELIMITER);

								newBuffil += newBufcur;
							}

							memset(&newStore, 0, sizeof(newStore));

							newStore.type = o;

							t = 0;
							thisLine = newLine;

							while(*thisLine != '\t') {
								thisLine++;
								t++;
							}

							if(t > (sizeof(newStore.name) - 1)) {
								t = sizeof(newStore.name) - 1;
							}

							strncpy(newStore.name, newLine, t);

							endLine = strchr(newLine, '\t');
							endLine++;

							t = 0;
							thisLine = endLine;

							while(*thisLine != '\t') {
								thisLine++;
								t++;
							}

							if(t > (sizeof(newStore.version) - 1)) {
								t = sizeof(newStore.version) - 1;
							}

							strncpy(newStore.version, endLine, t);

							endLine = strchr(endLine, '\t');
							endLine++;

							t = 0;
							thisLine = endLine;

							while(*thisLine != '\t') {
								thisLine++;
								t++;
							}

							if(t > (sizeof(newStore.size) - 1)) {
								t = sizeof(newStore.size) - 1;
							}

							strncpy(newStore.size, endLine, t);

							// Convert rpm package size to kilobytes
							if(newStore.type == PACK_TYPE_RPM) {
								p = (unsigned long long) atoll(newStore.size);
								p /= 1000;

								snprintf(newStore.size, sizeof(newStore.size), "%llu%c", p, 0);
							}

							endLine = strchr(endLine, '\t');
							endLine++;

							t = 0;
							thisLine = endLine;

							while(*thisLine != '\n') {
								thisLine++;
								t++;
							}

							if(t > (sizeof(newStore.url) - 1)) {
								t = sizeof(newStore.url) - 1;
							}

							strncpy(newStore.url, endLine, t);
						}
					}

					if(newStore.name[0] != 0) {
						newBufcur = strlen(newStore.name) + strlen(newStore.version) + strlen(newStore.size) + strlen(newStore.url) + CONFIG_SPACE_SIZE;

						if(newBuflen - newBuffil <= newBufcur) {
							newBuflen += DATA_BLOCK_SIZE * 20;

							if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
								free(newBuffer);

								warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for installed software buffer");

								return(NULL);
							}

							newBuffer = tmpBuffer;
						}

						l += snprintf(newBuffer + l, newBuflen, "%d%c%s%c%s%c%s%c%s%c", newStore.type, ITEM_SEPARATOR, newStore.name, ITEM_SEPARATOR, newStore.version, ITEM_SEPARATOR, newStore.size, ITEM_SEPARATOR, newStore.url, ITEM_DELIMITER);

						newBuffil += newBufcur;
					}

					if(fclose(newFile) == -1) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
					}

					if(l > 0) {
						l--;
					}

					newBuffer[l] = 0;

					break;
				}
			}
		}

		unlink(newTemp);
	}

	unlink(newTemp);

	return(newBuffer);
}

void softFreeInstalled(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
