#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "jip.h"



int jipCompress(unsigned char *fileInput, unsigned char *fileOutput, unsigned int fileSize) {
	unsigned int i;
	unsigned int c, d, f, x;

	if((jipAppend = malloc(JIP_TBSIZE * sizeof(unsigned char))) == NULL) {
		return(0);
	}

	if((jipCoded = malloc(JIP_TBSIZE * sizeof(unsigned int))) == NULL) {
		free(jipAppend);

		return(0);
	}

	if((jipPrefix = malloc(JIP_TBSIZE * sizeof(unsigned int))) == NULL) {
		free(jipAppend);
		free(jipCoded);

		return(0);
	}

	for(i = 0; i < JIP_TBSIZE; i++) {
		jipCoded[i] = -1;
	}

	jipInput = 0;
	jipOutput = 0;
	jipBitCount = 0;

	x = 256;

	f = fileInput[jipInput++];

	for(i = 0; i < fileSize; i++) {
		c = fileInput[jipInput++];

		d = jipFind(f, c);

		if(jipCoded[d] != -1) {
			f = jipCoded[d];
		}
		else {
			if(x <= JIP_MAXCOD) {
				jipAppend[d] = c;
				jipPrefix[d] = f;
				jipCoded[d] = x++;
			}

			jipOut(fileOutput, f);

			f = c;
		}
	}

	jipOut(fileOutput, f);

	free(jipAppend);
	free(jipCoded);
	free(jipPrefix);

	return(jipOutput);
}

int jipFind(int fileFirst, unsigned int fileChar) {
	int i, o;

	i = (fileChar << (JIP_CCBITS - 8)) ^ fileFirst;

	if(i == 0) {
		o = 1;
	}
	else {
		o = JIP_TBSIZE - i;
	}

	while(1) {
		if(jipCoded[i] == -1) {
			return(i);
		}

		if(jipPrefix[i] == fileFirst && jipAppend[i] == fileChar) {
			return(i);
		}

		i -= o;

		if(i < 0) {
			i += JIP_TBSIZE;
		}
	}
}

void jipOut(unsigned char *fileOutput, unsigned int fileCode) {
	unsigned char i;
	static unsigned long newBitBuffer = 0;

	newBitBuffer |= (unsigned long) fileCode << (32 - JIP_CCBITS - jipBitCount);
	jipBitCount += JIP_CCBITS;

	while(jipBitCount >= 8) {
		i = newBitBuffer >> 24;
		fileOutput[jipOutput++] = i;

		newBitBuffer <<= 8;
		jipBitCount -= 8;
	}
}
