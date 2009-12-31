#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#include "declarations.h"
#include "defines.h"
#include "fallback.h"
#include "telmon.h"



int main(int argc, char *argv[]) {
	int i;
	char *confConfig;

	Arg newArgs[CONFIG_ARG_COUNT];
	Widget appPanels, appWindow;
	XEvent newEvent;

	/*
	 *
	 * Initialize default values.
	 *
	 */

	pMainMainInfo = &mainMainInfo;

	memset(pMainMainInfo, 0, sizeof(mainMainInfo));

	pMainMainInfo->setServer = DAEMON_TELLUD;
	pMainMainInfo->statThis = STAT_USAGE_TELLUD;

	/*
	 *
	 * Read command line and parse configuration file.
	 *
	 */

	cmdRead(argv, argc);

	if((confConfig = configFetch("config_file")) != NULL) {
		if(configRead(confConfig, pMainMainInfo) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file", pMainMainInfo);
		}
	}
	else {
		if(configRead(CONFIG_DEFAULT_FILE, pMainMainInfo) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file", pMainMainInfo);
		}
	}

	settingsLoad();

	cmdRead(argv, argc);

	/*
	 *
	 * Initialize main thread.
	 *
	 */

	configSetUmask(0077);

	if(configSetLocale(CONFIG_DEFAULT_LOCALE) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to set default locale", pMainMainInfo);
	}

	if(configCloseInput() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close standard input", pMainMainInfo);
	}

	/*
	 *
	 * Initialize main window.
	 *
	 */

	pMainMainInfo->appData.timeOut = 0;

	XtSetLanguageProc(NULL, NULL, NULL);

	i = 0;

	XtSetArg(newArgs[i], XmNtitle, WINDOW_TITLE); i++;
	XtSetArg(newArgs[i], XmNallowShellResize, True); i++;

	appWindow = XtAppInitialize(&pMainMainInfo->appContext, WINDOW_TITLE, NULL, 0, &argc, argv, fallBack, newArgs, i);
	appPanels = XtCreateManagedWidget("shell", xmPanedWindowWidgetClass, appWindow, NULL, 0);

	initWindow(appPanels, pMainMainInfo);

	pMainMainInfo->dlgInfo = appPanels;
	pMainMainInfo->dlgWarn = appPanels;
	pMainMainInfo->dlgHistory = appPanels;
	pMainMainInfo->dlgSettings = appPanels;
	pMainMainInfo->dlgExport = appPanels;

	XtRealizeWidget(appWindow);

	pMainMainInfo->appDisplay = XtDisplay(appWindow);
	pMainMainInfo->appScreen = XtScreen(appWindow);
	pMainMainInfo->appWindow = XtWindow(appWindow);
	pMainMainInfo->appGC = XCreateGC(pMainMainInfo->appDisplay, RootWindowOfScreen(pMainMainInfo->appScreen), 0, NULL);

	/*
	 *
	 * Initialize timer.
	 *
	 */

	pMainMainInfo->appData.timeOut = XtAppAddTimeOut(pMainMainInfo->appContext, 0, (XtTimerCallbackProc) netFetchStat, (struct mainInfo *) pMainMainInfo);

	/*
	 *
	 * Main loop.
	 *
	 */

	pMainMainInfo->guiRunning = 1;
	pMainMainInfo->theEnd = 0;

	while(pMainMainInfo->theEnd == 0) {
		XtAppNextEvent(pMainMainInfo->appContext, &newEvent);
		XtDispatchEvent(&newEvent);
	}

	/*
	 *
	 * Free allocated resources and terminate program.
	 *
	 */

	settingsSave();

	XtDestroyWidget(appWindow);
	XtDestroyApplicationContext(pMainMainInfo->appContext);

	exit(0);
}
