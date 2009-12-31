struct cmdArray chartArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "conn", replyChartConns, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};

struct cmdArray historyArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "date", replyHistoryDate, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};

struct cmdArray monitorArrays[] = {
	{ "appn", appGetName, NULL },
	{ "appv", appGetVersion, NULL },
	{ "type", appGetDataPacket, NULL },
	{ "work", replyWorkersAvailable, NULL },
	{ "strt", replyServerStarted, NULL },
	{ "task", replyLastTask, NULL },
	{ "totl", replyTotalTasks, NULL },
	{ "time", replyInfoTime, NULL },
	{ "time", replyWarnTime, NULL },
	{ "info", replyInfoMessage, NULL },
	{ "warn", replyWarnMessage, NULL },
	{ "term", termNull, NULL },
	{ NULL, NULL, NULL }
};
