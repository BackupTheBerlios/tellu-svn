#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "defines.h"
#include "image.h"



int imageSave(FILE *imageFile, int imageWidth, int imageHeight, unsigned short imageDepth, char *imageData) {
	int newDepth;

	imageFileHeader newImageFileHeader;
	imageInfoHeader newImageInfoHeader;

	switch(imageDepth) {
		case 128:
			newDepth = 16;

			break;
		case 96:
			newDepth = 12;

			break;
		case 64:
			newDepth = 8;

			break;
		case 48:
			newDepth = 6;

			break;
		case 32:
			newDepth = 4;

			break;
		case 24:
			newDepth = 3;

			break;
		case 16:
			newDepth = 2;

			break;
		case 8:
		case 4:
		case 2:
		case 1:
		default:
			newDepth = 1;

			break;
	}

	newImageFileHeader.bfType = 0x4d42;
	newImageFileHeader.bfSize = (sizeof(newImageFileHeader) + sizeof(newImageInfoHeader) + (imageWidth * imageHeight * newDepth)) - sizeof(newImageFileHeader.bfType);
	newImageFileHeader.bfReserved1 = 0;
	newImageFileHeader.bfReserved2 = 0;
	newImageFileHeader.bfOffset = (sizeof(newImageFileHeader) + sizeof(newImageInfoHeader)) - sizeof(newImageFileHeader.bfType);

	newImageInfoHeader.biSize = sizeof(newImageInfoHeader);
	newImageInfoHeader.biWidth = imageWidth;
	newImageInfoHeader.biHeight = -(imageHeight);
	newImageInfoHeader.biPlanes = 1;
	newImageInfoHeader.biBits = imageDepth;
	newImageInfoHeader.biCompression = 0;
	newImageInfoHeader.biImageSize = imageWidth * imageHeight * newDepth;
	newImageInfoHeader.biXRes = 0;
	newImageInfoHeader.biYRes = 0;
	newImageInfoHeader.biNumberOfColors = 0; 
	newImageInfoHeader.biImportantColors = 0;

	imageWriteByte(imageFile, newImageFileHeader.bfType);
	imageWriteWord(imageFile, newImageFileHeader.bfSize);
	imageWriteByte(imageFile, newImageFileHeader.bfReserved1);
	imageWriteByte(imageFile, newImageFileHeader.bfReserved2);
	imageWriteWord(imageFile, newImageFileHeader.bfOffset);

	imageWriteWord(imageFile, newImageInfoHeader.biSize);
	imageWriteLongword(imageFile, newImageInfoHeader.biWidth);
	imageWriteLongword(imageFile, newImageInfoHeader.biHeight);
	imageWriteByte(imageFile, newImageInfoHeader.biPlanes);
	imageWriteByte(imageFile, newImageInfoHeader.biBits);
	imageWriteWord(imageFile, newImageInfoHeader.biCompression);
	imageWriteWord(imageFile, newImageInfoHeader.biImageSize);
	imageWriteLongword(imageFile, newImageInfoHeader.biXRes);
	imageWriteLongword(imageFile, newImageInfoHeader.biYRes);
	imageWriteWord(imageFile, newImageInfoHeader.biNumberOfColors);
	imageWriteWord(imageFile, newImageInfoHeader.biImportantColors);

	if(imageWidth > 0 && imageHeight > 0) {
		if(fwrite(imageData, imageWidth * imageHeight * newDepth, 1, imageFile) < 1) {
			return(-1);
		}
	}

	return(0);
}

unsigned short imageReadByte(FILE *imageFile) {
	unsigned char ba, bb;

	ba = getc(imageFile);
	bb = getc(imageFile);

	return((bb << 8) | ba);
}

unsigned int imageReadWord(FILE *imageFile) {
	unsigned char ba, bb, bc, bd;

	ba = getc(imageFile);
	bb = getc(imageFile);
	bc = getc(imageFile);
	bd = getc(imageFile);

	return(((((bd << 8) | bc) << 8) | bb) << 8 | ba);
}

int imageReadLongword(FILE *imageFile) {
	unsigned char ba, bb, bc, bd;

	ba = getc(imageFile);
	bb = getc(imageFile);
	bc = getc(imageFile);
	bd = getc(imageFile);

	return((int) ((((bd << 8) | bc) << 8) | bb) << 8 | ba);
}

void imageWriteByte(FILE *imageFile, unsigned short writeThis) {
	putc(writeThis, imageFile);
	putc(writeThis >> 8, imageFile);
}

void imageWriteWord(FILE *imageFile, unsigned int writeThis) {
	putc(writeThis, imageFile);
	putc(writeThis >> 8, imageFile);
	putc(writeThis >> 16, imageFile);
	putc(writeThis >> 24, imageFile);
}

void imageWriteLongword(FILE *imageFile, int writeThis) {
	putc(writeThis, imageFile);
	putc(writeThis >> 8, imageFile);
	putc(writeThis >> 16, imageFile);
	putc(writeThis >> 24, imageFile);
}
