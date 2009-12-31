#include "structures.h"



// application.c
extern char *appGetName(struct mainInfo *);
extern char *appGetVersion(struct mainInfo *);
extern char *appGetDataPacket(struct mainInfo *);

// button.c
extern void buttonServer(Widget, XtPointer, XtPointer);
extern void buttonHelp(Widget, XtPointer, XtPointer);
extern void buttonInfo(Widget, XtPointer, XtPointer);
extern void buttonUpdate(Widget, XtPointer, XtPointer);
extern void buttonQuit(Widget, XtPointer, XtPointer);

// cmdline.c
extern void cmdRead(char **, int);

// config.c
extern int configRead(char *, struct mainInfo *);
extern void *configFetch(char *);
extern void configUpdateBoolean(char *, char *);
extern void configUpdateInteger(char *, char *);
extern void configUpdateString(char *, char *);
extern int configCloseInput(void);
extern int configDaemonize(void);
extern int configSetLocale(char *);
extern void configSetUmask(mode_t);

// history.c
extern void historyExport(Widget, XtPointer, XtPointer);
extern void buttonHistory(Widget, XtPointer, XtPointer);

// home.c
extern char *getHome(void);

// image.c
extern int imageSave(FILE *, int, int, unsigned short, char *);

// jip.c
extern int jipDeflate(unsigned char *, unsigned char *, struct threadCompressInfo *, unsigned int);

// messages.c
extern void infoMessage(int, char *, struct mainInfo *);
extern void warningMessage(int, char *, struct mainInfo *);

// network.c
extern void netFetchChart(struct mainInfo *);
extern void netFetchDays(struct mainInfo *);
extern void netFetchStat(struct mainInfo *);
extern void netFetchChartHandler(struct mainInfo *, char *, size_t, int);
extern void netFetchDaysHandler(struct mainInfo *, char *, size_t, int);
extern void netFetchStatHandler(struct mainInfo *, char *, size_t, int);
extern void netGetReply(int, struct replyInfo *, struct mainInfo *);
extern void netSplitReply(char *, struct replyInfo *, struct mainInfo *);
extern void netDeliverPacket(struct cmdArray *, struct replyInfo *, struct mainInfo *);
extern void netSendPacket(char *, size_t, struct replyInfo *, struct mainInfo *);

// settings.c
extern void buttonSettings(Widget, XtPointer, XtPointer);
extern void settingsLoad(void);
extern void settingsSave(void);

// stat.c
extern char *statChart(struct mainInfo *);
extern char *statHistory(struct mainInfo *);
extern char *statMonitor(struct mainInfo *);

// terminate.c
extern char *termNull(struct mainInfo *);

// window.c
extern void updateWindow(struct mainInfo *);
extern void initWindow(Widget, struct mainInfo *);
extern void initWindowForm(Widget, struct mainInfo *);
extern void initWindowOutput(Widget, struct mainInfo *);
extern void initWindowMenus(Widget, struct mainInfo *);
extern void initWindowButtons(Widget, struct mainInfo *);
