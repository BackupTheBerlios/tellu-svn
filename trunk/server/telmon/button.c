#include <stdio.h>
#include <stdlib.h>

#include "banner.h"
#include "declarations.h"
#include "defines.h"



void buttonServer(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	switch((long) client) {
		case 0:
			pMainMainInfo->setServer = DAEMON_TELLUD;
			pMainMainInfo->statThis = STAT_USAGE_TELLUD;

			break;
		case 1:
			pMainMainInfo->setServer = DAEMON_TELMOND;
			pMainMainInfo->statThis = STAT_USAGE_TELMOND;

			break;
		case 2:
			pMainMainInfo->setServer = DAEMON_TELSKIND;
			pMainMainInfo->statThis = STAT_USAGE_TELSKIND;

			break;
		default:
			break;
	}

	XtRemoveTimeOut(pMainMainInfo->appData.timeOut);

	netFetchStat(pMainMainInfo);
}

void buttonHelp(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	infoMessage(ERROR_NOERROR, MESSAGE_HELP, pMainMainInfo);
}

void buttonInfo(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	infoMessage(ERROR_NOERROR, BANNER_LICENSE, pMainMainInfo);
}

void buttonUpdate(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	XtRemoveTimeOut(pMainMainInfo->appData.timeOut);

	netFetchStat(pMainMainInfo);
}

void buttonQuit(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	pMainMainInfo->theEnd++;
}
