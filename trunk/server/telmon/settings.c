#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"
#include "settings.h"



void buttonSettings(Widget w, XtPointer client, XtPointer call) {
	int i;

	Arg newArgs[CONFIG_ARG_COUNT];

	extern struct mainInfo *pMainMainInfo;

	settingsClose(w, client, call);

	// Create panel

	i = 0;

	XtSetArg(newArgs[i], XmNtitle, WINDOW_TITLE_SETTINGS); i++;
	XtSetArg(newArgs[i], XmNdeleteResponse, XmDESTROY); i++;

	pMainMainInfo->setDialog = XmCreateDialogShell(pMainMainInfo->dlgSettings, TITLE_SETTINGS_TITLE, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	pMainMainInfo->setPanel = XmCreateRowColumn(pMainMainInfo->setDialog, "settings_panel", newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_COLUMN); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	pMainMainInfo->setOutput = XmCreateRowColumn(pMainMainInfo->setPanel, "settings_form", newArgs, i);

	// Create checkbox

	i = 0;

	XtSetArg(newArgs[i], XmNindicatorOn, XmINDICATOR_CHECK_BOX); i++;
	XtSetArg(newArgs[i], XmNindicatorType, XmN_OF_MANY); i++;
	XtSetArg(newArgs[i], XmNtoggleMode, XmTOGGLE_BOOLEAN); i++;

	if(pMainMainInfo->setSave != 0) {
		XtSetArg(newArgs[i], XmNset, XmSET); i++;
	}
	else {
		XtSetArg(newArgs[i], XmNset, XmUNSET); i++;
	}

	pMainMainInfo->setCheck = XmCreateToggleButtonGadget(pMainMainInfo->setOutput, TITLE_SETTINGS_CHECKBOX_SAVEONEXIT, newArgs, i);

	XtAddCallback(pMainMainInfo->setCheck, XmNvalueChangedCallback, settingsToggle, NULL);
	XtManageChild(pMainMainInfo->setCheck);

	// Create separator

	pMainMainInfo->setSep = XmCreateSeparatorGadget(pMainMainInfo->setPanel, "settings_separator", NULL, 0);

	XtManageChild(pMainMainInfo->setSep);

	// Create buttons

	i = 0;

	XtSetArg(newArgs[i], XmNleftAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNleftPosition, 0); i++;
	XtSetArg(newArgs[i], XmNrightAttachment, XmATTACH_POSITION); i++;
	XtSetArg(newArgs[i], XmNrightPosition, 1); i++;
	XtSetArg(newArgs[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNbottomAttachment, XmATTACH_FORM); i++;
	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	pMainMainInfo->setDismiss = XmCreatePushButtonGadget(pMainMainInfo->setPanel, TITLE_SETTINGS_BUTTON_DISMISS, newArgs, i);

	XtAddCallback(pMainMainInfo->setDismiss, XmNactivateCallback, settingsClose, NULL);
	XtManageChild(pMainMainInfo->setDismiss);

	XtManageChild(pMainMainInfo->setOutput);
	XtManageChild(pMainMainInfo->setPanel);
}

void settingsClose(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	if(pMainMainInfo->setDialog != 0) {
		XtDestroyWidget(pMainMainInfo->setDialog);

		pMainMainInfo->setDialog = 0;
	}
}

void settingsToggle(Widget w, XtPointer client, XtPointer call) {
	unsigned long i;

	XmToggleButtonCallbackStruct *clientData;

	extern struct mainInfo *pMainMainInfo;

	i = (unsigned long) client;

	clientData = (XmToggleButtonCallbackStruct *) call;

	if(clientData->set == XmSET) {
		pMainMainInfo->setSave |= (1 << i);
	}
	else {
		pMainMainInfo->setSave &= ~(1 << i);
	}
}

void settingsLoad(void) {
	int *confSave;

	char *newHome;
	char newPath[CONFIG_STRING_SIZE];

	extern struct mainInfo *pMainMainInfo;

	if((newHome = getHome()) != NULL) {
		snprintf(newPath, sizeof(newPath), "%s/.%s.%s%c", newHome, APPLICATION_NAME, CONFIG_DEFAULT_SAVE, 0);

		configRead(newPath, pMainMainInfo);
	}

	if((confSave = configFetch("save_settings")) != NULL) {
		pMainMainInfo->setSave = *confSave;
	}
}

void settingsSave(void) {
	int k;
	int thisSave;
	int *confSave;

	char *newHome;
	char newLine[CONFIG_STRING_SIZE];
	char newPath[CONFIG_STRING_SIZE];

	FILE *newFile;

	extern struct mainInfo *pMainMainInfo;

	thisSave = 0;

	if((confSave = configFetch("save_settings")) != NULL) {
		thisSave = *confSave;
	}

	if(pMainMainInfo->setSave != 0 || (pMainMainInfo->setSave == 0 && thisSave != 0)) {
		if((newHome = getHome()) != NULL) {
			k = 0;

			k += snprintf(newLine + k, sizeof(newLine) - k, "application_name = %s%c", APPLICATION_NAME, CONFIG_LINEFEED);
			k += snprintf(newLine + k, sizeof(newLine) - k, "application_version = %s%c", APPLICATION_VERSION, CONFIG_LINEFEED);

			k += snprintf(newLine + k, sizeof(newLine) - k, "monitor_server = %lu%c", pMainMainInfo->setServer, CONFIG_LINEFEED);
			k += snprintf(newLine + k, sizeof(newLine) - k, "save_settings = %lu%c", pMainMainInfo->setSave, CONFIG_LINEFEED);

			k += snprintf(newLine + k, sizeof(newLine) - k, "%c", 0);

			snprintf(newPath, sizeof(newPath), "%s/.%s.%s%c", newHome, APPLICATION_NAME, CONFIG_DEFAULT_SAVE, 0);

			if((newFile = fopen(newPath, "w+")) != NULL) {
				if(fwrite(newLine, strlen(newLine), 1, newFile) < 1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to write personal config file", pMainMainInfo);
				}

				if(fclose(newFile) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close personal config file", pMainMainInfo);
				}
			}
			else {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to open personal config file for writing", pMainMainInfo);
			}
		}
		else {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to resolve home directory", pMainMainInfo);
		}
	}
}
