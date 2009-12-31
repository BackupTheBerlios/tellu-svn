#include "structures.h"



// application.c
extern char *appGetName(struct threadInfo *);
extern char *appGetVersion(struct threadInfo *);
extern char *appGetDataPacket(struct threadInfo *);

// cmdline.c
extern void cmdRead(char **, int);

// config.c
extern int configRead(char *);
extern void *configFetch(char *, int *);
extern void configUpdateBoolean(char *, char *);
extern void configUpdateInteger(char *, char *);
extern void configUpdateString(char *, char *);
extern int configChangeRoot(char *);
extern int configCloseInput(void);
extern int configDaemonize(void);
extern int configSetLocale(char *);
extern void configSetUmask(mode_t);

// jip.c
extern int jipDeflate(unsigned char *, unsigned char *, struct threadCompressInfo *, unsigned int);

// db_mysql.c
extern int mysqlConnect(struct threadStorageInfo *);
extern void mysqlDisconnect(struct threadStorageInfo *);
extern void mysqlEscape(struct threadStorageInfo *, char *, char *);
extern void mysqlMessage(struct threadStorageInfo *, int, char *, char *);
extern void mysqlPush(struct threadStorageInfo *, char *);
extern char *mysqlPull(struct threadStorageInfo *, char *);
extern void mysqlFree(struct threadStorageInfo *);

// db_plain.c
extern int plainConnect(struct threadStorageInfo *);
extern void plainDisconnect(struct threadStorageInfo *);
extern void plainEscape(struct threadStorageInfo *, char *, char *);
extern void plainMessage(struct threadStorageInfo *, int, char *, char *);
extern void plainPush(struct threadStorageInfo *, char *);
extern char *plainPull(struct threadStorageInfo *, char *);
extern void plainFree(struct threadStorageInfo *);

// messages.c
extern void infoMessage(int, char *);
extern void infoThread(int, char *, char *, int, int *, int *);
extern void warningMessage(int, char *);
extern void warningThread(int, char *, char *, int, int *, int *);
extern void logMessage(char *);
extern void histMessage(unsigned long long);

// network.c
extern int netCreateListenSocket(short);
extern void netCloseSocket(int);
extern int netWaitConnection(int, struct threadInfo *);
extern char *netReadPacket(int, struct threadInfo *);
extern void netFreePacket(char *);
extern void netDummyConnect(void);
extern void netSendReply(struct cmdArray *, int, struct threadInfo *);

// node.c
extern void nodeInitNames(void);
extern char *nodeFetchNode(void);
extern char *nodeFetchDomain(void);
extern char *nodeFetchSystem(void);
extern char *nodeFetchRelease(void);
extern char *nodeFetchMachine(void);
extern char *nodeFetchUserLogin(void);
extern char *nodeFetchUserName(void);
extern char *nodeFetchUserHome(void);
extern char *nodeFetchUserGroup(void);

// pid.c
extern void pidCreate(void);
extern void pidRemove(void);

// reply.c
extern char *replyChartConns(struct threadInfo *);
extern char *replyHistoryDate(struct threadInfo *);
extern char *replyWorkersAvailable(struct threadInfo *);
extern char *replyServerStarted(struct threadInfo *);
extern char *replyLastTask(struct threadInfo *);
extern char *replyTotalTasks(struct threadInfo *);
extern char *replyInfoTime(struct threadInfo *);
extern char *replyWarnTime(struct threadInfo *);
extern char *replyInfoMessage(struct threadInfo *);
extern char *replyWarnMessage(struct threadInfo *);

// shm.c
extern void shmCreate(int, int);
extern void shmRemove(int);
extern void shmUpdate(int, int);
extern void shmUsage(int);
extern void shmFetch(int, struct threadDaemonInfo *);
extern void shmInfoMessage(char *, int);
extern void shmWarningMessage(char *, int);

// telmond.c
extern void handlerProcess(void);
extern void timerStatThreads(int);
extern void timerStopThreads(int);

// thread.c
extern int threadInit(struct threadInfo *, void *, void *);
extern int threadKill(struct threadInfo *);
extern int threadWait(struct threadInfo *);
extern int threadWake(struct threadInfo *);
extern void threadStack(int);
extern void beginProcess(struct threadInfo *);
extern void startProcess(int);
extern void timesProcess(struct threadInfo *);
extern void exitProcess(int);
extern void exitThread(struct threadInfo *, void *);

// timer.c
extern int timerInit(time_t, long, void *);
extern void timerWait(unsigned int *, unsigned int, useconds_t);

// terminate.c
extern char *termNull(struct threadInfo *);

// uid.c
extern int uidSwitch(uid_t);
extern int gidSwitch(gid_t);

// worker.c
extern void workerThread(void *);
