#include <stdio.h>
#include <stdlib.h>
#include <Xm/XmAll.h>

#include "defines.h"



typedef struct {
	XtIntervalId timeOut;
} AppData, *AppDataPtr;

struct hstArray {
	char label[32];								// History window menu entry label
	char dayname[16];							// History window menu dayname
	char daynum[8];								// History window menu day
	char monthname[16];							// History window menu monthname
	char yearnum[8];							// History window menu year
};

struct threadCompressInfo {
	int i, n;								// Thread local variables
	unsigned int o, w, x;							// Thread local variables
	int jipInput, jipOutput;						// Thread offset variables
	int jipBitBuffer, jipBitCount;						// Thread bitcount variables
	unsigned char *jipAppend;						// Thread append buffer pointer
	unsigned char *jipString;						// Thread string buffer pointer
	unsigned int *jipPrefix;						// Thread prefix buffer pointer
	unsigned char jipDecode[4096];						// Thread decode buffer
};

struct mainInfo {
	int guiRunning;								// GUI is up and running
	int theEnd;								// Request main thread to quit
	int infoVisible, warnVisible;						// Requester visible flags
	unsigned long setSave;							// Save settings on exit
	unsigned long setServer;						// Which server id to get statistics from
	char *statThis;								// Which server name to get statistics from

	int hstDaysCount;							// Days available count
	long hstDaysFetch;							// Day chart to fetch
	unsigned long hstDaysStat[24];						// Daily stats

	char chartServer[CONFIG_SPACE_SIZE];					// Which server name to get chart from

	char srvWorkersAvailable[CONFIG_SPACE_SIZE];				// Workers available
	char srvServerStarted[CONFIG_SPACE_SIZE];				// Server started time
	char srvLastTask[CONFIG_SPACE_SIZE];					// Last task time
	char srvTotalTasks[CONFIG_SPACE_SIZE];					// Total tasks
	char srvInfoTime[CONFIG_SPACE_SIZE];					// Info time
	char srvWarnTime[CONFIG_SPACE_SIZE];					// Warning time
	char srvInfoMessage[CONFIG_SPACE_SIZE];					// Info message
	char srvWarnMessage[CONFIG_SPACE_SIZE];					// Warning message

	AppData appData;							// Application data
	Display *appDisplay;							// Application display handle
	GC appGC;								// Application graphic context handle
	Screen *appScreen;							// Application screen handle
	Window appWindow;							// Application window handles
	XtAppContext appContext;						// Application context

	Pixmap hstPixmap;							// History window pixmap handle

	Widget btnInfo, btnHelp, btnUpdate, btnHistory, btnSettings, btnQuit;	// Main window button widgets
	Widget drpServer;							// Main window menu widgets
	Widget dlgInfo, dlgWarn, dlgHistory, dlgSettings, dlgExport;		// Main window dialog widgets
	Widget outField1, outField2, outField3, outField4, outField5;		// Main window textarea widgets
	Widget winPanel, winTitle, winShell, winOutput, winMenus, winButtons;	// Main window panel widgets
	Widget infoLabel, warnLabel;						// Main window requester widgets

	Widget setDialog, setPanel, setOutput, setCheck, setSep, setDismiss;	// Settings window widgets
	Widget hstDialog, hstPanel, hstOutput, hstDraw, hstCtrl, hstButton;	// History window widgets
	Widget hstMenuDate, hstOptionDate, hstButtonDate;			// History window menu widgets

	struct hstArray hstArrays[366];						// History window menu entires

	struct threadCompressInfo compressInfo;					// Compress info structure
};

struct replyInfo {
	int replyCount;								// Reply items in packet
	void (*handler)(struct mainInfo *, char *, size_t, int);		// Reply handler
};

struct cmdArray {
	char *task;								// Task name
	char *(*allocator)(struct mainInfo *);					// Task allocator task pointer
	void (*destroyer)(char *);						// Task destroyer task pointer
};
