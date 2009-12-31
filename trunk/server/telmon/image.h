unsigned short imageReadByte(FILE *);
unsigned int imageReadWord(FILE *);
int imageReadLongword(FILE *);
void imageWriteByte(FILE *, unsigned short);
void imageWriteWord(FILE *, unsigned int);
void imageWriteLongword(FILE *, int);

typedef struct {
	unsigned short bfType;							// Magic identifier
	unsigned int bfSize;							// File size in bytes
	unsigned short bfReserved1;						// Reserved
	unsigned short bfReserved2;						// Reserved
	unsigned int bfOffset;							// Offset to image data
} imageFileHeader;

typedef struct {
	unsigned int biSize;							// Header size in bytes
	int biWidth;								// Image width
	int biHeight;								// Image height
	unsigned short biPlanes;						// Number of color planes
	unsigned short biBits;							// Bits per pixel
	unsigned int biCompression;						// Compression type
	unsigned int biImageSize;						// Image size in bytes
	int biXRes;								// Pixels per meter
	int biYRes;								// Pixels per meter
	unsigned int biNumberOfColors;						// Number of colors
	unsigned int biImportantColors;						// Number of important colors
} imageInfoHeader;
