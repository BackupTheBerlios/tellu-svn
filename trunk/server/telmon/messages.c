#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <time.h>

#include "declarations.h"
#include "defines.h"



void infoMessage(int fatalError, char *infoMessage, struct mainInfo * mi) {
	int i;
	int *infoBool;

	char newSpace[CONFIG_STRING_SIZE];
	char newString[CONFIG_STRING_SIZE];

	Arg infoArgs[CONFIG_ARG_COUNT];
	Widget tempWidget;
	XmString thisString;

	time_t timeAnd;

	struct tm *timeNow;

	timeAnd = time(NULL);
	timeNow = localtime((time_t *) &timeAnd);

	strftime(newSpace, sizeof(newSpace), TIME_FORMAT, timeNow);

	if(infoMessage != NULL) {
		snprintf(newString, sizeof(newString), "%s%c%c%s%c", newSpace, CONFIG_LINEFEED, CONFIG_LINEFEED, infoMessage, 0);
	}
	else {
		return;
	}

	if(mi != NULL && mi->guiRunning == 0) {
		if((infoBool = configFetch("info_stdout")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				fprintf(stdout, "%s.%c%c", newString, CONFIG_LINEFEED, 0);
			}
		}

		if((infoBool = configFetch("info_stderr")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				fprintf(stderr, "%s.%c%c", newString, CONFIG_LINEFEED, 0);
			}
		}

		if((infoBool = configFetch("info_syslog")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				if(fatalError == ERROR_FATAL) {
					syslog(LOG_ERR, "%s.%c", newString, 0);
				}
				else {
					syslog(LOG_INFO, "%s.%c", newString, 0);
				}
			}
		}
	}
	else {
		if(mi->infoLabel != NULL) {
			XtDestroyWidget(mi->infoLabel);

			mi->infoLabel = NULL;
		}

		thisString = XmStringCreateLocalized(newString);

		i = 0;

		XtSetArg(infoArgs[i], XmNtitle, TITLE_INFO_TITLE); i++;
		XtSetArg(infoArgs[i], XmNmessageString, thisString); i++;

		mi->infoLabel = XmCreateWarningDialog(mi->dlgInfo, TITLE_INFO_TITLE, infoArgs, i);

		tempWidget = XmMessageBoxGetChild(mi->infoLabel, XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild(tempWidget);

		tempWidget = XmMessageBoxGetChild(mi->infoLabel, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild(tempWidget);

		XmStringFree(thisString);

		XtManageChild(mi->infoLabel);
	}

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}

void warningMessage(int fatalError, char *warningMessage, struct mainInfo * mi) {
	int i;
	int *infoBool;

	char newSpace[CONFIG_STRING_SIZE];
	char newString[CONFIG_STRING_SIZE];

	Arg warnArgs[CONFIG_ARG_COUNT];
	Widget tempWidget;
	XmString thisString;

	time_t timeAnd;

	struct tm *timeNow;

	timeAnd = time(NULL);
	timeNow = localtime((time_t *) &timeAnd);

	strftime(newSpace, sizeof(newSpace), TIME_FORMAT, timeNow);

	if(errno == 0) {
		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s%c%c%s%c", newSpace, CONFIG_LINEFEED, CONFIG_LINEFEED, warningMessage, 0);
		}
		else {
			return;
		}
	}
	else {
		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s%c%c%s: %s%c", newSpace, CONFIG_LINEFEED, CONFIG_LINEFEED, warningMessage, strerror(errno), 0);
		}
		else {
			snprintf(newString, sizeof(newString), "%s%c%c%s%c", newSpace, CONFIG_LINEFEED, CONFIG_LINEFEED, strerror(errno), 0);
		}
	}

	if(mi != NULL && mi->guiRunning == 0) {
		if((infoBool = configFetch("warn_stdout")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				fprintf(stdout, "%s.%c%c", newString, CONFIG_LINEFEED, 0);
			}
		}

		if((infoBool = configFetch("warn_stderr")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				fprintf(stderr, "%s.%c%c", newString, CONFIG_LINEFEED, 0);
			}
		}

		if((infoBool = configFetch("warn_syslog")) != NULL) {
			if(*infoBool == CONFIG_TYPE_BOOLEAN_YES) {
				if(fatalError == ERROR_FATAL) {
					syslog(LOG_ERR, "%s.%c", newString, 0);
				}
				else {
					syslog(LOG_WARNING, "%s.%c", newString, 0);
				}
			}
		}
	}
	else {
		if(mi->warnLabel != NULL) {
			XtDestroyWidget(mi->warnLabel);

			mi->warnLabel = NULL;
		}

		thisString = XmStringCreateLocalized(newString);

		i = 0;

		XtSetArg(warnArgs[i], XmNtitle, TITLE_WARNING_TITLE); i++;
		XtSetArg(warnArgs[i], XmNmessageString, thisString); i++;

		mi->warnLabel = XmCreateWarningDialog(mi->dlgWarn, TITLE_WARNING_TITLE, warnArgs, i);

		tempWidget = XmMessageBoxGetChild(mi->warnLabel, XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild(tempWidget);

		tempWidget = XmMessageBoxGetChild(mi->warnLabel, XmDIALOG_HELP_BUTTON);
		XtUnmanageChild(tempWidget);

		XmStringFree(thisString);

		XtManageChild(mi->warnLabel);
	}

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}
