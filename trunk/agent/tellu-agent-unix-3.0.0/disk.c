#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/statvfs.h>

#if defined(__linux__)
#include <mntent.h>
#elif defined(__FreeBSD__)
#include <sys/param.h>
#include <sys/ucred.h>
#include <sys/mount.h>
#elif defined(__OpenBSD__)
#include <sys/param.h>
#include <sys/mount.h>
#endif

#include "declarations.h"



char *diskGetMounted(struct paramInfo * pi) {
#if defined(__linux__)
	int k;
	unsigned long p;
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
			p = 0;

			if(newStat.f_frsize > 0) {
				p = newStat.f_frsize;
			}

			sysSize = (newStat.f_blocks * p) / 1000;
			sysFree = (newStat.f_bfree * p) / 1000;
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
#elif defined(__FreeBSD__) || (__NetBSD__) || (__OpenBSD__)
	int i, j, k, l, m;
	unsigned long g;
	unsigned long long sysSize, sysFree, sysSerial;
#if defined(__FreeBSD__)
	uint64_t f, p;
#elif defined(__NetBSD__)
	unsigned long f, p;
#elif defined(__OpenBSD__)
	u_int32_t f, p;
#endif
	char *newBuffer, *tmpBuffer;
	char newOptions[CONFIG_SPACE_SIZE];

	size_t newBuflen, newBufcur, newBuffil;
#if defined(__FreeBSD__)
	struct statfs *newStat;

	uint64_t newFlags[] = {
		MNT_RDONLY, MNT_SYNCHRONOUS, MNT_NOEXEC, MNT_NOSUID, MNT_UNION, MNT_ASYNC, MNT_SUIDDIR, MNT_SOFTDEP, MNT_NOSYMFOLLOW,
		MNT_GJOURNAL, MNT_MULTILABEL, MNT_ACLS, MNT_NOATIME, MNT_NOCLUSTERR, MNT_NOCLUSTERW, MNT_EXRDONLY, MNT_EXPORTED,
		MNT_DEFEXPORTED, MNT_EXPORTANON, MNT_EXKERB, MNT_EXPUBLIC, MNT_LOCAL, MNT_QUOTA, MNT_ROOTFS, MNT_USER, MNT_IGNORE,
		-1
	};

	const char *newClags[] = {
		"read-only", "synchronous", "noexec", "nosuid", "union", "asynchronous", "suiddir", "soft dependencies", "nosymlinks",
		"gjournal", "multilabel", "acls", "noatime", "noclusterr", "noclusterw", "exported read-only", "NFS exported",
		"exported to the world", "anon uid mapping", "kerberos uid mapping", "WebNFS exports", "local", "with quotas",
		"root file system", "user", "ignore"
	};
#elif defined(__NetBSD__)
	struct statvfs *newStat;

	unsigned long newFlags[] = {
		MNT_RDONLY, MNT_SYNCHRONOUS, MNT_NOEXEC, MNT_NOSUID, MNT_NODEV, MNT_UNION, MNT_ASYNC, MNT_NOCOREDUMP, MNT_IGNORE, MNT_LOG,
		MNT_NOATIME, MNT_SYMPERM, MNT_NODEVMTIME, MNT_SOFTDEP, MNT_EXRDONLY, MNT_EXPORTED, MNT_DEFEXPORTED, MNT_EXPORTANON,
		MNT_EXKERB, MNT_EXNORESPORT, MNT_EXPUBLIC, MNT_LOCAL, MNT_QUOTA, MNT_ROOTFS, MNT_UPDATE, MNT_RELOAD, MNT_FORCE, MNT_GETARGS,
		-1
	};

	const char *newClags[] = {
		"read-only", "synchronous", "noexec", "nosuid", "nodev", "union", "asynchronous", "nocoredump", "hidden", "log",
		"noatime", "symperm", "nodevmtime", "soft dependencies", "exported read-only", "NFS exported", "exported to the world",
		"anon uid mapping", "kerberos uid mapping", "on-reserved ports", "WebNFS exports", "local", "with quotas", "root file system",
		"being updated", "reload filesystem data", "force unmount or readonly change", "retrieve mount arguments"
	};
#elif defined(__OpenBSD__)
	struct statfs *newStat;

	u_int32_t newFlags[] = {
		MNT_RDONLY, MNT_SYNCHRONOUS, MNT_NOEXEC, MNT_NOSUID, MNT_NODEV, MNT_ASYNC, MNT_EXRDONLY, MNT_EXPORTED, MNT_DEFEXPORTED,
		MNT_EXPORTANON, MNT_EXKERB, MNT_LOCAL, MNT_QUOTA, MNT_ROOTFS, MNT_NOATIME, MNT_UPDATE, MNT_DELEXPORT, MNT_RELOAD,
		MNT_FORCE, MNT_WANTRDWR, MNT_SOFTDEP, MNT_DOOMED,
		-1
	};

	const char *newClags[] = {
		"read-only", "synchronous", "noexec", "nosuid", "nodev", "asynchronous", "exported read-only", "NFS exported",
		"exported to the world", "anon uid mapping", "kerberos uid mapping", "local", "with quotas", "root file system",
		"noatime", "being updated", "delete export", "reload filesystem data", "force unmount or readonly change", "want rdrw",
		"soft dependencies", "doomed"
	};
#endif
	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

		return(NULL);
	}

	k = 0;
#if defined(__FreeBSD__) || (__OpenBSD__)
	if((j = getmntinfo(&newStat, MNT_NOWAIT)) != 0) {
#elif defined(__NetBSD__)
	if((j = getmntinfo(&newStat, ST_NOWAIT)) != 0) {
#endif
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

			p = 0;
#if defined(__FreeBSD__) || (__OpenBSD__)
			if(newStat[i].f_bsize > 0) {
				p = newStat[i].f_bsize;
			}
#elif defined(__NetBSD__)
			if(newStat[i].f_frsize > 0) {
				p = newStat[i].f_frsize;
			}
#endif
			sysSize = (newStat[i].f_blocks * p) / 1000;
			sysFree = (newStat[i].f_bfree * p) / 1000;
#if defined(__FreeBSD__) || (__OpenBSD__)
			sysSerial = newStat[i].f_fsid.val[0];
			sysSerial += newStat[i].f_fsid.val[1];
			sysSerial += newStat[i].f_fsid.val[2];
#elif defined(__NetBSD__)
			sysSerial = newStat[i].f_fsid;
#endif
			memset(newOptions, 0, sizeof(newOptions));

			g = 1;
#if defined(__FreeBSD__)
			for(l = 0; l < sizeof(uint64_t) * 8; l++) {
				f = newStat[i].f_flags;
#elif defined(__NetBSD__)
			for(l = 0; l < sizeof(unsigned long) * 8; l++) {
				f = newStat[i].f_flag;
#elif defined(__OpenBSD__)
			for(l = 0; l < sizeof(u_int32_t) * 8; l++) {
				f = newStat[i].f_flags;
#endif
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
