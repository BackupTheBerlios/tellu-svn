#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "declarations.h"
#include "defines.h"
#include "export.h"



void historyExport(Widget w, XtPointer client, XtPointer call) {
	int i;
	char newName[CONFIG_SPACE_SIZE];

	Arg newArgs[CONFIG_ARG_COUNT];
	Widget newDialog;
	XmString newTitle, newContent;

	extern struct mainInfo *pMainMainInfo;

	if(pMainMainInfo->hstArrays[pMainMainInfo->hstDaysFetch].label[0] != 0) {
		snprintf(newName, sizeof(newName), "%s.bmp%c", pMainMainInfo->hstArrays[pMainMainInfo->hstDaysFetch].label, 0);
	}
	else {
		snprintf(newName, sizeof(newName), "Unknown.bmp%c", 0);
	}

	for(i = 0; i < strlen(newName); i++) {
		if(isspace((int) newName[i]) != 0) {
			newName[i] = '_';
		}
	}

	newTitle = XmStringCreateLocalized(TITLE_HISTORY_EXPORT);
	newContent = XmStringCreateLocalized(newName);

	i = 0;

	XtSetArg(newArgs[i], XmNtitle, WINDOW_TITLE_HISTORY_EXPORT); i++;
	XtSetArg(newArgs[i], XmNselectionLabelString, newTitle); i++;
	XtSetArg(newArgs[i], XmNtextString, newContent); i++;
	XtSetArg(newArgs[i], XmNdefaultButtonType, XmDIALOG_OK_BUTTON); i++;
	XtSetArg(newArgs[i], XmNautoUnmanage, False); i++;

	newDialog = XmCreatePromptDialog(pMainMainInfo->dlgExport, TITLE_HISTORY_EXPORT_TITLE, newArgs, i);

	XmStringFree(newTitle);
	XmStringFree(newContent);

	XtAddCallback(newDialog, XmNokCallback, exportOk, (XtPointer) newDialog);
	XtAddCallback(newDialog, XmNcancelCallback, exportCancel, (XtPointer) newDialog);

	XtSetSensitive(XtNameToWidget(newDialog, "Help"), False);

	XtManageChild(newDialog);
}

void exportCancel(Widget w, XtPointer client, XtPointer call) {
	XtDestroyWidget(XtParent(w));
}

void exportOk(Widget w, XtPointer client, XtPointer call) {
	char *newInput;

	FILE *newFile;

	XImage *newImage;
	XmSelectionBoxCallbackStruct *clientData;

	extern struct mainInfo *pMainMainInfo;

	clientData = (XmSelectionBoxCallbackStruct *) call;

	newInput = XmStringUnparse(clientData->value, NULL, XmCHARSET_TEXT, XmCHARSET_TEXT, NULL, 0, XmOUTPUT_ALL);

	if(newInput != NULL && newInput[0] != 0) {
		if((newFile = fopen(newInput, "r")) != NULL) {
			infoMessage(ERROR_SLIGHT, "File exists already, please pick another one", pMainMainInfo);

			XtFree(newInput);

			fclose(newFile);

			return;
		}
		else {
			if((newFile = fopen(newInput, "w+")) != NULL) {
				newImage = XGetImage(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, 0, 0, NUM_HISTORY_WIDTH, NUM_HISTORY_HEIGHT, -1, ZPixmap);

				if(imageSave(newFile, newImage->width, newImage->height, newImage->bits_per_pixel, newImage->data) != 0) {
					infoMessage(ERROR_SLIGHT, "Error occurred while saving history image", pMainMainInfo);

					unlink(newInput);
				}

				XFree(newImage);

				fclose(newFile);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to save history image", pMainMainInfo);
			}
		}
	}
	else {
		infoMessage(ERROR_SLIGHT, "File name is missing or invalid", pMainMainInfo);

		XtFree(newInput);

		return;
	}

	XtFree(newInput);
	XtDestroyWidget(XtParent(w));
}
