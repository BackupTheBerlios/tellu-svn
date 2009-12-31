#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>

#if defined(__linux__)
#include <mntent.h>
#endif

#include "declarations.h"



char *diskGetMounted(struct paramInfo * pi) {
#if defined(__linux__)
	int k;
	unsigned long sysMultiplier;
	unsigned long long sysSize, sysFree, sysSerial;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	FILE *newFile;

	struct statvfs newStat;
	struct mntent *newEntry;

	if((newFile = setmntent(DISK_GENERAL, "r")) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");

		return(NULL);
	}

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		endmntent(newFile);

		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

		return(NULL);
	}

	k = 0;

	while((newEntry = getmntent(newFile)) != NULL) {
		if(newEntry->mnt_fsname == NULL || newEntry->mnt_dir == NULL || newEntry->mnt_type == NULL || newEntry->mnt_opts == NULL) {
			continue;
		}

		sysSize = 0;
		sysFree = 0;
		sysSerial = 0;

		memset(&newStat, 0, sizeof(newStat));

		if(statvfs(newEntry->mnt_dir, &newStat) == 0) {
			sysMultiplier = 0;

			if(newStat.f_bsize > 0) {
				sysMultiplier = newStat.f_bsize;
			}

			sysSize = (newStat.f_blocks * sysMultiplier) / 1000;
			sysFree = (newStat.f_bfree * sysMultiplier) / 1000;
			sysSerial = newStat.f_fsid;
		}

		newBufcur = strlen(newEntry->mnt_fsname) + strlen(newEntry->mnt_dir) + strlen(newEntry->mnt_type) + strlen(newEntry->mnt_opts) + sizeof(long long) + sizeof(long long) + sizeof(long long) + 64;

		if(newBuflen - newBuffil <= newBufcur) {
			newBuflen += DATA_BLOCK_SIZE;

			if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
				free(newBuffer);

				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

				return(NULL);
			}

			newBuffer = tmpBuffer;
		}

		k += snprintf(newBuffer + k, newBuflen, "%s%c%s%c%s%c%s%c%llu%c%llu%c%.16llx%c", newEntry->mnt_fsname, ITEM_SEPARATOR, newEntry->mnt_dir, ITEM_SEPARATOR, newEntry->mnt_type, ITEM_SEPARATOR, newEntry->mnt_opts, ITEM_SEPARATOR, sysSize, ITEM_SEPARATOR, sysFree, ITEM_SEPARATOR, sysSerial, ITEM_DELIMITER);

		newBuffil += newBufcur;
	}

	endmntent(newFile);

	if(k > 0) {
		k--;
	}

	newBuffer[k] = 0;

	return(newBuffer);
#else
	return(NULL);
#endif
}

void diskFreeMounted(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
