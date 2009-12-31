#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"
#include "jip.h"



int jipDeflate(unsigned char *fileInput, unsigned char *fileOutput, struct threadCompressInfo * ci, unsigned int fileSize) {
	if((ci->jipAppend = malloc(JIP_TBSIZE * sizeof(unsigned char))) == NULL) {
		return(-1);
	}

	if((ci->jipPrefix = malloc(JIP_TBSIZE * sizeof(unsigned int))) == NULL) {
		free(ci->jipAppend);

		return(-1);
	}

	memset(&ci->jipDecode, 0, sizeof(ci->jipDecode));

	ci->jipBitBuffer = 0;
	ci->jipBitCount = 0;
	ci->jipInput = DATA_COOKIE_SIZE;
	ci->jipOutput = DATA_COOKIE_SIZE;

	ci->x = 256;

	ci->o = jipIn(fileInput, ci);

	ci->n = ci->o;

	fileOutput[ci->jipOutput++] = ci->o;

	while(ci->jipInput <= fileSize) {
		ci->w = jipIn(fileInput, ci);

		if(ci->w >= ci->x) {
			*ci->jipDecode = ci->n;

			ci->jipString = jipDecode(ci->jipDecode + 1, ci->o, ci);
		}
		else {
			ci->jipString = jipDecode(ci->jipDecode, ci->w, ci);
		}

		ci->n = *ci->jipString;

		while(ci->jipString >= ci->jipDecode) {
			fileOutput[ci->jipOutput++] = *ci->jipString--;
		}

		if(ci->x <= JIP_MAXCOD) {
			ci->jipPrefix[ci->x] = ci->o;
			ci->jipAppend[ci->x++] = ci->n;
		}

		ci->o = ci->w;
	}

	free(ci->jipAppend);
	free(ci->jipPrefix);

	return(0);
}

int jipIn(unsigned char *fileInput, struct threadCompressInfo * ci) {
	while(ci->jipBitCount <= 24) {
		ci->jipBitBuffer |= (unsigned int) fileInput[ci->jipInput++] << (24 - ci->jipBitCount);
		ci->jipBitCount += 8;
	}

	ci->i = ci->jipBitBuffer >> (32 - JIP_CCBITS);

	ci->jipBitBuffer <<= JIP_CCBITS;
	ci->jipBitCount -= JIP_CCBITS;

	return(ci->i);
}

unsigned char *jipDecode(unsigned char *fileBuffer, unsigned int fileCode, struct threadCompressInfo * ci) {
	ci->i = 0;

	while(fileCode > 255) {
		*fileBuffer++ = ci->jipAppend[fileCode];

		fileCode = ci->jipPrefix[fileCode];

		if(ci->i++ >= 4094) {
			return(NULL);
		}
	}

	*fileBuffer = fileCode;

	return(fileBuffer);
}
