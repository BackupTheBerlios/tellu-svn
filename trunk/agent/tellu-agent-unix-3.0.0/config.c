#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "config.h"



int config(char *configFile) {
	int i, j, k;

	char *newArgument;
	char newLine[CONFIG_SPACE_SIZE * 3];

	const char *newDirs[] = {
		CONFIG_DEFAULT_PATH_1, CONFIG_DEFAULT_PATH_2,
		NULL
	};

	FILE *newFile;

	for(j = 0; ; j++) {
		if(newDirs[j] == NULL) {
			break;
		}

		snprintf(newLine, sizeof(newLine), "%s/%s%c", newDirs[j], configFile, 0);

		if((newFile = fopen(newLine, "r")) != NULL) {
			k = 1;

			while(fgets(newLine, sizeof(newLine) - 1, newFile) != NULL) {
				if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#' || newLine[0] == '%' || newLine[0] == ';') {
					k++;

					continue;
				}

				for(i = 0; ; i++) {
					if(mainConfigs[i].confKeyword == NULL) {
						break;
					}

					if(strncasecmp(mainConfigs[i].confKeyword, newLine, strlen(mainConfigs[i].confKeyword)) == 0) {
						if((newArgument = configParse(newLine)) == NULL) {
							continue;
						}

						if(newArgument == (char *) -1) {
							fprintf(stderr, "Keyword %s at line %d requires an argument of type %d.\n", mainConfigs[i].confKeyword, k, mainConfigs[i].confArgType);

							continue;
						}

						switch(mainConfigs[i].confArgType) {
							case CONFIG_TYPE_BOOLEAN:
								if((configBoolean(newArgument, &mainConfigs[i].confArgInt)) != 0) {
									fprintf(stderr, "Keyword %s at line %d requires a boolean (yes/no/1/0) argument.\n", mainConfigs[i].confKeyword, k);

									continue;
								}

								break;
							case CONFIG_TYPE_INTEGER:
								if((configInteger(newArgument, &mainConfigs[i].confArgInt)) != 0) {
									fprintf(stderr, "Keyword %s at line %d requires a numeral (0-9) argument.\n", mainConfigs[i].confKeyword, k);

									continue;
								}

								break;
							case CONFIG_TYPE_STRING:
								configString(newArgument, mainConfigs[i].confArgStr);

								break;
							default:
								fprintf(stderr, "Unknown argument type %d for keyword %s at line %d.\n", mainConfigs[i].confArgType, mainConfigs[i].confKeyword, k);

								break;
						}
					}
				}

				k++;
			}

			if(fclose(newFile) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
			}

			return(0);
		}
	}

	return(-1);
}

int configBoolean(char *confArgument, int *confStore) {
	if((strncasecmp(confArgument, "yes", 3)) == 0) {
		*confStore = CONFIG_TYPE_BOOLEAN_YES;

		return(0);
	}
	else if((strncasecmp(confArgument, "no", 2)) == 0) {
		*confStore = CONFIG_TYPE_BOOLEAN_NO;

		return(0);
	}
	else if((strncasecmp(confArgument, "1", 1)) == 0) {
		*confStore = CONFIG_TYPE_BOOLEAN_YES;

		return(0);
	}
	else if((strncasecmp(confArgument, "0", 1)) == 0) {
		*confStore = CONFIG_TYPE_BOOLEAN_NO;

		return(0);
	}

	return(-1);
}

int configInteger(char *confArgument, int *confStore) {
	int i;

	for(i = 0; i < strlen(confArgument); i++) {
		if(confArgument[i] < 48 || confArgument[i] > 57) {
			return(-1);
		}
	}

	*confStore = atoi(confArgument);

	return(0);
}

int configString(char *confArgument, char *confStore) {
	size_t i;

	i = strlen(confArgument);

	if(i > CONFIG_SPACE_SIZE - 1) {
		i = CONFIG_SPACE_SIZE - 1;
	}

	strncpy(confStore, confArgument, i);

	confStore[i] = 0;

	return(0);
}

void *configFetch(char *confKeyword) {
	int i;

	for(i = 0; ; i++) {
		if(mainConfigs[i].confKeyword == NULL) {
			break;
		}

		if(strncasecmp(mainConfigs[i].confKeyword, confKeyword, strlen(mainConfigs[i].confKeyword)) == 0) {
			switch(mainConfigs[i].confArgType) {
				case CONFIG_TYPE_BOOLEAN:
					return(&mainConfigs[i].confArgInt);
				case CONFIG_TYPE_INTEGER:
					return(&mainConfigs[i].confArgInt);
				case CONFIG_TYPE_STRING:
					if(mainConfigs[i].confArgStr[0] == 0) {
						return(NULL);
					}

					return(mainConfigs[i].confArgStr);
				default:
					return(NULL);
			}
		}
	}

	return(NULL);
}

char *configParse(char *confKeyword) {
	char *endLine;

	if((endLine = strchr(confKeyword, '=')) == NULL) {
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

	if(*endLine == '\r' || *endLine == '\n' || *endLine == 0 || *endLine == EOF) {
		return((char *) -1);
	}

	return(endLine);
}

char *configParseAttr(char *confKeyword) {
	char *endLine;

	if((endLine = strchr(confKeyword, '=')) == NULL) {
		return(NULL);
	}

	endLine++;

	while(*endLine == ' ' || *endLine == '\t') {
		endLine++;
	}

	if(*endLine == '\r' || *endLine == '\n' || *endLine == 0 || *endLine == EOF) {
		return(NULL);
	}

	return(endLine);
}

char *configParseKeyword(char *confKeyword) {
	char *endLine;

	if((endLine = strchr(confKeyword, '=')) == NULL) {
		return(NULL);
	}

	*endLine = 0;

	return(confKeyword);
}
