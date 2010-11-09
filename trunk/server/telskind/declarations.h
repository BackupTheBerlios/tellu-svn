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

// db_ldap.c
extern int ldapLogin(char *, char *, struct threadInfo *);
extern void ldapMessage(struct threadInfo *, int, char *, char *);

// db_mysql.c
extern int mysqlConnect(struct threadStorageInfo *);
extern void mysqlDisconnect(struct threadStorageInfo *);
extern void mysqlEscape(struct threadStorageInfo *, char *, char *);
extern void mysqlMessage(struct threadStorageInfo *, int, char *, char *);
extern void mysqlPush(struct threadStorageInfo *, char *);
extern char *mysqlPull(struct threadStorageInfo *, char *);
extern char *mysqlRound(struct threadStorageInfo *, char *);
extern void mysqlFree(struct threadStorageInfo *);
extern void mysqlExpire(struct threadStorageInfo *);
extern int mysqlCookie(char *, int, struct threadStorageInfo *);
extern int mysqlInsert(char *, int, struct threadStorageInfo *);
extern int mysqlLogin(char *, char *, int, int, struct threadStorageInfo *);
extern int mysqlLogout(char *, int, struct threadStorageInfo *);
extern int mysqlSession(char *, char *, int, int, struct threadStorageInfo *);
extern int mysqlPermission(unsigned long long, char *, char *, char *, int, int, int, struct threadStorageInfo *);

// db_plain.c
extern int plainConnect(struct threadStorageInfo *);
extern void plainDisconnect(struct threadStorageInfo *);
extern void plainEscape(struct threadStorageInfo *, char *, char *);
extern void plainMessage(struct threadStorageInfo *, int, char *, char *);
extern void plainPush(struct threadStorageInfo *, char *);
extern char *plainPull(struct threadStorageInfo *, char *);
extern char *plainRound(struct threadStorageInfo *, char *);
extern void plainFree(struct threadStorageInfo *);
extern void plainExpire(struct threadStorageInfo *);
extern int plainCookie(char *, int, struct threadStorageInfo *);
extern int plainInsert(char *, int, struct threadStorageInfo *);
extern int plainLogin(char *, char *, int, int, struct threadStorageInfo *);
extern int plainLogout(char *, int, struct threadStorageInfo *);
extern int plainSession(char *, char *, int, int, struct threadStorageInfo *);
extern int plainPermission(unsigned long long, char *, char *, char *, int, int, int, struct threadStorageInfo *);

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

// rand.c
extern int randRandom(int, struct timeval *);
extern unsigned long long randGetId(struct threadInfo *);

// reply.c
extern void replyPrepare(unsigned int, unsigned int, unsigned int, char *, struct threadInfo *);
extern void replyFree(struct threadInfo *);
extern char *replyThis(struct threadInfo *);

// shm.c
extern void shmCreate(int, int);
extern void shmRemove(int);
extern void shmUpdate(int, int);
extern void shmUsage(int);
extern void shmInfoMessage(char *, int);
extern void shmWarningMessage(char *, int);

// telskind.c
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

// worker_access.c
extern char *needLogin(struct threadInfo *);
extern char *needPerms(struct threadInfo *);
extern char *tryLogin(struct threadInfo *);
extern char *tryLogout(struct threadInfo *);
extern char *changeOwnPassword(struct threadInfo *);
extern char *changeUserPassword(struct threadInfo *);
extern char *isAuthLDAP(struct threadInfo *);
extern char *isUserAdmin(struct threadInfo *);
extern char *pullPrivilegeLevel(struct threadInfo *);
extern char *pullDomainPrivilegeLevel(struct threadInfo *);
extern char *newPrivilegeLevel(struct threadInfo *);
extern char *newDefaultPrivilegeLevel(struct threadInfo *);
extern char *pushPrivilegeLevel(struct threadInfo *);
extern char *pushDefaultPrivilegeLevel(struct threadInfo *);
extern char *checkDefaultPrivilegeLevel(struct threadInfo *);
extern char *deletePrivilegeLevel(struct threadInfo *);
extern char *fetchAccess(int, int, struct threadInfo *);

// worker_device.c
extern char *listDevice(struct threadInfo *);
extern char *pullDevice(struct threadInfo *);
extern char *newDevice(struct threadInfo *);
extern char *cloneDeviceAttachmentsForMachine(struct threadInfo *);
extern char *pushDevice(struct threadInfo *);
extern char *notePullDevice(struct threadInfo *);
extern char *notePullDeviceByID(struct threadInfo *);
extern char *noteAddDevice(struct threadInfo *);
extern char *noteModifyDevice(struct threadInfo *);
extern char *noteDeleteDevice(struct threadInfo *);
extern char *searchDevice(struct threadInfo *);
extern char *deleteDevice(struct threadInfo *);
extern char *restoreDevice(struct threadInfo *);
extern char *attachDevice(struct threadInfo *);
extern char *attachDomainDevice(struct threadInfo *);
extern char *attachGlobalDevice(struct threadInfo *);
extern char *attachDeviceToDevice(struct threadInfo *);
extern char *attachGlobalDeviceToDevice(struct threadInfo *);
extern char *attachDeviceToPeripheral(struct threadInfo *);
extern char *attachGlobalDeviceToPeripheral(struct threadInfo *);
extern char *removeDevice(struct threadInfo *);
extern char *removeDomainDevice(struct threadInfo *);
extern char *removeGlobalDevice(struct threadInfo *);
extern char *removeDeviceFromDevice(struct threadInfo *);
extern char *removeGlobalDeviceFromDevice(struct threadInfo *);
extern char *removeDeviceFromPeripheral(struct threadInfo *);
extern char *removeGlobalDeviceFromPeripheral(struct threadInfo *);
extern char *attachedDevice(struct threadInfo *);
extern char *attachedDeviceDevice(struct threadInfo *);
extern char *attachedDevicePeripheral(struct threadInfo *);
extern char *listDisposedDevice(struct threadInfo *);
extern char *fetchDevice(int, int, struct threadInfo *);

// worker_faction.c
extern char *listFaction(struct threadInfo *);
extern char *listMyFaction(struct threadInfo *);
extern char *pullFaction(struct threadInfo *);
extern char *newFaction(struct threadInfo *);
extern char *cloneFactionAttachmentsForMachine(struct threadInfo *);
extern char *pushFaction(struct threadInfo *);
extern char *searchFaction(struct threadInfo *);
extern char *deleteFaction(struct threadInfo *);
extern char *deleteTempFaction(struct threadInfo *);
extern char *attachFaction(struct threadInfo *);
extern char *attachDomainFaction(struct threadInfo *);
extern char *attachGlobalFaction(struct threadInfo *);
extern char *removeFaction(struct threadInfo *);
extern char *removeDomainFaction(struct threadInfo *);
extern char *removeGlobalFaction(struct threadInfo *);
extern char *attachedFaction(struct threadInfo *);
extern char *fetchFaction(int, int, struct threadInfo *);

// worker_file.c
extern char *listFile(struct threadInfo *);
extern char *listMyFile(struct threadInfo *);
extern char *pullFile(struct threadInfo *);
extern char *newFile(struct threadInfo *);
extern char *cloneFileAttachmentsForMachine(struct threadInfo *);
extern char *pushFile(struct threadInfo *);
extern char *searchFile(struct threadInfo *);
extern char *deleteFile(struct threadInfo *);
extern char *attachFile(struct threadInfo *);
extern char *attachDomainFile(struct threadInfo *);
extern char *attachGlobalFile(struct threadInfo *);
extern char *removeFile(struct threadInfo *);
extern char *removeDomainFile(struct threadInfo *);
extern char *removeGlobalFile(struct threadInfo *);
extern char *attachedFile(struct threadInfo *);
extern char *checkFile(struct threadInfo *);
extern char *fetchFile(int, int, struct threadInfo *);

// worker_help.c
extern char *listHelp(struct threadInfo *);
extern char *pullHelp(struct threadInfo *);
extern char *searchHelp(struct threadInfo *);
extern char *fetchHelp(int, int, struct threadInfo *);

// worker_log.c
extern char *listLog(struct threadInfo *);
extern char *pullLog(struct threadInfo *);
extern char *searchLog(struct threadInfo *);
extern char *listHistory(struct threadInfo *);
extern char *pullHistory(struct threadInfo *);
extern char *searchHistory(struct threadInfo *);
extern char *pullDatabaseStatus(struct threadInfo *);
extern char *pullDatabaseVariables(struct threadInfo *);
extern char *pullDatabaseErrors(struct threadInfo *);
extern char *pullDatabaseWarnings(struct threadInfo *);
extern char *pullDatabaseTablestatus(struct threadInfo *);
extern char *listSession(struct threadInfo *);
extern char *fetchLog(int, int, struct threadInfo *);

// worker_machine.c
extern char *listMachine(struct threadInfo *);
extern char *pullMachine(struct threadInfo *);
extern char *pullMachineByID(struct threadInfo *);
extern char *newMachine(struct threadInfo *);
extern char *cloneMachine(struct threadInfo *);
extern char *pushMachine(struct threadInfo *);
extern char *notePullMachine(struct threadInfo *);
extern char *notePullMachineByID(struct threadInfo *);
extern char *noteAddMachine(struct threadInfo *);
extern char *noteModifyMachine(struct threadInfo *);
extern char *noteDeleteMachine(struct threadInfo *);
extern char *searchMachine(struct threadInfo *);
extern char *deleteMachine(struct threadInfo *);
extern char *listDisposedMachine(struct threadInfo *);
extern char *restoreDisposedMachine(struct threadInfo *);
extern char *pullDisposedMachine(struct threadInfo *);
extern char *pullDisposedMachineByID(struct threadInfo *);
extern char *pushDisposedMachine(struct threadInfo *);
extern char *searchDisposedMachine(struct threadInfo *);
extern char *deleteDisposedMachine(struct threadInfo *);
extern char *fetchMachine(int, int, struct threadInfo *);

// worker_misc.c
extern char *pullMisc(struct threadInfo *);
extern char *fetchMisc(int, int, struct threadInfo *);

// worker_password.c
extern char *listPassword(struct threadInfo *);
extern char *listMyPassword(struct threadInfo *);
extern char *pullPassword(struct threadInfo *);
extern char *newPassword(struct threadInfo *);
extern char *clonePasswordAttachmentsForMachine(struct threadInfo *);
extern char *pushPassword(struct threadInfo *);
extern char *encryptPassword(struct threadInfo *);
extern char *decryptPassword(struct threadInfo *);
extern char *searchPassword(struct threadInfo *);
extern char *deletePassword(struct threadInfo *);
extern char *attachPassword(struct threadInfo *);
extern char *attachDomainPassword(struct threadInfo *);
extern char *attachGlobalPassword(struct threadInfo *);
extern char *removePassword(struct threadInfo *);
extern char *removeDomainPassword(struct threadInfo *);
extern char *removeGlobalPassword(struct threadInfo *);
extern char *attachedPassword(struct threadInfo *);
extern char *fetchPassword(int, int, struct threadInfo *);

// worker_peripheral.c
extern char *listPeripheral(struct threadInfo *);
extern char *pullPeripheral(struct threadInfo *);
extern char *newPeripheral(struct threadInfo *);
extern char *clonePeripheralAttachmentsForMachine(struct threadInfo *);
extern char *pushPeripheral(struct threadInfo *);
extern char *notePullPeripheral(struct threadInfo *);
extern char *notePullPeripheralByID(struct threadInfo *);
extern char *noteAddPeripheral(struct threadInfo *);
extern char *noteModifyPeripheral(struct threadInfo *);
extern char *noteDeletePeripheral(struct threadInfo *);
extern char *searchPeripheral(struct threadInfo *);
extern char *deletePeripheral(struct threadInfo *);
extern char *restorePeripheral(struct threadInfo *);
extern char *attachPeripheral(struct threadInfo *);
extern char *attachDomainPeripheral(struct threadInfo *);
extern char *attachGlobalPeripheral(struct threadInfo *);
extern char *attachPeripheralToDevice(struct threadInfo *);
extern char *attachGlobalPeripheralToDevice(struct threadInfo *);
extern char *attachPeripheralToPeripheral(struct threadInfo *);
extern char *attachGlobalPeripheralToPeripheral(struct threadInfo *);
extern char *removePeripheral(struct threadInfo *);
extern char *removeDomainPeripheral(struct threadInfo *);
extern char *removeGlobalPeripheral(struct threadInfo *);
extern char *removePeripheralFromDevice(struct threadInfo *);
extern char *removeGlobalPeripheralFromDevice(struct threadInfo *);
extern char *removePeripheralFromPeripheral(struct threadInfo *);
extern char *removeGlobalPeripheralFromPeripheral(struct threadInfo *);
extern char *attachedPeripheral(struct threadInfo *);
extern char *attachedPeripheralDevice(struct threadInfo *);
extern char *attachedPeripheralPeripheral(struct threadInfo *);
extern char *listDisposedPeripheral(struct threadInfo *);
extern char *fetchPeripheral(int, int, struct threadInfo *);

// worker_port.c
extern char *listTCP(struct threadInfo *);
extern char *listUDP(struct threadInfo *);
extern char *pullTCP(struct threadInfo *);
extern char *pullUDP(struct threadInfo *);
extern char *searchTCP(struct threadInfo *);
extern char *searchUDP(struct threadInfo *);
extern char *fetchTCP(int, int, struct threadInfo *);
extern char *fetchUDP(int, int, struct threadInfo *);

// worker_rgb.c
extern char *listRGB(struct threadInfo *);
extern char *pullRGB(struct threadInfo *);
extern char *searchRGB(struct threadInfo *);
extern char *fetchRGB(int, int, struct threadInfo *);

// worker_service.c
extern char *listService(struct threadInfo *);
extern char *listProvider(struct threadInfo *);
extern char *pullService(struct threadInfo *);
extern char *pullProvider(struct threadInfo *);
extern char *newService(struct threadInfo *);
extern char *newProvider(struct threadInfo *);
extern char *cloneProviderAttachmentsForMachine(struct threadInfo *);
extern char *pushService(struct threadInfo *);
extern char *pushProvider(struct threadInfo *);
extern char *notePullProvider(struct threadInfo *);
extern char *notePullProviderByID(struct threadInfo *);
extern char *noteAddProvider(struct threadInfo *);
extern char *noteModifyProvider(struct threadInfo *);
extern char *noteDeleteProvider(struct threadInfo *);
extern char *searchService(struct threadInfo *);
extern char *searchProvider(struct threadInfo *);
extern char *deleteService(struct threadInfo *);
extern char *deleteProvider(struct threadInfo *);
extern char *restoreService(struct threadInfo *);
extern char *restoreProvider(struct threadInfo *);
extern char *attachProvider(struct threadInfo *);
extern char *attachDomainProvider(struct threadInfo *);
extern char *attachGlobalProvider(struct threadInfo *);
extern char *removeProvider(struct threadInfo *);
extern char *removeDomainProvider(struct threadInfo *);
extern char *removeGlobalProvider(struct threadInfo *);
extern char *attachedProvider(struct threadInfo *);
extern char *attachedProviderProvider(struct threadInfo *);
extern char *listDisposedService(struct threadInfo *);
extern char *listDisposedProvider(struct threadInfo *);
extern char *fetchService(int, int, struct threadInfo *);
extern char *fetchProvider(int, int, struct threadInfo *);

// worker_skinuser.c
extern char *listUser(struct threadInfo *);
extern char *pullUser(struct threadInfo *);
extern char *searchUser(struct threadInfo *);
extern char *newUser(struct threadInfo *);
extern char *pushOwnUser(struct threadInfo *);
extern char *pushUserUser(struct threadInfo *);
extern char *deleteUser(struct threadInfo *);
extern char *fetchUser(int, int, struct threadInfo *);

// worker_temp.c
extern char *pullTemp(struct threadInfo *);
extern char *pushTemp(struct threadInfo *);
extern char *fetchTemp(int, int, struct threadInfo *);
