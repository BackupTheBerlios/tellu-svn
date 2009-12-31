#include <unistd.h>
#include <dbus/dbus.h>
#include <hal/libhal.h>

#include "defines.h"
#include "param.h"



// application.c
extern char *appGetName(struct paramInfo *);
extern char *appGetVersion(struct paramInfo *);
extern char *appGetDataPacket(struct paramInfo *);

// config.c
extern int config(char *);
extern void *configFetch(char *);

// disk.c
extern char *diskGetMounted(struct paramInfo *);
extern void diskFreeMounted(char *);

// hal.c
extern int halFetchInit(void);
extern void halFetchFree(void);
extern struct halStore *halFetchItem(int);
extern char *halGetDevices(struct paramInfo *);
extern void halFreeDevices(char *);

// jip.c
extern int jipCompress(unsigned char *, unsigned char *, unsigned int);

// load.c
extern char *loadGetLoad(struct paramInfo *);
extern void loadFreeLoad(char *);

// machine.c
extern char *machGetInfo(struct paramInfo *);
extern void machFreeInfo(char *);

// memory.c
extern char *memGetMemory(struct paramInfo *);
extern void memFreeMemory(char *);

// message.c
extern void dbusMessage(int, char *, DBusError *);
extern void infoMessage(int, char *);
extern void warningMessage(int, char *);

// network.c
extern char *netGetInterfaceData(struct paramInfo *);
extern void netFreeInterfaceData(char *);
extern void netInitOpenPorts(struct paramInfo *);
extern char *netGetOpenPorts(struct paramInfo *);
extern void netFreeOpenPorts(char *);
extern void netSendPacket(char *, size_t);

// node.c
extern void nodeInitNames(void);
extern char *nodeFetchNode(void);
extern char *nodeFetchDomain(void);
extern char *nodeFetchSystem(void);
extern char *nodeFetchRelease(void);
extern char *nodeFetchDistribution(void);
extern char *nodeFetchMachine(void);
extern char *nodeFetchUserLogin(void);
extern char *nodeFetchUserName(void);
extern char *nodeFetchUserHome(void);
extern char *nodeFetchUserGroup(void);

// processor.c
extern char *cpuGetProcessor(struct paramInfo *);
extern void cpuFreeProcessor(char *);

// services.c
extern char *servGetCount(struct paramInfo *);
extern void servFreeCount(char *);
extern char *servGetProcesses(struct paramInfo *);
extern void servFreeProcesses(char *);
extern char *servGetServices(struct paramInfo *);
extern void servFreeServices(char *);

// software.c
extern char *softGetInstalled(struct paramInfo *);
extern void softFreeInstalled(char *);

// system.c
extern int sysFetchInit(void);
extern void sysFetchFree(void);
extern void sysFetchItem(struct sysInfo *, int);
extern char *sysGetSystem(struct paramInfo *);
extern void sysFreeSystem(char *);

// terminate.c
extern char *termNull(struct paramInfo *);

// timer.c
extern void timerWait(unsigned int, useconds_t);

// user.c
extern char *userGetInfo(struct paramInfo *);
extern void userFreeInfo(char *);
