#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "declarations.h"
#include "services.h"



char *servGetCount(struct paramInfo * pi) {
#if defined(__linux__)
	int i, k, l;

	char *newArg, *newBuffer;
	char newLine[DATA_BLOCK_SIZE];
	char newName[DATA_STRING_SIZE];

	DIR *newDir;
	FILE *newFile;

	struct dirent *newEntry;

	if((newDir = opendir(PROC_GENERAL)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open directory");

		return(NULL);
	}

	k = 0;
	l = 0;

	while((newEntry = readdir(newDir)) != NULL) {
		for(i = 0; i < strlen(newEntry->d_name); i++) {
			if(newEntry->d_name[i] < '0' || newEntry->d_name[i] > '9') {
				break;
			}
		}

		if(i == strlen(newEntry->d_name)) {
			snprintf(newName, sizeof(newName), "%s/%s/status%c", PROC_GENERAL, newEntry->d_name, 0);

			if((newFile = fopen(newName, "r")) == NULL) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
			}
			else {
				while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
					if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
						continue;
					}

					if(strncasecmp(PROC_THREADS, newLine, strlen(PROC_THREADS)) == 0) {
						if((newArg = servParseArg(newLine)) == NULL) {
							continue;
						}

						l += atoi(newArg);

						break;
					}
				}

				if(fclose(newFile) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
				}

				k++;
			}
		}
	}

	if(closedir(newDir) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close directory");
	}

	if((newBuffer = malloc(DATA_STRING_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process count buffer");

		return(NULL);
	}

	snprintf(newBuffer, DATA_STRING_SIZE, "%d%c%d%c", k, ITEM_SEPARATOR, l, 0);

	return(newBuffer);
#endif
	return(NULL);
}

void servFreeCount(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *servGetProcesses(struct paramInfo * pi) {
#if defined(__linux__)
	int i, k;

	char *newArg, *newBuffer, *tmpBuffer;
	char newLine[DATA_BLOCK_SIZE];
	char newName[DATA_STRING_SIZE];
	char newCmdline[DATA_STRING_SIZE];

	const char *newStatkeys[] = {
		PROC_NAME, PROC_STATE, PROC_PID, PROC_PPID, PROC_UID, PROC_GID, PROC_VMPEAK, PROC_VMSIZE, PROC_VMHWM, PROC_VMRSS, PROC_VMDATA, PROC_VMSTK,
		PROC_VMEXE, PROC_VMLIB, PROC_VMPTE, PROC_THREADS,
		NULL
	};

	const char *newIokeys[] = {
		PROC_IO_RCHAR, PROC_IO_WCHAR, PROC_IO_SYSCR, PROC_IO_SYSCW, PROC_IO_RBYTE, PROC_IO_WBYTE,
		NULL
	};

	size_t newBuflen, newBufcur, newBuffil;

	uid_t newUid;
	gid_t newGid;

	DIR *newDir;
	FILE *newFile;

	struct servStore newStore;
	struct dirent *newEntry;
	struct passwd *newPasswd;
	struct group *newGroup;

	newBuffer = NULL;

	if((newDir = opendir(PROC_GENERAL)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open directory");
	}
	else {
		k = 0;

		newBuffil = 0;
		newBuflen = DATA_BLOCK_SIZE;

		if((newBuffer = malloc(newBuflen)) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process buffer");

			return(NULL);
		}

		while((newEntry = readdir(newDir)) != NULL) {
			for(i = 0; i < strlen(newEntry->d_name); i++) {
				if(newEntry->d_name[i] < '0' || newEntry->d_name[i] > '9') {
					break;
				}
			}

			if(i == strlen(newEntry->d_name)) {
				snprintf(newName, sizeof(newName), "%s/%s/cmdline%c", PROC_GENERAL, newEntry->d_name, 0);

				if((newFile = fopen(newName, "r")) == NULL) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
				}
				else {
					i = 0;

					while(fread(newCmdline + i, 1, 1, newFile)) {
						i++;
					}

					newCmdline[i] = 0;

					if(fclose(newFile) == -1) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
					}

					memset(&newStore, 0, sizeof(newStore));

					if(newCmdline[0] != 0 && strlen(newCmdline) > 1) {
						servCopyArg(newCmdline, newStore.cmdline);
					}
					else {
						servCopyArg(PROC_KERNEL, newStore.cmdline);
					}

					snprintf(newName, sizeof(newName), "%s/%s/status%c", PROC_GENERAL, newEntry->d_name, 0);

					if((newFile = fopen(newName, "r")) != NULL) {
						while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
							if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
								continue;
							}

							for(i = 0; ; i++) {
								if(newStatkeys[i] == NULL) {
									break;
								}

								if(strncasecmp(newStatkeys[i], newLine, strlen(newStatkeys[i])) == 0) {
									if((newArg = servParseArg(newLine)) == NULL) {
										continue;
									}

									if(strncasecmp(newStatkeys[i], PROC_NAME, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.name);
									}
									else if(strncasecmp(newStatkeys[i], PROC_STATE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.state);
									}
									else if(strncasecmp(newStatkeys[i], PROC_PID, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.pid);
									}
									else if(strncasecmp(newStatkeys[i], PROC_PPID, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.ppid);
									}
									else if(strncasecmp(newStatkeys[i], PROC_UID, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.uid);
									}
									else if(strncasecmp(newStatkeys[i], PROC_GID, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.gid);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMPEAK, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmpeak);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMSIZE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmsize);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMHWM, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmhwm);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMRSS, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmrss);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMDATA, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmdata);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMSTK, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmstk);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMEXE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmexe);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMLIB, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmlib);
									}
									else if(strncasecmp(newStatkeys[i], PROC_VMPTE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.vmpte);
									}
									else if(strncasecmp(newStatkeys[i], PROC_THREADS, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.threads);
									}

									break;
								}
							}
						}

						if(fclose(newFile) == -1) {
							warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
						}
					}

					snprintf(newName, sizeof(newName), "%s/%s/io%c", PROC_GENERAL, newEntry->d_name, 0);

					if((newFile = fopen(newName, "r")) != NULL) {
						while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
							if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
								continue;
							}

							for(i = 0; ; i++) {
								if(newIokeys[i] == NULL) {
									break;
								}

								if(strncasecmp(newIokeys[i], newLine, strlen(newIokeys[i])) == 0) {
									if((newArg = servParseArg(newLine)) == NULL) {
										continue;
									}

									if(strncasecmp(newStatkeys[i], PROC_IO_RCHAR, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.rchar);
									}
									else if(strncasecmp(newStatkeys[i], PROC_IO_WCHAR, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.wchar);
									}
									else if(strncasecmp(newStatkeys[i], PROC_IO_SYSCR, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.syscr);
									}
									else if(strncasecmp(newStatkeys[i], PROC_IO_SYSCW, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.syscw);
									}
									else if(strncasecmp(newStatkeys[i], PROC_IO_RBYTE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.rbyte);
									}
									else if(strncasecmp(newStatkeys[i], PROC_IO_WBYTE, strlen(newStatkeys[i])) == 0) {
										servCopyArg(newArg, newStore.wbyte);
									}

									break;
								}
							}
						}

						if(fclose(newFile) == -1) {
							warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
						}
					}

					newUid = (uid_t) atoi(newStore.uid);

					if((newPasswd = getpwuid(newUid)) != NULL) {
						strncpy(newStore.uid, newPasswd->pw_name, sizeof(newStore.uid));
					}

					newGid = (gid_t) atoi(newStore.gid);

					if((newGroup = getgrgid(newGid)) != NULL) {
						strncpy(newStore.gid, newGroup->gr_name, sizeof(newStore.gid));
					}

					newBufcur = strlen(newStore.cmdline) + strlen(newStore.name) + strlen(newStore.state) + strlen(newStore.pid) + strlen(newStore.ppid) + strlen(newStore.threads) + strlen(newStore.vmdata) + strlen(newStore.vmexe) + strlen(newStore.vmhwm) + strlen(newStore.vmlib) + strlen(newStore.vmpeak) + strlen(newStore.vmpte) + strlen(newStore.vmrss) + strlen(newStore.vmsize) + strlen(newStore.vmstk) + strlen(newStore.rchar) + strlen(newStore.wchar) + strlen(newStore.syscr) + strlen(newStore.syscw) + strlen(newStore.rbyte) + strlen(newStore.wbyte) + strlen(newStore.uid) + strlen(newStore.gid) + CONFIG_SPACE_SIZE;

					if(newBuflen - newBuffil <= newBufcur) {
						newBuflen += DATA_BLOCK_SIZE * 20;

						if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
							free(newBuffer);

							warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process buffer");

							return(NULL);
						}

						newBuffer = tmpBuffer;
					}

					k += snprintf(newBuffer + k, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c", newStore.cmdline, ITEM_SEPARATOR, newStore.name, ITEM_SEPARATOR, newStore.state, ITEM_SEPARATOR, newStore.pid, ITEM_SEPARATOR, newStore.ppid, ITEM_SEPARATOR, newStore.threads, ITEM_SEPARATOR, newStore.vmdata, ITEM_SEPARATOR, newStore.vmexe, ITEM_SEPARATOR, newStore.vmhwm, ITEM_SEPARATOR, newStore.vmlib, ITEM_SEPARATOR, newStore.vmpeak, ITEM_SEPARATOR, newStore.vmpte, ITEM_SEPARATOR, newStore.vmrss, ITEM_SEPARATOR, newStore.vmsize, ITEM_SEPARATOR, newStore.vmstk, ITEM_SEPARATOR, newStore.rchar, ITEM_SEPARATOR, newStore.wchar, ITEM_SEPARATOR, newStore.syscr, ITEM_SEPARATOR, newStore.syscw, ITEM_SEPARATOR, newStore.rbyte, ITEM_SEPARATOR, newStore.wbyte, ITEM_SEPARATOR, newStore.uid, ITEM_SEPARATOR, newStore.gid, ITEM_DELIMITER);

					newBuffil += newBufcur;
				}
			}
		}

		if(closedir(newDir) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close directory");
		}

		if(k > 0) {
			k--;
		}

		newBuffer[k] = 0;
	}

	return(newBuffer);
#endif
	return(NULL);
}

void servFreeProcesses(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *servGetServices(struct paramInfo * pi) {
#if defined(__linux__)
	int i, k;

	char *newArg, *newBuffer, *tmpBuffer;
	char *endLine, *thisLine;
	char newLine[DATA_BLOCK_SIZE];
	char newName[DATA_STRING_SIZE];
	char newCmdline[DATA_STRING_SIZE];

	const char *newStatkeys[] = {
		PROC_NAME, PROC_STATE, PROC_PID, PROC_PPID, PROC_UID, PROC_GID, PROC_VMPEAK, PROC_VMSIZE, PROC_VMHWM, PROC_VMRSS, PROC_VMDATA, PROC_VMSTK,
		PROC_VMEXE, PROC_VMLIB, PROC_VMPTE, PROC_THREADS,
		NULL
	};

	const char *newIokeys[] = {
		PROC_IO_RCHAR, PROC_IO_WCHAR, PROC_IO_SYSCR, PROC_IO_SYSCW, PROC_IO_RBYTE, PROC_IO_WBYTE,
		NULL
	};

	size_t newBuflen, newBufcur, newBuffil;

	uid_t newUid;
	gid_t newGid;

	DIR *newDir;
	FILE *newFile;

	struct servStore newStore;
	struct dirent *newEntry;
	struct passwd *newPasswd;
	struct group *newGroup;

	newBuffer = NULL;

	if((newDir = opendir(PROC_GENERAL)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open directory");
	}
	else {
		k = 0;

		newBuffil = 0;
		newBuflen = DATA_BLOCK_SIZE;

		if((newBuffer = malloc(newBuflen)) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process buffer");

			return(NULL);
		}

		while((newEntry = readdir(newDir)) != NULL) {
			for(i = 0; i < strlen(newEntry->d_name); i++) {
				if(newEntry->d_name[i] < '0' || newEntry->d_name[i] > '9') {
					break;
				}
			}

			if(i == strlen(newEntry->d_name)) {
				snprintf(newName, sizeof(newName), "%s/%s/cmdline%c", PROC_GENERAL, newEntry->d_name, 0);

				if((newFile = fopen(newName, "r")) == NULL) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
				}
				else {
					i = 0;

					while(fread(newCmdline + i, 1, 1, newFile)) {
						i++;
					}

					newCmdline[i] = 0;

					if(fclose(newFile) == -1) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
					}

					if(newCmdline[0] != 0 && strlen(newCmdline) > 1) {
						thisLine = newCmdline;

						if((endLine = strchr(newCmdline, ' ')) != NULL) {
							*endLine = 0;
						}
						if(thisLine[strlen(thisLine) - 1] == ':') {
							thisLine[strlen(thisLine) - 1] = 0;
						}
						if((endLine = strrchr(thisLine, '/')) != NULL) {
							endLine++;

							if(endLine != 0) {
								thisLine = endLine;
							}
						}

						if(thisLine[strlen(thisLine) - 1] == 'd') {
							memset(&newStore, 0, sizeof(newStore));

							servCopyArg(thisLine, newStore.cmdline);

							snprintf(newName, sizeof(newName), "%s/%s/status%c", PROC_GENERAL, newEntry->d_name, 0);

							if((newFile = fopen(newName, "r")) != NULL) {
								while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
									if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
										continue;
									}

									for(i = 0; ; i++) {
										if(newStatkeys[i] == NULL) {
											break;
										}

										if(strncasecmp(newStatkeys[i], newLine, strlen(newStatkeys[i])) == 0) {
											if((newArg = servParseArg(newLine)) == NULL) {
												continue;
											}

											if(strncasecmp(newStatkeys[i], PROC_NAME, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.name);
											}
											else if(strncasecmp(newStatkeys[i], PROC_STATE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.state);
											}
											else if(strncasecmp(newStatkeys[i], PROC_PID, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.pid);
											}
											else if(strncasecmp(newStatkeys[i], PROC_PPID, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.ppid);
											}
											else if(strncasecmp(newStatkeys[i], PROC_UID, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.uid);
											}
											else if(strncasecmp(newStatkeys[i], PROC_GID, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.gid);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMPEAK, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmpeak);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMSIZE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmsize);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMHWM, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmhwm);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMRSS, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmrss);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMDATA, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmdata);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMSTK, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmstk);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMEXE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmexe);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMLIB, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmlib);
											}
											else if(strncasecmp(newStatkeys[i], PROC_VMPTE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.vmpte);
											}
											else if(strncasecmp(newStatkeys[i], PROC_THREADS, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.threads);
											}

											break;
										}
									}
								}

								if(fclose(newFile) == -1) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
								}
							}

							snprintf(newName, sizeof(newName), "%s/%s/io%c", PROC_GENERAL, newEntry->d_name, 0);

							if((newFile = fopen(newName, "r")) != NULL) {
								while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
									if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
										continue;
									}

									for(i = 0; ; i++) {
										if(newIokeys[i] == NULL) {
											break;
										}

										if(strncasecmp(newIokeys[i], newLine, strlen(newIokeys[i])) == 0) {
											if((newArg = servParseArg(newLine)) == NULL) {
												continue;
											}

											if(strncasecmp(newStatkeys[i], PROC_IO_RCHAR, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.rchar);
											}
											else if(strncasecmp(newStatkeys[i], PROC_IO_WCHAR, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.wchar);
											}
											else if(strncasecmp(newStatkeys[i], PROC_IO_SYSCR, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.syscr);
											}
											else if(strncasecmp(newStatkeys[i], PROC_IO_SYSCW, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.syscw);
											}
											else if(strncasecmp(newStatkeys[i], PROC_IO_RBYTE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.rbyte);
											}
											else if(strncasecmp(newStatkeys[i], PROC_IO_WBYTE, strlen(newStatkeys[i])) == 0) {
												servCopyArg(newArg, newStore.wbyte);
											}

											break;
										}
									}
								}

								if(fclose(newFile) == -1) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
								}
							}

							newUid = (uid_t) atoi(newStore.uid);

							if((newPasswd = getpwuid(newUid)) != NULL) {
								strncpy(newStore.uid, newPasswd->pw_name, sizeof(newStore.uid));
							}

							newGid = (gid_t) atoi(newStore.gid);

							if((newGroup = getgrgid(newGid)) != NULL) {
								strncpy(newStore.gid, newGroup->gr_name, sizeof(newStore.gid));
							}

							newBufcur = strlen(newStore.cmdline) + strlen(newStore.name) + strlen(newStore.state) + strlen(newStore.pid) + strlen(newStore.ppid) + strlen(newStore.threads) + strlen(newStore.vmdata) + strlen(newStore.vmexe) + strlen(newStore.vmhwm) + strlen(newStore.vmlib) + strlen(newStore.vmpeak) + strlen(newStore.vmpte) + strlen(newStore.vmrss) + strlen(newStore.vmsize) + strlen(newStore.vmstk) + strlen(newStore.rchar) + strlen(newStore.wchar) + strlen(newStore.syscr) + strlen(newStore.syscw) + strlen(newStore.rbyte) + strlen(newStore.wbyte) + strlen(newStore.uid) + strlen(newStore.gid) + CONFIG_SPACE_SIZE;

							if(newBuflen - newBuffil <= newBufcur) {
								newBuflen += DATA_BLOCK_SIZE * 20;

								if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
									free(newBuffer);

									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process buffer");

									return(NULL);
								}

								newBuffer = tmpBuffer;
							}

							k += snprintf(newBuffer + k, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c", newStore.cmdline, ITEM_SEPARATOR, newStore.name, ITEM_SEPARATOR, newStore.state, ITEM_SEPARATOR, newStore.pid, ITEM_SEPARATOR, newStore.ppid, ITEM_SEPARATOR, newStore.threads, ITEM_SEPARATOR, newStore.vmdata, ITEM_SEPARATOR, newStore.vmexe, ITEM_SEPARATOR, newStore.vmhwm, ITEM_SEPARATOR, newStore.vmlib, ITEM_SEPARATOR, newStore.vmpeak, ITEM_SEPARATOR, newStore.vmpte, ITEM_SEPARATOR, newStore.vmrss, ITEM_SEPARATOR, newStore.vmsize, ITEM_SEPARATOR, newStore.vmstk, ITEM_SEPARATOR, newStore.rchar, ITEM_SEPARATOR, newStore.wchar, ITEM_SEPARATOR, newStore.syscr, ITEM_SEPARATOR, newStore.syscw, ITEM_SEPARATOR, newStore.rbyte, ITEM_SEPARATOR, newStore.wbyte, ITEM_SEPARATOR, newStore.uid, ITEM_SEPARATOR, newStore.gid, ITEM_DELIMITER);

							newBuffil += newBufcur;
						}
					}
				}
			}
		}

		if(closedir(newDir) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close directory");
		}

		if(k > 0) {
			k--;
		}

		newBuffer[k] = 0;
	}

	return(newBuffer);
#endif
	return(NULL);
}

void servFreeServices(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *servParseArg(char *confKeyword) {
	char *endLine, *endSpace;

	if((endLine = strchr(confKeyword, ':')) == NULL) {
		return(NULL);
	}

	endLine++;

	if(endLine[strlen(endLine) - 2] == '\r') {
		endLine[strlen(endLine) - 2] = 0;
	}
	else {
		endLine[strlen(endLine) - 1] = 0;
	}

	while(*endLine == ' ' || *endLine == '\t') {
		endLine++;
	}

	while((endSpace = strrchr(endLine, ' ')) != NULL) {
		*endSpace = 0;
	}

	if(*endLine == '\r' || *endLine == '\n' || *endLine == 0 || *endLine == EOF || strlen(endLine) < 1) {
		return(NULL);
	}

	return(endLine);
}

void servCopyArg(char *confArgument, char *confStore) {
	size_t i;

	i = strlen(confArgument);

	if(i > DATA_STRING_SIZE - 1) {
		i = DATA_STRING_SIZE - 1;
	}

	strncpy(confStore, confArgument, i);

	confStore[i] = 0;
}
