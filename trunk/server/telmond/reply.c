#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "declarations.h"
#include "defines.h"



char *replyChartConns(struct threadInfo * ti) {
	return(ti->itemSpace);
}

char *replyHistoryDate(struct threadInfo * ti) {
	return(ti->storageInfo.replyBuffer);
}

char *replyWorkersAvailable(struct threadInfo * ti) {
	snprintf(ti->itemSpace, sizeof(ti->itemSpace), "%llu%c", ti->daemonInfo.workersAvailable, 0);

	return(ti->itemSpace);
}

char *replyServerStarted(struct threadInfo * ti) {
	ti->itemSpace[0] = 0;

	ti->timeNow = localtime((time_t *) &ti->daemonInfo.serverStarted);

	strftime(ti->itemSpace, sizeof(ti->itemSpace), TIME_FORMAT, ti->timeNow);

	return(ti->itemSpace);
}

char *replyLastTask(struct threadInfo * ti) {
	ti->itemSpace[0] = 0;

	ti->timeNow = localtime((time_t *) &ti->daemonInfo.lastTask);

	strftime(ti->itemSpace, sizeof(ti->itemSpace), TIME_FORMAT, ti->timeNow);

	return(ti->itemSpace);
}

char *replyTotalTasks(struct threadInfo * ti) {
	snprintf(ti->itemSpace, sizeof(ti->itemSpace), "%llu%c", ti->daemonInfo.totalTasks, 0);

	return(ti->itemSpace);
}

char *replyInfoTime(struct threadInfo * ti) {
	ti->itemSpace[0] = 0;

	ti->timeNow = localtime((time_t *) &ti->daemonInfo.infoTime);

	strftime(ti->itemSpace, sizeof(ti->itemSpace), TIME_FORMAT, ti->timeNow);

	return(ti->itemSpace);
}

char *replyWarnTime(struct threadInfo * ti) {
	ti->itemSpace[0] = 0;

	ti->timeNow = localtime((time_t *) &ti->daemonInfo.errorTime);

	strftime(ti->itemSpace, sizeof(ti->itemSpace), TIME_FORMAT, ti->timeNow);

	return(ti->itemSpace);
}

char *replyInfoMessage(struct threadInfo * ti) {
	return(ti->daemonInfo.infoMessage);
}

char *replyWarnMessage(struct threadInfo * ti) {
	return(ti->daemonInfo.errorMessage);
}
