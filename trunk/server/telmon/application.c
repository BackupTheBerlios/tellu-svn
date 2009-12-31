#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"



char *appGetName(struct mainInfo * mi) {
	return(APPLICATION_NAME);
}

char *appGetVersion(struct mainInfo * mi) {
	return(APPLICATION_VERSION);
}

char *appGetDataPacket(struct mainInfo * mi) {
	return(DATA_PACKET_COLLECT);
}
