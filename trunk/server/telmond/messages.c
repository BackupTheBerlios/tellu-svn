#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include "declarations.h"
#include "defines.h"



void infoMessage(int fatalError, char *infoMessage) {
	int i;
	int *infoBool;

	char newString[CONFIG_STRING_SIZE];

	if(infoMessage != NULL) {
		snprintf(newString, sizeof(newString), "%s.%c", infoMessage, 0);
	}
	else {
		return;
	}

	if((infoBool = configFetch("info_stdout", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stdout, "%s%c%c", newString, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("info_stderr", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stderr, "%s%c%c", newString, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("info_syslog", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(fatalError == ERROR_FATAL) {
				syslog(LOG_ERR, "%s%c", newString, 0);
			}
			else {
				syslog(LOG_INFO, "%s%c", newString, 0);
			}
		}
	}

	shmInfoMessage(newString, DAEMON_TELMOND);

	if(fatalError == ERROR_FATAL) {
		exitProcess(errno);
	}
}

void infoThread(int fatalError, char *infoMessage, char *infoSpace, int infoSize, int *infoBool, int *i) {
	if(infoMessage != NULL) {
		snprintf(infoSpace, infoSize, "%s.%c", infoMessage, 0);
	}
	else {
		return;
	}

	if((infoBool = configFetch("info_stdout", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stdout, "%s%c%c", infoSpace, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("info_stderr", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stderr, "%s%c%c", infoSpace, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("info_syslog", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(fatalError == ERROR_FATAL) {
				syslog(LOG_ERR, "%s%c", infoSpace, 0);
			}
			else {
				syslog(LOG_INFO, "%s%c", infoSpace, 0);
			}
		}
	}

	shmInfoMessage(infoSpace, DAEMON_TELMOND);

	if(fatalError == ERROR_FATAL) {
		exitProcess(errno);
	}
}

void warningMessage(int fatalError, char *warningMessage) {
	int i;
	int *infoBool;

	char newString[CONFIG_STRING_SIZE];

	if(errno == 0) {
		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s.%c", warningMessage, 0);
		}
		else {
			return;
		}
	}
	else {
		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s: %s%c", warningMessage, strerror(errno), 0);
		}
		else {
			snprintf(newString, sizeof(newString), "%s%c", strerror(errno), 0);
		}
	}

	if((infoBool = configFetch("warn_stdout", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stdout, "%s%c%c", newString, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("warn_stderr", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stderr, "%s%c%c", newString, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("warn_syslog", &i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(fatalError == ERROR_FATAL) {
				syslog(LOG_ERR, "%s%c", newString, 0);
			}
			else {
				syslog(LOG_WARNING, "%s%c", newString, 0);
			}
		}
	}

	shmWarningMessage(newString, DAEMON_TELMOND);

	if(fatalError == ERROR_FATAL) {
		exitProcess(errno);
	}
}

void warningThread(int fatalError, char *warningMessage, char *warningSpace, int warningSize, int *infoBool, int *i) {
	if(errno == 0) {
		if(warningMessage != NULL) {
			snprintf(warningSpace, warningSize, "%s.%c", warningMessage, 0);
		}
		else {
			return;
		}
	}
	else {
		if(warningMessage != NULL) {
			snprintf(warningSpace, warningSize, "%s: %s%c", warningMessage, strerror(errno), 0);
		}
		else {
			snprintf(warningSpace, warningSize, "%s%c", strerror(errno), 0);
		}
	}

	if((infoBool = configFetch("warn_stdout", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stdout, "%s%c%c", warningSpace, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("warn_stderr", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			fprintf(stderr, "%s%c%c", warningSpace, CONFIG_LINEFEED, 0);
		}
	}

	if((infoBool = configFetch("warn_syslog", i)) != NULL) {
		if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
			if(fatalError == ERROR_FATAL) {
				syslog(LOG_ERR, "%s%c", warningSpace, 0);
			}
			else {
				syslog(LOG_WARNING, "%s%c", warningSpace, 0);
			}
		}
	}

	shmWarningMessage(warningSpace, DAEMON_TELMOND);

	if(fatalError == ERROR_FATAL) {
		exitProcess(errno);
	}
}

void logMessage(char *logMessage) {
	char *thisHost, *thisDomain, *thisSystem, *thisRelease, *thisLogin, *thisGroup;
	char thisBuffer[CONFIG_STRING_SIZE];

	struct threadStorageInfo storageInfo;
	extern struct threadInfo *pMainThreadInfo;

	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	void (*dbEscape)(struct threadStorageInfo *, char *, char *);
	void (*dbPush)(struct threadStorageInfo *, char *);
	char *(*dbPull)(struct threadStorageInfo *, char *);
	void (*dbFree)(struct threadStorageInfo *);

	memset(&storageInfo, 0, sizeof(storageInfo));

	dbConnect = pMainThreadInfo->dbInfo.connect;
	dbDisconnect = pMainThreadInfo->dbInfo.disconnect;
	dbEscape = pMainThreadInfo->dbInfo.escape;
	dbPush = pMainThreadInfo->dbInfo.push;
	dbPull = pMainThreadInfo->dbInfo.pull;
	dbFree = pMainThreadInfo->dbInfo.free;

	if((thisHost = nodeFetchNode()) == NULL) {
		thisHost = "";
	}

	if((thisDomain = nodeFetchDomain()) == NULL) {
		thisDomain = "";
	}

	if((thisSystem = nodeFetchSystem()) == NULL) {
		thisSystem = "";
	}

	if((thisRelease = nodeFetchRelease()) == NULL) {
		thisRelease = "";
	}

	if((thisLogin = nodeFetchUserLogin()) == NULL) {
		thisLogin = "";
	}

	if((thisGroup = nodeFetchUserGroup()) == NULL) {
		thisGroup = "";
	}

	snprintf(
		thisBuffer,
		sizeof(thisBuffer),
		"%s%c",
		logMessage,
		0
	);

	shmInfoMessage(thisBuffer, DAEMON_TELMOND);

	if(dbConnect(&storageInfo) == 0) {
		snprintf(
			thisBuffer,
			sizeof(thisBuffer),
			"INSERT INTO " TABLE_LOG " (" TABLECOL_LOG ") VALUES('%d','%s','%s','%s','%s','%s','%s','%s','%s','%s')%c",
			ERROR_NOERROR,
			thisHost,
			thisDomain,
			thisSystem,
			thisRelease,
			thisLogin,
			thisGroup,
			APPLICATION_NAME,
			APPLICATION_VERSION,
			logMessage,
			0
		);

		dbPush(&storageInfo, thisBuffer);

		snprintf(
			thisBuffer,
			sizeof(thisBuffer),
			"DELETE FROM " TABLE_LOG " WHERE " TABLECOL_LOG_PROC " = '" APPLICATION_NAME "' AND UNIX_TIMESTAMP(" TABLECOL_LOG_TIME ") < UNIX_TIMESTAMP() - " TIMER_RESOLUTION_STATUS_FLUSH "%c",
			0
		);

		dbPush(&storageInfo, thisBuffer);
		dbDisconnect(&storageInfo);
	}
}

void histMessage(unsigned long long totalServed) {
	char *thisHost, *thisDomain, *thisSystem, *thisRelease, *thisLogin, *thisGroup;
	char thisBuffer[CONFIG_STRING_SIZE];

	struct threadStorageInfo storageInfo;
	extern struct threadInfo *pMainThreadInfo;

	int (*dbConnect)(struct threadStorageInfo *);
	void (*dbDisconnect)(struct threadStorageInfo *);
	void (*dbEscape)(struct threadStorageInfo *, char *, char *);
	void (*dbPush)(struct threadStorageInfo *, char *);
	char *(*dbPull)(struct threadStorageInfo *, char *);
	void (*dbFree)(struct threadStorageInfo *);

	memset(&storageInfo, 0, sizeof(storageInfo));

	dbConnect = pMainThreadInfo->dbInfo.connect;
	dbDisconnect = pMainThreadInfo->dbInfo.disconnect;
	dbEscape = pMainThreadInfo->dbInfo.escape;
	dbPush = pMainThreadInfo->dbInfo.push;
	dbPull = pMainThreadInfo->dbInfo.pull;
	dbFree = pMainThreadInfo->dbInfo.free;

	if((thisHost = nodeFetchNode()) == NULL) {
		thisHost = "";
	}

	if((thisDomain = nodeFetchDomain()) == NULL) {
		thisDomain = "";
	}

	if((thisSystem = nodeFetchSystem()) == NULL) {
		thisSystem = "";
	}

	if((thisRelease = nodeFetchRelease()) == NULL) {
		thisRelease = "";
	}

	if((thisLogin = nodeFetchUserLogin()) == NULL) {
		thisLogin = "";
	}

	if((thisGroup = nodeFetchUserGroup()) == NULL) {
		thisGroup = "";
	}

	if(dbConnect(&storageInfo) == 0) {
		snprintf(
			thisBuffer,
			sizeof(thisBuffer),
			"INSERT INTO " TABLE_HIST " (" TABLECOL_HIST ") VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%llu')%c",
			thisHost,
			thisDomain,
			thisSystem,
			thisRelease,
			thisLogin,
			thisGroup,
			APPLICATION_NAME,
			APPLICATION_VERSION,
			totalServed,
			0
		);

		dbPush(&storageInfo, thisBuffer);

		snprintf(
			thisBuffer,
			sizeof(thisBuffer),
			"DELETE FROM " TABLE_HIST " WHERE " TABLECOL_HIST_PROC " = '" APPLICATION_NAME "' AND UNIX_TIMESTAMP(" TABLECOL_HIST_TIME ") < UNIX_TIMESTAMP() - " TIMER_RESOLUTION_STATUS_FLUSH "%c",
			0
		);

		dbPush(&storageInfo, thisBuffer);
		dbDisconnect(&storageInfo);
	}
}
