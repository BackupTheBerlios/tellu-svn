#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "declarations.h"
#include "defines.h"



int randRandom(int maxVal, struct timeval * tv) {
	if(gettimeofday(tv, NULL) == 0) {
		srand(tv->tv_usec);
	}
	else {
		srand(rand());
	}

	return(rand() % maxVal);
}

unsigned long long randGetId(struct threadInfo * ti) {
	if(gettimeofday(&ti->timeVal, NULL) != 0) {
		return(0);
	}

	srand(ti->timeVal.tv_usec);

	ti->cc = (unsigned char *) &ti->v;
	ti->dd = (unsigned char *) &ti->w;

	ti->w = (unsigned long long) 0;
	ti->v = (unsigned long long) ti->timeVal.tv_sec;

	ti->dd[4] = ti->cc[0];
	ti->dd[5] = ti->cc[1];
	ti->dd[6] = ti->cc[2];
	ti->dd[7] = ti->cc[3];

	ti->w |= rand() % 65536;

	return(ti->w);
}
