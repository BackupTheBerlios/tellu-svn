#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



int uidSwitch(uid_t newUid) {
	if(setuid(newUid) != 0) {
		return(-1);
	}

	return(0);
}

int gidSwitch(gid_t newGid) {
	if(setgid(newGid) != 0) {
		return(-1);
	}

	return(0);
}
