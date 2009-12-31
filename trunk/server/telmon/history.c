#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"
#include "history.h"



void buttonHistory(Widget w, XtPointer client, XtPointer call) {
	int i;
	unsigned long k;

	Arg newArgs[CONFIG_ARG_COUNT];

	extern struct mainInfo *pMainMainInfo;

	historyClose(w, client, call);

	if(pMainMainInfo->hstPixmap == 0) {
		if((pMainMainInfo->hstPixmap = XCreatePixmap(pMainMainInfo->appDisplay, RootWindowOfScreen(pMainMainInfo->appScreen), NUM_HISTORY_WIDTH, NUM_HISTORY_HEIGHT, DefaultDepthOfScreen(pMainMainInfo->appScreen))) == 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for pixmap", pMainMainInfo);

			return;
		}
	}

	// Create panel

	i = 0;

	XtSetArg(newArgs[i], XmNtitle, WINDOW_TITLE_HISTORY); i++;
	XtSetArg(newArgs[i], XmNdeleteResponse, XmDESTROY); i++;

	pMainMainInfo->hstDialog = XmCreateDialogShell(pMainMainInfo->dlgHistory, TITLE_HISTORY_TITLE, newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	pMainMainInfo->hstPanel = XmCreateRowColumn(pMainMainInfo->hstDialog, "history_panel", newArgs, i);

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmHORIZONTAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmAUTOMATIC); i++;

	pMainMainInfo->hstOutput = XmCreateRowColumn(pMainMainInfo->hstPanel, "history_form", newArgs, i);

	// Create drawing area

	i = 0;

	XtSetArg(newArgs[i], XmNwidth, NUM_HISTORY_WIDTH); i++;
	XtSetArg(newArgs[i], XmNheight, NUM_HISTORY_HEIGHT); i++;

	pMainMainInfo->hstDraw = XmCreateDrawingArea(pMainMainInfo->hstOutput, "history_drawing", newArgs, i);

	XtAddCallback(pMainMainInfo->hstDraw, XmNinputCallback, historyExpose, NULL);
	XtAddCallback(pMainMainInfo->hstDraw, XmNexposeCallback, historyExpose, NULL);

	XtVaSetValues(pMainMainInfo->hstDraw, XmNuserData, pMainMainInfo->appGC, NULL);
	XtManageChild(pMainMainInfo->hstDraw);

	// Create control area

	i = 0;

	XtSetArg(newArgs[i], XmNorientation, XmVERTICAL); i++;
	XtSetArg(newArgs[i], XmNpacking, XmPACK_TIGHT); i++;
	XtSetArg(newArgs[i], XmNrowColumnType, XmWORK_AREA); i++;
	XtSetArg(newArgs[i], XmNscrollingPolicy, XmNONE); i++;

	pMainMainInfo->hstCtrl = XtCreateManagedWidget("history_controls", xmRowColumnWidgetClass, pMainMainInfo->hstOutput, newArgs, i);

	// Create control area menus

	netFetchDays(pMainMainInfo);

	pMainMainInfo->hstMenuDate = XmCreatePulldownMenu(pMainMainInfo->hstCtrl, "date", NULL, 0);

	i = 0;

	XtSetArg(newArgs[i], XmNsubMenuId, pMainMainInfo->hstMenuDate); i++;

	pMainMainInfo->hstOptionDate = XmCreateOptionMenu(pMainMainInfo->hstCtrl, "option", newArgs, i);

	XtManageChild(pMainMainInfo->hstOptionDate);

	for(k = 0; ; k++) {
		if(pMainMainInfo->hstArrays[k].label[0] == 0) {
			break;
		}

		pMainMainInfo->hstButtonDate = XtCreateManagedWidget(pMainMainInfo->hstArrays[k].label, xmPushButtonWidgetClass, pMainMainInfo->hstMenuDate, NULL, 0);

		XtAddCallback(pMainMainInfo->hstButtonDate, XmNactivateCallback, historyMenuDate, (XtPointer) k);
	}

	if(k == 0) {
		pMainMainInfo->hstButtonDate = XtCreateManagedWidget(TITLE_HISTORY_MENU_EMPTY, xmPushButtonWidgetClass, pMainMainInfo->hstMenuDate, NULL, 0);
	}

	pMainMainInfo->hstDaysFetch = 0;

	// Create separator

	pMainMainInfo->hstButton = XmCreateSeparatorGadget(pMainMainInfo->hstCtrl, "history_separator", NULL, 0);

	XtManageChild(pMainMainInfo->hstButton);

	// Create control area buttons

	i = 0;

	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	pMainMainInfo->hstButton = XmCreatePushButtonGadget(pMainMainInfo->hstCtrl, TITLE_HISTORY_BUTTON_UPDATE, newArgs, i);

	XtAddCallback(pMainMainInfo->hstButton, XmNactivateCallback, historyUpdate, NULL);
	XtManageChild(pMainMainInfo->hstButton);

	i = 0;

	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	pMainMainInfo->hstButton = XmCreatePushButtonGadget(pMainMainInfo->hstCtrl, TITLE_HISTORY_BUTTON_SAVE, newArgs, i);

	XtAddCallback(pMainMainInfo->hstButton, XmNactivateCallback, historyExport, NULL);
	XtManageChild(pMainMainInfo->hstButton);

	// Create separator

	pMainMainInfo->hstButton = XmCreateSeparatorGadget(pMainMainInfo->hstCtrl, "history_separator", NULL, 0);

	XtManageChild(pMainMainInfo->hstButton);

	i = 0;

	XtSetArg(newArgs[i], XmNshowAsDefault, True); i++;

	pMainMainInfo->hstButton = XmCreatePushButtonGadget(pMainMainInfo->hstCtrl, TITLE_HISTORY_BUTTON_DISMISS, newArgs, i);

	XtAddCallback(pMainMainInfo->hstButton, XmNactivateCallback, historyClose, NULL);
	XtManageChild(pMainMainInfo->hstButton);

	XtManageChild(pMainMainInfo->hstOutput);
	XtManageChild(pMainMainInfo->hstPanel);

	historyMenuDate(w, client, call);
}

void historyClose(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	if(pMainMainInfo->hstDialog != 0) {
		XtDestroyWidget(pMainMainInfo->hstDialog);

		pMainMainInfo->hstDialog = 0;
	}
}

void historyExpose(Widget w, XtPointer client, XtPointer call) {
	XEvent *clientEvent;
	XmDrawingAreaCallbackStruct *clientData;

	extern struct mainInfo *pMainMainInfo;

	clientData = (XmDrawingAreaCallbackStruct *) call;
	clientEvent = clientData->event;

	XCopyArea(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, clientEvent->xany.window, pMainMainInfo->appGC, 0, 0, NUM_HISTORY_WIDTH, NUM_HISTORY_HEIGHT, 0, 0);
}

void historyMenuDate(Widget w, XtPointer client, XtPointer call) {
	extern struct mainInfo *pMainMainInfo;

	pMainMainInfo->hstDaysFetch = (long) client;

	historyUpdate(w, client, call);
}

void historyUpdate(Widget w, XtPointer client, XtPointer call) {
	int i, m, v, x, y;
	float k, l, n;
	unsigned long p;
	unsigned long brColor, fgColor, fnColor, hlColor;

	char newString[CONFIG_SPACE_SIZE];
	unsigned int thisCoords[24];

	extern struct mainInfo *pMainMainInfo;

	memset(&thisCoords, 0, sizeof(thisCoords));

	// Fetch chart data from the server

	netFetchChart(pMainMainInfo);

	// Find highest value and initialize coordinate array

	p = 0;
	k = 0.0;
	n = 0.0;

	for(i = 0; i < 24; i++) {
		if((float) pMainMainInfo->hstDaysStat[i] > k) {
			p = pMainMainInfo->hstDaysStat[i];
			k = (float) pMainMainInfo->hstDaysStat[i];
		}

		n += k;
	}

	n /= 24;
	m = (int) n;

	if(k > 0.0) {
		l = k / ((NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 2) - NUM_HISTORY_MARGIN_TOP);

		for(i = 0; i < 24; i++) {
			thisCoords[i] = (unsigned int) pMainMainInfo->hstDaysStat[i] / l;
		}

		m /= l;
	}

	// Clear window and draw bars

	brColor = historyGetColor(COLOR_HISTORY_TOWERBORDER);
	fgColor = historyGetColor(COLOR_HISTORY_TOWER);
	fnColor = historyGetColor(COLOR_HISTORY_FONT);
	hlColor = historyGetColor(COLOR_HISTORY_TOWERMERIDIAN);

	XSetLineAttributes(pMainMainInfo->appDisplay, pMainMainInfo->appGC, 1, LineSolid, 0, 0);

	historyUpdateClear(w, client, call);
	historyUpdateInit(w, client, call);

	v = (NUM_HISTORY_WIDTH - (NUM_HISTORY_MARGIN_SIDE * 2)) / 24;
	x = NUM_HISTORY_MARGIN_SIDE + 2;
	y = NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1;

	for(i = 0; i < 24; i++) {
		if(thisCoords[i] != 0) {
			XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, fgColor);

			XFillRectangle(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, x, y - thisCoords[i], v - 3, thisCoords[i]);

			XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, brColor);

			XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, x, y - thisCoords[i], x + v - 4, y - thisCoords[i]);
			XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, x + v - 4, y - thisCoords[i], x + v - 4, y);
			XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, x, y, x, y - thisCoords[i]);
		}

		x += v;
	}

	// Draw meridian line

	if(m != 0) {
		y = NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1;

		snprintf(newString, sizeof(newString), "%.0f%c", n, 0);

		XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, hlColor);
		XSetLineAttributes(pMainMainInfo->appDisplay, pMainMainInfo->appGC, 1, LineOnOffDash, 0, 0);

		XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_SIDE + 1, y - m, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 2, y - m);

		XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, fnColor);
		XSetLineAttributes(pMainMainInfo->appDisplay, pMainMainInfo->appGC, 1, LineSolid, 0, 0);

		XDrawString(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, (NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE) + 4, y - m + 5, newString, strlen(newString));
	}

	// Draw information area text

	i = 0;

	switch(pMainMainInfo->setServer) {
		case DAEMON_TELLUD:
			i += snprintf(newString + i, sizeof(newString) - i, "%s", TITLE_MENU_SERVER_OPTION_1);

			break;
		case DAEMON_TELMOND:
			i += snprintf(newString + i, sizeof(newString) - i, "%s", TITLE_MENU_SERVER_OPTION_2);

			break;
		case DAEMON_TELSKIND:
			i += snprintf(newString + i, sizeof(newString) - i, "%s", TITLE_MENU_SERVER_OPTION_3);

			break;
		default:
			break;
	}

	if(pMainMainInfo->hstArrays[pMainMainInfo->hstDaysFetch].label[0] != 0) {
		i += snprintf(
			newString + i,
			sizeof(newString) - i,
			" usage at %s",
			pMainMainInfo->hstArrays[pMainMainInfo->hstDaysFetch].label
		);
	}

	newString[i] = 0;

	XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, fnColor);

	XDrawString(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_SIDE, NUM_HISTORY_HEIGHT - 10, newString, strlen(newString));

	snprintf(newString, sizeof(newString), "%lu%c", p, 0);

	XDrawString(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_TOP, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1, "0", 1);
	XDrawString(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_TOP, NUM_HISTORY_MARGIN_TOP + 10, newString, strlen(newString));

	// Redraw window

	XCopyArea(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, XtWindow(pMainMainInfo->hstDraw), pMainMainInfo->appGC, 0, 0, NUM_HISTORY_WIDTH, NUM_HISTORY_HEIGHT, 0, 0);
}

void historyUpdateClear(Widget w, XtPointer client, XtPointer call) {
	unsigned long bgColor;

	extern struct mainInfo *pMainMainInfo;

	bgColor = historyGetColor(COLOR_HISTORY_BACKGROUND);

	XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, bgColor);

	XFillRectangle(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, 0, 0, NUM_HISTORY_WIDTH, NUM_HISTORY_HEIGHT);
}

void historyUpdateInit(Widget w, XtPointer client, XtPointer call) {
	int i, e, f, k, l;
	unsigned long fgColor, fnColor, hlColor, slColor;

	char newString[CONFIG_SPACE_SIZE];

	extern struct mainInfo *pMainMainInfo;

	fgColor = historyGetColor(COLOR_HISTORY_BORDER);
	fnColor = historyGetColor(COLOR_HISTORY_FONT);
	hlColor = historyGetColor(COLOR_HISTORY_GRID);
	slColor = historyGetColor(COLOR_HISTORY_SEPARATOR);

	// Draw outer border

	XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, fgColor);

	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, 0, 0, NUM_HISTORY_WIDTH, 0);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_WIDTH - 1, 0, NUM_HISTORY_WIDTH - 1, NUM_HISTORY_HEIGHT);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_WIDTH - 1, NUM_HISTORY_HEIGHT - 1, 0, NUM_HISTORY_HEIGHT - 1);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, 0, NUM_HISTORY_HEIGHT - 1, 0, 0);

	// Draw inner border

	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_SIDE - 5, NUM_HISTORY_MARGIN_TOP, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 1, NUM_HISTORY_MARGIN_TOP);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 1, NUM_HISTORY_MARGIN_TOP, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 1, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 1, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1, NUM_HISTORY_MARGIN_SIDE - 5, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1);
	XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_SIDE, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1, NUM_HISTORY_MARGIN_SIDE, NUM_HISTORY_MARGIN_TOP);

	// Draw grid

	XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, hlColor);

	e = 0;
	f = 2;
	k = (NUM_HISTORY_WIDTH - (NUM_HISTORY_MARGIN_SIDE * 2)) / 24;
	l = k + NUM_HISTORY_MARGIN_SIDE;

	for(i = 2; i < 25; i++) {
		XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, l, NUM_HISTORY_MARGIN_TOP + 1, l, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1);

		l = (k * i) + NUM_HISTORY_MARGIN_SIDE;

		e ^= 1;

		if(e == 0) {
			snprintf(newString, sizeof(newString), "%.2d:00%c", f, 0);

			XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, fnColor);

			XDrawString(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, l - k - 14, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM + NUM_HISTORY_FONT_HEIGHT, newString, strlen(newString));

			XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, hlColor);

			f += 2;
		}
	}

	k = (NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_TOP - NUM_HISTORY_MARGIN_BOTTOM) / 10;
	l = k + NUM_HISTORY_MARGIN_TOP;

	for(i = 2; i < 11; i++) {
		XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, NUM_HISTORY_MARGIN_SIDE + 1, l, NUM_HISTORY_WIDTH - NUM_HISTORY_MARGIN_SIDE - 1, l);

		l = (k * i) + NUM_HISTORY_MARGIN_TOP;
	}

	// Draw daytime separators

	XSetForeground(pMainMainInfo->appDisplay, pMainMainInfo->appGC, slColor);

	k = (NUM_HISTORY_WIDTH - (NUM_HISTORY_MARGIN_SIDE * 2)) / 4;
	l = k + NUM_HISTORY_MARGIN_SIDE;

	for(i = 2; i < 5; i++) {
		XDrawLine(pMainMainInfo->appDisplay, pMainMainInfo->hstPixmap, pMainMainInfo->appGC, l, NUM_HISTORY_MARGIN_TOP + 1, l, NUM_HISTORY_HEIGHT - NUM_HISTORY_MARGIN_BOTTOM - 1);

		l = (k * i) + NUM_HISTORY_MARGIN_SIDE;
	}
}

unsigned long historyGetColor(char *colorName) {
	Colormap newColormap;
	XColor newColor, newExact;

	extern struct mainInfo *pMainMainInfo;

	newColormap = DefaultColormap(pMainMainInfo->appDisplay, DefaultScreen(pMainMainInfo->appDisplay));

	if(XAllocNamedColor(pMainMainInfo->appDisplay, newColormap, colorName, &newColor, &newExact) == 0) {
		return(0);
	}

	return(newColor.pixel);
}
