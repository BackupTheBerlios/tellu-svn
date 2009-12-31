struct cmdArray chartArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "stat", statChart, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};

struct cmdArray historyArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "stat", statHistory, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};

struct cmdArray monitorArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "stat", statMonitor, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};
