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
