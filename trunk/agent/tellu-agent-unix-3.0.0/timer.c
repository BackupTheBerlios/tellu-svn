#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "declarations.h"



void timerWait(unsigned int reqSeconds, useconds_t reqMicroSeconds) {
	int tmpSeconds;

	if(reqSeconds > 0) {
		while(1) {
			tmpSeconds = sleep(reqSeconds);

			if(tmpSeconds == 0) {
				break;
			}

			reqSeconds = tmpSeconds;
		}
	}

	if(reqMicroSeconds > 0 && reqMicroSeconds < 1000000) {
		usleep(reqMicroSeconds);
	}
}
