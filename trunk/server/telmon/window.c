#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



void updateWindow(struct mainInfo * mi) {
	int i;

	char newString[CONFIG_SPACE_SIZE];

	Widget newStrings[] = {
		mi->outField1, mi->outField2, mi->outField3, mi->outField4, mi->outField5,
		NULL
	};

	if(mi == NULL || mi->guiRunning == 0) {
		return;
	}

	for(i = 0; ; i++) {
		if(newStrings[i] == NULL) {
			break;
		}

		XmTextFieldSetString(newStrings[i], "");
	}

	i = 0;

	if(mi->srvWorkersAvailable[0] != 0 && mi->srvWorkersAvailable[0] != '0') {
		snprintf(newString, sizeof(newString), "Server started at %s, with %s workers%c", mi->srvServerStarted, mi->srvWorkersAvailable, 0);

		XmTextFieldSetString(newStrings[i], newString); i++;

		if(mi->srvTotalTasks[0] != 0 && mi->srvTotalTasks[0] != '0') {
			snprintf(newString, sizeof(newString), "%s clients served, last at %s%c", mi->srvTotalTasks, mi->srvLastTask, 0);

			XmTextFieldSetString(newStrings[i], newString); i++;
		}

		if(mi->srvInfoMessage[0] != 0) {
			snprintf(newString, sizeof(newString), "Last message at %s, '%s'%c", mi->srvInfoTime, mi->srvInfoMessage, 0);

			XmTextFieldSetString(newStrings[i], newString); i++;
		}

		if(mi->srvWarnMessage[0] != 0) {
			snprintf(newString, sizeof(newString), "Last error at %s, '%s'%c", mi->srvWarnTime, mi->srvWarnMessage, 0);

			XmTextFieldSetString(newStrings[i], newString); i++;
		}
	}
	else {
		i = 0;

		XmTextFieldSetString(newStrings[i], "Unable to fetch information from the server"); i++;

		for(; ; i++) {
			if(newStrings[i] == NULL) {
				break;
			}

			XmTextFieldSetString(newStrings[i], "");
		}
	}
}

void initWindow(Widget winParent, struct mainInfo * mi) {
	initWindowForm(winParent, mi);
	initWindowOutput(winParent, mi);
	initWindowMenus(winParent, mi);
	initWindowButtons(winParent, mi);
}

void initWindowForm(Widget winParent, struct mainInfo * mi) {
	int i;

	Arg newArgs[CONFIG_ARG_COUNT];
	XmString newString;

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	mi->winPanel = XtCreateManagedWidget("panel", xmRowColumnWidgetClass, winParent, newArgs, i);

	newString = XmStringCreateLocalized(WINDOW_TITLE);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNlabelType, XmSTRING); i++;
	XtSetArg(newArgs[i], XmNlabelString, newString); i++;

	mi->winTitle = XtCreateManagedWidget("title", xmLabelWidgetClass, mi->winPanel, newArgs, i);

	XmStringFree(newString);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;
	XtSetArg(newArgs[i], XmNwidth, NUM_MAIN_COLROWS); i++;
	XtSetArg(newArgs[i], XmNheight, NUM_MAIN_COLLINES); i++;

	mi->winShell = XtCreateManagedWidget("field", xmScrolledWindowWidgetClass, mi->winPanel, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNrowColumnType, XmWORK_AREA); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	mi->winOutput = XtCreateManagedWidget("output", xmRowColumnWidgetClass, mi->winShell, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNrowColumnType, XmWORK_AREA); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	mi->winMenus = XtCreateManagedWidget("menus", xmRowColumnWidgetClass, mi->winPanel, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNfractionBase, NUM_MAIN_BUTTONS); i++;

	mi->winButtons = XtCreateManagedWidget("buttons", xmFormWidgetClass, mi->winPanel, newArgs, i);
}

void initWindowOutput(Widget winParent, struct mainInfo * mi) {
	int i;

	Arg newArgs[CONFIG_ARG_COUNT];

	i = 0;

	XtSetArg(newArgs[i], XmNeditable, False); i++;
	XtSetArg(newArgs[i], XmNcolumns, NUM_MAIN_COLUMNS); i++;
	XtSetArg(newArgs[i], XmNcursorPositionVisible, False); i++;
	XtSetArg(newArgs[i], XmNmarginWidth, NUM_MAIN_COLMARGIN); i++;
	XtSetArg(newArgs[i], XmNmarginHeight, NUM_MAIN_COLMARGIN); i++;

	mi->outField1 = XtCreateManagedWidget("output_1", xmTextFieldWidgetClass, mi->winOutput, newArgs, i);
	mi->outField2 = XtCreateManagedWidget("output_2", xmTextFieldWidgetClass, mi->winOutput, newArgs, i);
	mi->outField3 = XtCreateManagedWidget("output_3", xmTextFieldWidgetClass, mi->winOutput, newArgs, i);
	mi->outField4 = XtCreateManagedWidget("output_4", xmTextFieldWidgetClass, mi->winOutput, newArgs, i);
	mi->outField5 = XtCreateManagedWidget("output_5", xmTextFieldWidgetClass, mi->winOutput, newArgs, i);
}

void initWindowMenus(Widget winParent, struct mainInfo * mi) {
	int i;
	int thisSelect;
	int *confSelect;

	XmString newTitle;
	XmString newOption[TITLE_MENU_SERVER_OPTIONS];

	char *newOptions[] = {
		TITLE_MENU_SERVER_OPTION_1, TITLE_MENU_SERVER_OPTION_2, TITLE_MENU_SERVER_OPTION_3
	};

	thisSelect = DAEMON_TELLUD;

	if((confSelect = configFetch("monitor_server")) != NULL) {
		thisSelect = *confSelect;
	}

	mi->setServer = (unsigned long) thisSelect;

	switch(thisSelect) {
		case DAEMON_TELLUD:
			mi->statThis = STAT_USAGE_TELLUD;

			break;
		case DAEMON_TELMOND:
			mi->statThis = STAT_USAGE_TELMOND;

			break;
		case DAEMON_TELSKIND:
			mi->statThis = STAT_USAGE_TELSKIND;

			break;
		default:
			thisSelect = DAEMON_TELLUD;

			mi->statThis = STAT_USAGE_TELLUD;
			mi->setServer = (unsigned long) thisSelect;

			break;
	}

	thisSelect--;

	newTitle = XmStringCreateLocalized(TITLE_MENU_SERVER);

	for(i = 0; i < TITLE_MENU_SERVER_OPTIONS; i++) {
		newOption[i] = XmStringCreateLocalized(newOptions[i]);
	}

	mi->drpServer = XmVaCreateSimpleOptionMenu(mi->winMenus, "menu_server", newTitle, 'S', thisSelect, buttonServer,
		XmVaPUSHBUTTON, newOption[0], '1', NULL, NULL,
		XmVaPUSHBUTTON, newOption[1], '2', NULL, NULL,
		XmVaPUSHBUTTON, newOption[2], '3', NULL, NULL,
		NULL
	);

	XmStringFree(newTitle);

	for(i = 0; i < TITLE_MENU_SERVER_OPTIONS; i++) {
		XmStringFree(newOption[i]);
	}

	XtManageChild(mi->drpServer);
}

void initWindowButtons(Widget winParent, struct mainInfo * mi) {
	int i;

	Arg newArgs[CONFIG_ARG_COUNT];

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 0); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 1); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnInfo = XtCreateManagedWidget(TITLE_BUTTON_1, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 1); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 2); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnHelp = XtCreateManagedWidget(TITLE_BUTTON_2, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 2); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 3); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnUpdate = XtCreateManagedWidget(TITLE_BUTTON_3, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 3); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 4); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnHistory = XtCreateManagedWidget(TITLE_BUTTON_4, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 4); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 5); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnSettings = XtCreateManagedWidget(TITLE_BUTTON_5, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 5); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 6); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	mi->btnQuit = XtCreateManagedWidget(TITLE_BUTTON_6, xmPushButtonWidgetClass, mi->winButtons, newArgs, i);

	XtAddCallback(mi->btnInfo, XmNactivateCallback, (XtCallbackProc) buttonInfo, NULL);
	XtAddCallback(mi->btnHelp, XmNactivateCallback, (XtCallbackProc) buttonHelp, NULL);
	XtAddCallback(mi->btnUpdate, XmNactivateCallback, (XtCallbackProc) buttonUpdate, NULL);
	XtAddCallback(mi->btnHistory, XmNactivateCallback, (XtCallbackProc) buttonHistory, NULL);
	XtAddCallback(mi->btnSettings, XmNactivateCallback, (XtCallbackProc) buttonSettings, NULL);
	XtAddCallback(mi->btnQuit, XmNactivateCallback, (XtCallbackProc) buttonQuit, NULL);
}
