struct cmdArray {
	char *task;
	void (*constructor)(struct paramInfo *);
	char *(*allocator)(struct paramInfo *);
	void (*destroyer)(char *);
};

struct cmdArray cmdArrays[] = {
	{ "appn", NULL, appGetName, NULL },
	{ "appv", NULL, appGetVersion, NULL },
	{ "type", NULL, appGetDataPacket, NULL },
	{ "mach", NULL, machGetInfo, machFreeInfo },
	{ "user", NULL, userGetInfo, userFreeInfo },
	{ "load", NULL, loadGetLoad, loadFreeLoad },
	{ "cpus", NULL, cpuGetProcessor, cpuFreeProcessor },
	{ "mems", NULL, memGetMemory, memFreeMemory },
	{ "disk", NULL, diskGetMounted, diskFreeMounted },
	{ "nics", NULL, netGetInterfaceData, netFreeInterfaceData },
	{ "devs", NULL, halGetDevices, halFreeDevices },
	{ "runs", NULL, servGetCount, servFreeCount },
	{ "proc", NULL, servGetProcesses, servFreeProcesses },
	{ "serv", NULL, servGetServices, servFreeServices },
	{ "port", netInitOpenPorts, netGetOpenPorts, netFreeOpenPorts },
	{ "soft", NULL, softGetInstalled, softFreeInstalled },
	{ "syst", NULL, sysGetSystem, sysFreeSystem },
	{ "term", NULL, termNull, NULL },
	{ NULL, NULL, NULL, NULL }
};
