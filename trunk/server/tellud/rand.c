#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "declarations.h"
#include "defines.h"



unsigned long long randGetId(struct threadInfo * ti) {
	if(gettimeofday(&ti->timeVal, NULL) != 0) {
		return(0);
	}

	srand(ti->timeVal.tv_usec);

	ti->c = (unsigned char *) &ti->v;
	ti->d = (unsigned char *) &ti->w;

	ti->w = (unsigned long long) 0;
	ti->v = (unsigned long long) ti->timeVal.tv_sec;

	ti->d[4] = ti->c[0];
	ti->d[5] = ti->c[1];
	ti->d[6] = ti->c[2];
	ti->d[7] = ti->c[3];

	ti->w |= rand() % 65536;

	return(ti->w);
}
