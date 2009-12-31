#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *appGetName(struct threadInfo * ti) {
	return(APPLICATION_NAME);
}

char *appGetVersion(struct threadInfo * ti) {
	return(APPLICATION_VERSION);
}

char *appGetDataPacket(struct threadInfo * ti) {
	return(DATA_PACKET_COLLECT);
}
