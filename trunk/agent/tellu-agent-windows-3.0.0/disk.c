#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



char *diskGetMounted(struct paramInfo * pi) {
	unsigned int i, j, k;
	_int64 spaceAvail, spaceTotal;

	char *newOffset, *newBuffer;

	size_t newBuflen;

	char *newOptnames[] = {
		"case_preserved_names", "case_sensitive_search", "file_compression", "named_streams", "persistent_acls", "read_only",
		"seq_write_once", "encryption_support", "ext_attrs_support", "hard_link_support", "obj_ids_support", "open_by_file_id_support",
		"reparse_points_support", "sparse_file_support", "transaction_support", "usn_journal_support", "unicode", "is_compressed",
		"quotas"
	};

	DWORD newOpts[] = {
		0x00000002, 0x00000001, 0x00000010, 0x00040000, 0x00000008, 0x00080000, 0x00100000, 0x00020000, 0x00800000, 0x00400000,
		0x00010000, 0x01000000, 0x00000080, 0x00000040, 0x00200000, 0x02000000, 0x00000004, 0x00008000, 0x00000020,
		0
	};

	DWORD newSerial, newMaxLen, newOptions, newOpttemp;
	DWORD oldSecPerCluster, oldBytesPerSec, oldTotal, oldAvail;
	FARPROC diskFreeSpace;
	HMODULE modKernel;
	ULARGE_INTEGER newFree, newTotal, newAvail;
	TCHAR newDrives[CONFIG_STRING_SIZE];
	TCHAR newFsName[CONFIG_SPACE_SIZE];
	TCHAR newTemp[CONFIG_SPACE_SIZE];
	TCHAR newVolume[MAX_PATH + 1];

	newBuflen = CONFIG_STRING_SIZE * 10;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for disk info buffer");

		return(NULL);
	}

	k = 0;

	if(GetLogicalDriveStrings(sizeof(newDrives), newDrives) != 0) {
		newOffset = newDrives;

		for(i = 0; i < 1024; i++) {
			if(*newOffset != 0) {
				// Resolve drive type

				switch(GetDriveType(newOffset)) {
					case DRIVE_REMOVABLE:
						k += _snprintf(newBuffer + k, newBuflen, "Removable%c", ITEM_SEPARATOR);

						break;
					case DRIVE_FIXED:
						k += _snprintf(newBuffer + k, newBuflen, "Disk%c", ITEM_SEPARATOR);

						break;
					case DRIVE_REMOTE:
						k += _snprintf(newBuffer + k, newBuflen, "Remote%c", ITEM_SEPARATOR);

						break;
					case DRIVE_CDROM:
						k += _snprintf(newBuffer + k, newBuflen, "Optical%c", ITEM_SEPARATOR);

						break;
					case DRIVE_RAMDISK:
						k += _snprintf(newBuffer + k, newBuflen, "Volatile%c", ITEM_SEPARATOR);

						break;
					default:
						k += _snprintf(newBuffer + k, newBuflen, "Unknown%c", ITEM_SEPARATOR);

						break;
				}

				// Resolve fstype, serial and options

				newSerial = 0;
				newMaxLen = 0;
				newOptions = 0;

				memset(&newFsName, 0, sizeof(newFsName));
				memset(&newVolume, 0, sizeof(newVolume));

				GetVolumeInformation(newOffset, newVolume, sizeof(newVolume), &newSerial, &newMaxLen, &newOptions, newFsName, sizeof(newFsName));

				if(newVolume[0] != 0) {
					k += _snprintf(newBuffer + k, newBuflen, "%s (%s)%c%s%c", newOffset, newVolume, ITEM_SEPARATOR, newFsName, ITEM_SEPARATOR);
				}
				else {
					k += _snprintf(newBuffer + k, newBuflen, "%s%c%s%c", newOffset, ITEM_SEPARATOR, newFsName, ITEM_SEPARATOR);
				}

				for(j = 0; ; j++) {
					if(newOpts[j] == 0) {
						break;
					}

					newOpttemp = newOptions;
					newOpttemp &= newOpts[j];

					if(newOpttemp == newOpts[j]) {
						k += _snprintf(newBuffer + k, newBuflen, "%s,", newOptnames[j]);
					}
				}

				if(k > 0 && newBuffer[k - 1] == ',') {
					k--;
				}

				k += _snprintf(newBuffer + k, newBuflen, "%c", ITEM_SEPARATOR);

				// Resolve total and available space

				memset(&newFree, 0, sizeof(newFree));
				memset(&newTotal, 0, sizeof(newTotal));
				memset(&newAvail, 0, sizeof(newAvail));

				spaceAvail = 0;
				spaceTotal = 0;

				newTemp[0] = 0;

				if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
					if((diskFreeSpace = GetProcAddress(modKernel, "GetDiskFreeSpaceExA")) != NULL) {
						if((diskFreeSpace)(newOffset, &newFree, &newTotal, &newAvail) != 0) {
							_snprintf(newTemp, sizeof(newTemp), "%llu%c", newTotal.QuadPart, 0);

							spaceTotal = _atoi64(newTemp);
							spaceTotal /= 1000;

							_snprintf(newTemp, sizeof(newTemp), "%llu%c", newAvail.QuadPart, 0);

							spaceAvail = _atoi64(newTemp);
							spaceAvail /= 1000;

							newTemp[0] = -1;
						}
					}

					FreeLibrary(modKernel);
				}

				if(newTemp[0] != -1) {
					if(GetDiskFreeSpace(newOffset, &oldSecPerCluster, &oldBytesPerSec, &oldAvail, &oldTotal) != 0) {
						spaceTotal = oldSecPerCluster * oldBytesPerSec;
						spaceTotal *= oldTotal;
						spaceTotal /= 1000;

						spaceAvail = oldSecPerCluster * oldBytesPerSec;
						spaceAvail *= oldAvail;
						spaceAvail /= 1000;
					}
				}

				k += _snprintf(newBuffer + k, newBuflen, "%llu%c%llu%c%.16x%c", spaceTotal, ITEM_SEPARATOR, spaceAvail, ITEM_SEPARATOR, newSerial, ITEM_DELIMITER);
			}

			while(*newOffset != 0) {
				newOffset++;
			}

			newOffset++;

			if(*newOffset == 0) {
				break;
			}
		}
	}

	if(k > 0) {
		k--;
	}

	newBuffer[k] = 0;

	return(newBuffer);
}

void diskFreeMounted(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
