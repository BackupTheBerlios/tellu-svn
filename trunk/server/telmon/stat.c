#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *statChart(struct mainInfo * mi) {
	char thisServer[CONFIG_SPACE_SIZE];

	switch(mi->setServer) {
		case DAEMON_TELLUD:
			snprintf(thisServer, sizeof(thisServer), "%s%c", TITLE_MENU_SERVER_OPTION_1, 0);

			break;
		case DAEMON_TELMOND:
			snprintf(thisServer, sizeof(thisServer), "%s%c", TITLE_MENU_SERVER_OPTION_2, 0);

			break;
		case DAEMON_TELSKIND:
			snprintf(thisServer, sizeof(thisServer), "%s%c", TITLE_MENU_SERVER_OPTION_3, 0);

			break;
		default:
			return(NULL);

			break;
	}

	snprintf(
		mi->chartServer,
		sizeof(mi->chartServer),
		"%s proc = '%s' AND DAYNAME(time) = '%s' AND DAY(time) = '%s' AND MONTHNAME(time) = '%s' AND YEAR(time) = '%s'%c",
		STAT_HISTORY_CHART,
		thisServer,
		mi->hstArrays[mi->hstDaysFetch].dayname,
		mi->hstArrays[mi->hstDaysFetch].daynum,
		mi->hstArrays[mi->hstDaysFetch].monthname,
		mi->hstArrays[mi->hstDaysFetch].yearnum,
		0
	);

	return(mi->chartServer);
}

char *statHistory(struct mainInfo * mi) {
	return(STAT_HISTORY_DAYS);
}

char *statMonitor(struct mainInfo * mi) {
	return(mi->statThis);
}
