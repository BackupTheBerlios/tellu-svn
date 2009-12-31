#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



char *appGetName(struct paramInfo * pi) {
	return(APPLICATION_NAME);
}

char *appGetVersion(struct paramInfo * pi) {
	return(APPLICATION_VERSION);
}

char *appGetDataPacket(struct paramInfo * pi) {
	return(DATA_PACKET_COLLECT);
}
