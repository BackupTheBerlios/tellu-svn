#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "declarations.h"
#include "defines.h"



void pidCreate(void) {
	int i;
	int *confPort;

	char *confPid;
	char thisLine[CONFIG_SPACE_SIZE];
	char thatLine[CONFIG_SPACE_SIZE];

	pid_t newPid;

	FILE *pidFile;

	struct stat newStat;

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		if((confPid = configFetch("pid_file", &i)) != NULL) {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", confPid, *confPort, 0);
		}
		else {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", CONFIG_DEFAULT_PID, *confPort, 0);
		}
	}
	else {
		if((confPid = configFetch("pid_file", &i)) != NULL) {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", confPid, CONFIG_DEFAULT_PORT, 0);
		}
		else {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", CONFIG_DEFAULT_PID, CONFIG_DEFAULT_PORT, 0);
		}
	}

	if(stat(thisLine, &newStat) == 0) {
		if(newStat.st_size > 0 && newStat.st_size < sizeof(thisLine)) {
			if((pidFile = fopen(thisLine, "r")) != NULL) {
				memset(thatLine, 0, sizeof(thatLine));

				if(fread(thatLine, newStat.st_size, 1, pidFile) < 1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to read from file");
				}
				else {
					newPid = atoi(thatLine);

					if(newPid > 1) {
						if(kill(newPid, 0) == 0) {
							if(fclose(pidFile) == -1) {
								warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
							}

							warningMessage(ERROR_FATAL, "Process listening same port already exists");
						}
					}
				}

				if(fclose(pidFile) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
				}
			}
		}
	}

	if((pidFile = fopen(thisLine, "w+")) == NULL) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to create process id file");
	}

	snprintf(thatLine, sizeof(thatLine), "%u%c", getpid(), 0);

	if(fwrite(thatLine, strlen(thatLine), 1, pidFile) < 1) {
		if(fclose(pidFile) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
		}

		warningMessage(ERROR_FATAL, "Error occurred while trying to write to process id file");
	}

	if(fclose(pidFile) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
	}
}

void pidRemove(void) {
	int i;
	int *confPort;

	char *confPid;
	char thisLine[CONFIG_SPACE_SIZE];

	struct stat newStat;

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		if((confPid = configFetch("pid_file", &i)) != NULL) {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", confPid, *confPort, 0);
		}
		else {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", CONFIG_DEFAULT_PID, *confPort, 0);
		}
	}
	else {
		if((confPid = configFetch("pid_file", &i)) != NULL) {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", confPid, CONFIG_DEFAULT_PORT, 0);
		}
		else {
			snprintf(thisLine, sizeof(thisLine), "%s.%d%c", CONFIG_DEFAULT_PID, CONFIG_DEFAULT_PORT, 0);
		}
	}

	if(stat(thisLine, &newStat) == 0) {
		if(unlink(thisLine) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to remove file");
		}
	}
}
