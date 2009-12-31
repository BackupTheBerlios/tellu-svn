#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "declarations.h"
#include "defines.h"
#include "shm.h"



void shmInfo(void) {
	int i;

	char *confShm;
	char thisLine[CONFIG_SPACE_SIZE];
	char thatLine[CONFIG_SPACE_SIZE];

	FILE *shmFile;

	struct stat newStat;

	if((confShm = configFetch("shm_file", &i)) != NULL) {
		snprintf(thisLine, sizeof(thisLine), "%s%c", confShm, 0);
	}
	else {
		snprintf(thisLine, sizeof(thisLine), "%s%c", CONFIG_DEFAULT_SHM, 0);
	}

	if(stat(thisLine, &newStat) == 0) {
		if(newStat.st_size > 0 && newStat.st_size < sizeof(thisLine)) {
			if((shmFile = fopen(thisLine, "r")) != NULL) {
				memset(thatLine, 0, sizeof(thatLine));

				if(fread(thatLine, newStat.st_size, 1, shmFile) == 1) {
					shmId = atoi(thatLine);

					statBuffer = NULL;

					if((statBuffer = shmat(shmId, NULL, 0)) == (void *) -1 || statBuffer == NULL) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to attach to shared memory segment");

						return;
					}

					shmTell(statBuffer->telludEntrySize, statBuffer->telludWorkersAvailable, statBuffer->telludServerStarted, statBuffer->telludLastTask, statBuffer->telludTotalTasks, statBuffer->telludInfoTime, statBuffer->telludErrorTime, statBuffer->telludThreadTasks, statBuffer->telludInfoMessage, statBuffer->telludErrorMessage, "tellud");
					shmTell(statBuffer->telmondEntrySize, statBuffer->telmondWorkersAvailable, statBuffer->telmondServerStarted, statBuffer->telmondLastTask, statBuffer->telmondTotalTasks, statBuffer->telmondInfoTime, statBuffer->telmondErrorTime, statBuffer->telmondThreadTasks, statBuffer->telmondInfoMessage, statBuffer->telmondErrorMessage, "telmond");
					shmTell(statBuffer->telskindEntrySize, statBuffer->telskindWorkersAvailable, statBuffer->telskindServerStarted, statBuffer->telskindLastTask, statBuffer->telskindTotalTasks, statBuffer->telskindInfoTime, statBuffer->telskindErrorTime, statBuffer->telskindThreadTasks, statBuffer->telskindInfoMessage, statBuffer->telskindErrorMessage, "telskind");
				}

				if(fclose(shmFile) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close shared memory id file");
				}
			}
			else {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to open shared memory id file for reading");
			}
		}
		else {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to stat shared memory id file");
		}
	}
	else {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to stat shared memory id file");
	}
}

void shmTell(unsigned long long entrySize, unsigned long long workersAvailable, unsigned long long serverStarted, unsigned long long lastTask, unsigned long long totalTasks, unsigned long long infoTime, unsigned long long errorTime, unsigned long long *threadTasks, char *infoMess, char *errorMess, char *serverName) {
	int k;
	unsigned long long p, r;

	char dataBuffer[CONFIG_STRING_SIZE];
	char timeBuffer[CONFIG_SPACE_SIZE];

	struct tm *newTime;

	if(entrySize == sizeof(unsigned long long)) {
		// Server started

		k = 0;

		if(workersAvailable != 0) {
			newTime = localtime((time_t *) &serverStarted);

			strftime(timeBuffer, sizeof(timeBuffer), TIME_FORMAT, newTime);

			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%c* %s started at %s, with %llu workers%c%c",
				CONFIG_LINEFEED,
				serverName,
				timeBuffer,
				workersAvailable,
				CONFIG_LINEFEED, CONFIG_LINEFEED
			);
		}
		else {
			return;
		}

		// Connections served

		if(lastTask != 0) {
			newTime = localtime((time_t *) &lastTask);

			strftime(timeBuffer, sizeof(timeBuffer), TIME_FORMAT, newTime);

			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%llu connections served, last at %s%c",
				totalTasks,
				timeBuffer,
				CONFIG_LINEFEED
			);
		}
		else {
			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%llu connections served%c",
				totalTasks,
				CONFIG_LINEFEED
			);
		}

		// Workers

		r = 0;

		for(p = 0; p < workersAvailable; p++) {
			if(threadTasks[p] != 0) {
				k += snprintf(
					dataBuffer + k,
					sizeof(dataBuffer) - k,
					"worker %llu has served %llu agents in last hour%c",
					p,
					threadTasks[p],
					CONFIG_LINEFEED
				);

				r++;
			}
		}

		if(r == workersAvailable) {
			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"All workers busy"
			);
		}
		else if(r == 0) {
			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"All workers idling"
			);
		}
		else {
			p -= r;

			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%llu workers idling",
				p
			);
		}

		// Last info message

		if(infoMess[0] != 0) {
			newTime = localtime((time_t *) &infoTime);

			strftime(timeBuffer, sizeof(timeBuffer), TIME_FORMAT, newTime);

			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%cLast message at %s, '%s'",
				CONFIG_LINEFEED,
				timeBuffer,
				infoMess
			);
		}

		// Last error message

		if(errorMess[0] != 0) {
			newTime = localtime((time_t *) &errorTime);

			strftime(timeBuffer, sizeof(timeBuffer), TIME_FORMAT, newTime);

			k += snprintf(
				dataBuffer + k,
				sizeof(dataBuffer) - k,
				"%cLast error at %s, '%s'",
				CONFIG_LINEFEED,
				timeBuffer,
				errorMess
			);
		}

		dataBuffer[k] = 0;

		infoMessage(ERROR_NOERROR, dataBuffer);
	}
}
