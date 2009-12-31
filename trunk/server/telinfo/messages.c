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

	if(fatalError == ERROR_FATAL) {
		exit(errno);
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

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}
