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
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file '" DISK_GENERAL "' for reading");

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

			if(newStat.f_frsize > 0) {
				sysMultiplier = newStat.f_frsize;
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
#elif defined(__NetBSD__)
	int i, j, k, l, m;
	unsigned long f, g;
	unsigned long sysMultiplier;
	unsigned long long sysSize, sysFree, sysSerial;

	char *newBuffer, *tmpBuffer;
	char newOptions[CONFIG_SPACE_SIZE];

	size_t newBuflen, newBufcur, newBuffil;

	struct statvfs *newStat;

	unsigned long newFlags[] = {
		0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00008000, 0x00100000, 0x02000000,
		0x04000000, 0x20000000, 0x40000000, 0x80000000, 0x00000080, 0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x08000000,
		0x10000000, 0x00001000, 0x00002000, 0x00004000, 0x00010000, 0x00040000, 0x00080000, 0x00400000,
		-1
	};

	char *newClags[] = {
		"read-only", "synchronous", "noexec", "nosuid", "nodev", "union", "asynchronous", "nocoredump", "hidden", "log",
		"noatime", "symperm", "nodevmtime", "soft dependencies", "exported read-only", "NFS exported", "exported to the world",
		"anon uid mapping", "kerberos uid mapping", "on-reserved ports", "WebNFS exports", "local", "with quotas", "root file system",
		"being updated", "reload filesystem data", "force unmount or readonly change", "retrieve mount arguments"
	};

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

		return(NULL);
	}

	k = 0;

	if((j = getmntinfo(&newStat, ST_NOWAIT)) != 0) {
		for(i = 0; i < j; i++) {
			if(newStat[i].f_mntfromname[0] == 0 || newStat[i].f_mntonname[0] == 0 || newStat[i].f_fstypename[0] == 0) {
				continue;
			}

			newBufcur = strlen(newStat[i].f_mntfromname) + strlen(newStat[i].f_mntonname) + strlen(newStat[i].f_fstypename) + 64;

			if(newBuflen - newBuffil <= newBufcur) {
				newBuflen += DATA_BLOCK_SIZE;

				if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
					free(newBuffer);

					warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

					return(NULL);
				}

				newBuffer = tmpBuffer;
			}

			sysSize = 0;
			sysFree = 0;
			sysSerial = 0;

			sysMultiplier = 0;

			if(newStat[i].f_frsize > 0) {
				sysMultiplier = newStat[i].f_frsize;
			}

			sysSize = (newStat[i].f_blocks * sysMultiplier) / 1000;
			sysFree = (newStat[i].f_bfree * sysMultiplier) / 1000;
			sysSerial = newStat[i].f_fsid;

			memset(newOptions, 0, sizeof(newOptions));

			g = 1;

			for(l = 0; l < sizeof(unsigned long) * 8; l++) {
				f = newStat[i].f_flag;
				f &= g;

				for(m = 0; ; m++) {
					if(newFlags[m] == -1) {
						break;
					}

					if(newFlags[m] == f) {
						snprintf(newOptions + strlen(newOptions), sizeof(newOptions), "%s,%c", newClags[m], 0);
					}
				}

				g <<= 1;
			}

			if(strlen(newOptions) > 0) {
				if(newOptions[strlen(newOptions) - 1] == ',') {
					newOptions[strlen(newOptions) - 1] = 0;
				}
			}

			k += snprintf(newBuffer + k, newBuflen, "%s%c%s%c%s%c%s%c%llu%c%llu%c%.16llx%c", newStat[i].f_mntfromname, ITEM_SEPARATOR, newStat[i].f_mntonname, ITEM_SEPARATOR, newStat[i].f_fstypename, ITEM_SEPARATOR, newOptions, ITEM_SEPARATOR, sysSize, ITEM_SEPARATOR, sysFree, ITEM_SEPARATOR, sysSerial, ITEM_DELIMITER);

			newBuffil += newBufcur;
		}
	}

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
