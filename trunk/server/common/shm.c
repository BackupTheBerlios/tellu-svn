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



void shmCreate(int whoAmi, int thisMany) {
	int i;
	int shmNew;

	char *confShm;
	char thisLine[CONFIG_SPACE_SIZE];
	char thatLine[CONFIG_SPACE_SIZE];

	FILE *shmFile;

	struct stat newStat;

	shmNew = 0;

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

				if(fread(thatLine, newStat.st_size, 1, shmFile) < 1) {
					shmNew++;
				}
				else {
					shmId = atoi(thatLine);

					if((statBuffer = shmat(shmId, NULL, 0)) == (struct statEntry *) -1) {
						shmNew++;
					}
				}

				if(fclose(shmFile) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
				}
			}
			else {
				shmNew++;
			}
		}
		else {
			shmNew++;
		}
	}
	else {
		shmNew++;
	}

	if(shmNew != 0) {
		if((shmId = shmget(IPC_PRIVATE | IPC_EXCL, sizeof(struct statEntry), IPC_CREAT | 0777)) == -1) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to create new shared memory segment");
		}

		if((statBuffer = shmat(shmId, NULL, 0)) == (struct statEntry *) -1) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to attach to shared memory segment");

			if(shmctl(shmId, IPC_RMID, NULL) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to set shared memory segment's control bits");
			}

			if(shmdt(statBuffer) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to destroy shared memory segment");
			}
		}

		snprintf(thatLine, sizeof(thatLine), "%d%c", shmId, 0);

		if((shmFile = fopen(thisLine, "w+")) == NULL) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to create shared memory file");

			if(shmctl(shmId, IPC_RMID, NULL) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to set shared memory segment's control bits");
			}

			if(shmdt(statBuffer) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to destroy shared memory segment");
			}
		}

		if(fwrite(thatLine, strlen(thatLine), 1, shmFile) < 1) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to write to shared memory file");

			if(fclose(shmFile) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
			}

			if(shmctl(shmId, IPC_RMID, NULL) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to set shared memory segment's control bits");
			}

			if(shmdt(statBuffer) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to destroy shared memory segment");
			}
		}

		if(fclose(shmFile) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
		}
	}

	switch(whoAmi) {
		case DAEMON_TELLUD:
			statBuffer->telludEntrySize = sizeof(unsigned long long);
			statBuffer->telludWorkersAvailable = thisMany;
			statBuffer->telludServerStarted = (time_t) time(NULL);
			statBuffer->telludLastTask = 0;
			statBuffer->telludTotalTasks = 0;
			statBuffer->telludTotalServed = 0;
			statBuffer->telludMessageLength = sizeof(statBuffer->telludErrorMessage);
			statBuffer->telludInfoTime = 0;
			statBuffer->telludErrorTime = 0;
			statBuffer->telludInfoMessage[0] = 0;
			statBuffer->telludErrorMessage[0] = 0;

			for(i = 0; i < thisMany; i++) {
				statBuffer->telludThreadTasks[i] = 0;
			}

			break;
		case DAEMON_TELMOND:
			statBuffer->telmondEntrySize = sizeof(unsigned long long);
			statBuffer->telmondWorkersAvailable = thisMany;
			statBuffer->telmondServerStarted = (time_t) time(NULL);
			statBuffer->telmondLastTask = 0;
			statBuffer->telmondTotalTasks = 0;
			statBuffer->telmondTotalServed = 0;
			statBuffer->telmondMessageLength = sizeof(statBuffer->telmondErrorMessage);
			statBuffer->telmondInfoTime = 0;
			statBuffer->telmondErrorTime = 0;
			statBuffer->telmondInfoMessage[0] = 0;
			statBuffer->telmondErrorMessage[0] = 0;

			for(i = 0; i < thisMany; i++) {
				statBuffer->telmondThreadTasks[i] = 0;
			}

			break;
		case DAEMON_TELSKIND:
			statBuffer->telskindEntrySize = sizeof(unsigned long long);
			statBuffer->telskindWorkersAvailable = thisMany;
			statBuffer->telskindServerStarted = (time_t) time(NULL);
			statBuffer->telskindLastTask = 0;
			statBuffer->telskindTotalTasks = 0;
			statBuffer->telskindTotalServed = 0;
			statBuffer->telskindMessageLength = sizeof(statBuffer->telskindErrorMessage);
			statBuffer->telskindInfoTime = 0;
			statBuffer->telskindErrorTime = 0;
			statBuffer->telskindInfoMessage[0] = 0;
			statBuffer->telskindErrorMessage[0] = 0;

			for(i = 0; i < thisMany; i++) {
				statBuffer->telskindThreadTasks[i] = 0;
			}

			break;
		default:
			break;
	}
}

void shmRemove(int whoAmi) {
	switch(whoAmi) {
		case DAEMON_TELLUD:
			if(statBuffer->telludEntrySize == 0) {
				break;
			}

			if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
				statBuffer->telludErrorMessage[0] = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELMOND:
			if(statBuffer->telmondEntrySize == 0) {
				break;
			}

			if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
				statBuffer->telmondErrorMessage[0] = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELSKIND:
			if(statBuffer->telskindEntrySize == 0) {
				break;
			}

			if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
				statBuffer->telskindErrorMessage[0] = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		default:
			break;
	}

	if(shmctl(shmId, IPC_RMID, NULL) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to set shared memory segment's control bits");
	}

	if(shmdt(statBuffer) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to destroy shared memory segment");
	}
}

void shmUpdate(int thisWorker, int whoAmi) {
	switch(whoAmi) {
		case DAEMON_TELLUD:
			if(statBuffer->telludEntrySize == 0) {
				break;
			}

			if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
				statBuffer->telludTotalTasks++;
				statBuffer->telludTotalServed++;
				statBuffer->telludThreadTasks[thisWorker]++;

				statBuffer->telludLastTask = (time_t) time(NULL);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELMOND:
			if(statBuffer->telmondEntrySize == 0) {
				break;
			}

			if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
				statBuffer->telmondTotalTasks++;
				statBuffer->telmondTotalServed++;
				statBuffer->telmondThreadTasks[thisWorker]++;

				statBuffer->telmondLastTask = (time_t) time(NULL);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELSKIND:
			if(statBuffer->telskindEntrySize == 0) {
				break;
			}

			if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
				statBuffer->telskindTotalTasks++;
				statBuffer->telskindTotalServed++;
				statBuffer->telskindThreadTasks[thisWorker]++;

				statBuffer->telskindLastTask = (time_t) time(NULL);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		default:
			break;
	}
}

void shmUsage(int whoAmi) {
	int i, j, k;

	char dataBuffer[CONFIG_SPACE_SIZE];

	switch(whoAmi) {
		case DAEMON_TELLUD:
			if(statBuffer->telludEntrySize == 0) {
				break;
			}

			if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
				k = snprintf(dataBuffer, sizeof(dataBuffer), "%llu connections served, ", statBuffer->telludTotalTasks);

				j = 0;

				for(i = 0; i < statBuffer->telludWorkersAvailable; i++) {
					if(statBuffer->telludThreadTasks[i] != 0) {
						if(j == 0) {
							k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "worker ");
						}

						k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d/%llu, ", i, statBuffer->telludThreadTasks[i]);

						statBuffer->telludThreadTasks[i] = 0;

						j++;
					}
				}

				if(j == statBuffer->telludWorkersAvailable) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers busy");
				}
				else if(j == 0) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers idling");
				}
				else {
					i -= j;

					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d workers idling", i);
				}

				dataBuffer[k] = 0;

				logMessage(dataBuffer);
				histMessage(statBuffer->telludTotalServed);

				statBuffer->telludTotalServed = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELMOND:
			if(statBuffer->telmondEntrySize == 0) {
				break;
			}

			if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
				k = snprintf(dataBuffer, sizeof(dataBuffer), "%llu connections served, ", statBuffer->telmondTotalTasks);

				j = 0;

				for(i = 0; i < statBuffer->telmondWorkersAvailable; i++) {
					if(statBuffer->telmondThreadTasks[i] != 0) {
						if(j == 0) {
							k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "worker ");
						}

						k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d/%llu, ", i, statBuffer->telmondThreadTasks[i]);

						statBuffer->telmondThreadTasks[i] = 0;

						j++;
					}
				}

				if(j == statBuffer->telmondWorkersAvailable) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers busy");
				}
				else if(j == 0) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers idling");
				}
				else {
					i -= j;

					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d workers idling", i);
				}

				dataBuffer[k] = 0;

				logMessage(dataBuffer);
				histMessage(statBuffer->telmondTotalServed);

				statBuffer->telmondTotalServed = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELSKIND:
			if(statBuffer->telskindEntrySize == 0) {
				break;
			}

			if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
				k = snprintf(dataBuffer, sizeof(dataBuffer), "%llu connections served, ", statBuffer->telskindTotalTasks);

				j = 0;

				for(i = 0; i < statBuffer->telskindWorkersAvailable; i++) {
					if(statBuffer->telskindThreadTasks[i] != 0) {
						if(j == 0) {
							k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "worker ");
						}

						k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d/%llu, ", i, statBuffer->telskindThreadTasks[i]);

						statBuffer->telskindThreadTasks[i] = 0;

						j++;
					}
				}

				if(j == statBuffer->telskindWorkersAvailable) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers busy");
				}
				else if(j == 0) {
					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "all workers idling");
				}
				else {
					i -= j;

					k += snprintf(dataBuffer + k, sizeof(dataBuffer) - k, "%d workers idling", i);
				}

				dataBuffer[k] = 0;

				logMessage(dataBuffer);
				histMessage(statBuffer->telskindTotalServed);

				statBuffer->telskindTotalServed = 0;
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		default:
			break;
	}
}

void shmFetch(int thisWho, struct threadDaemonInfo * se) {
	se->workersAvailable = 0;
	se->serverStarted = 0;
	se->lastTask = 0;
	se->totalTasks = 0;
	se->infoTime = 0;
	se->errorTime = 0;

	memset(&se->infoMessage, 0, sizeof(se->infoMessage));
	memset(&se->errorMessage, 0, sizeof(se->errorMessage));

	switch(thisWho) {
		case DAEMON_TELLUD:
			if(statBuffer->telludEntrySize == 0) {
				break;
			}

			if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
				se->workersAvailable = statBuffer->telludWorkersAvailable;
				se->serverStarted = statBuffer->telludServerStarted;
				se->lastTask = statBuffer->telludLastTask;
				se->totalTasks = statBuffer->telludTotalTasks;
				se->infoTime = statBuffer->telludInfoTime;
				se->errorTime = statBuffer->telludErrorTime;

				strncpy(se->infoMessage, statBuffer->telludInfoMessage, statBuffer->telludMessageLength - 1);
				strncpy(se->errorMessage, statBuffer->telludErrorMessage, statBuffer->telludMessageLength - 1);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELMOND:
			if(statBuffer->telmondEntrySize == 0) {
				break;
			}

			if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
				se->workersAvailable = statBuffer->telmondWorkersAvailable;
				se->serverStarted = statBuffer->telmondServerStarted;
				se->lastTask = statBuffer->telmondLastTask;
				se->totalTasks = statBuffer->telmondTotalTasks;
				se->infoTime = statBuffer->telmondInfoTime;
				se->errorTime = statBuffer->telmondErrorTime;

				strncpy(se->infoMessage, statBuffer->telmondInfoMessage, statBuffer->telmondMessageLength - 1);
				strncpy(se->errorMessage, statBuffer->telmondErrorMessage, statBuffer->telmondMessageLength - 1);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		case DAEMON_TELSKIND:
			if(statBuffer->telskindEntrySize == 0) {
				break;
			}

			if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
				se->workersAvailable = statBuffer->telskindWorkersAvailable;
				se->serverStarted = statBuffer->telskindServerStarted;
				se->lastTask = statBuffer->telskindLastTask;
				se->totalTasks = statBuffer->telskindTotalTasks;
				se->infoTime = statBuffer->telskindInfoTime;
				se->errorTime = statBuffer->telskindErrorTime;

				strncpy(se->infoMessage, statBuffer->telskindInfoMessage, statBuffer->telskindMessageLength - 1);
				strncpy(se->errorMessage, statBuffer->telskindErrorMessage, statBuffer->telskindMessageLength - 1);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Internal and shared memory variable sizes does not match");
			}

			break;
		default:
			break;
	}
}

void shmInfoMessage(char *thisMessage, int whoAmi) {
	if(statBuffer != NULL) {
		switch(whoAmi) {
			case DAEMON_TELLUD:
				if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
					statBuffer->telludInfoTime = (time_t) time(NULL);

					strncpy(statBuffer->telludInfoMessage, thisMessage, statBuffer->telludMessageLength - 1);
				}

				break;
			case DAEMON_TELMOND:
				if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
					statBuffer->telmondInfoTime = (time_t) time(NULL);

					strncpy(statBuffer->telmondInfoMessage, thisMessage, statBuffer->telmondMessageLength - 1);
				}

				break;
			case DAEMON_TELSKIND:
				if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
					statBuffer->telskindInfoTime = (time_t) time(NULL);

					strncpy(statBuffer->telskindInfoMessage, thisMessage, statBuffer->telskindMessageLength - 1);
				}

				break;
			default:
				break;
		}
	}
}

void shmWarningMessage(char *thisMessage, int whoAmi) {
	if(statBuffer != NULL) {
		switch(whoAmi) {
			case DAEMON_TELLUD:
				if(statBuffer->telludEntrySize == sizeof(unsigned long long)) {
					statBuffer->telludErrorTime = (time_t) time(NULL);

					strncpy(statBuffer->telludErrorMessage, thisMessage, statBuffer->telludMessageLength - 1);
				}

				break;
			case DAEMON_TELMOND:
				if(statBuffer->telmondEntrySize == sizeof(unsigned long long)) {
					statBuffer->telmondErrorTime = (time_t) time(NULL);

					strncpy(statBuffer->telmondErrorMessage, thisMessage, statBuffer->telmondMessageLength - 1);
				}

				break;
			case DAEMON_TELSKIND:
				if(statBuffer->telskindEntrySize == sizeof(unsigned long long)) {
					statBuffer->telskindErrorTime = (time_t) time(NULL);

					strncpy(statBuffer->telskindErrorMessage, thisMessage, statBuffer->telskindMessageLength - 1);
				}

				break;
			default:
				break;
		}
	}
}
