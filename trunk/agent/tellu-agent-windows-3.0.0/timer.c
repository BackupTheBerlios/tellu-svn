#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



void timerWait(unsigned int reqSeconds) {
	Sleep(reqSeconds);
}
