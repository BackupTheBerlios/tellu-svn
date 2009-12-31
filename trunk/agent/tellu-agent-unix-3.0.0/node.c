#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>

#if defined(__sun__)
#include <sys/systeminfo.h>
#else
#include <sys/utsname.h>
#endif

#include "declarations.h"
#include "node.h"



void nodeInitNames(void) {
	int i;

	char *thisPointer;

	uid_t newUid;
	gid_t newGid;
#if defined(__linux__)
	int j;

	char *newArg;
	char newLine[DATA_BLOCK_SIZE];
	char newDistname[DATA_STRING_SIZE];

	const char *newDists[] = {
		DIST_DEBIAN1, DIST_DEBIAN2, DIST_FEDORA, DIST_GENTOO, DIST_MANDRAKE, DIST_REDHAT1, DIST_REDHAT2,
		DIST_SLACKWARE1, DIST_SLACKWARE2, DIST_SUNJDS, DIST_SUSE, DIST_UNITED, DIST_YELLOWDOG,
		NULL
	};

	const char *newNames[] = {
		DIST_NAME_DEBIAN1, DIST_NAME_DEBIAN2, DIST_NAME_FEDORA, DIST_NAME_GENTOO, DIST_NAME_MANDRAKE, DIST_NAME_REDHAT1, DIST_NAME_REDHAT2,
		DIST_NAME_SLACKWARE1, DIST_NAME_SLACKWARE2, DIST_NAME_SUNJDS, DIST_NAME_SUSE, DIST_NAME_UNITED, DIST_NAME_YELLOWDOG,
		NULL
	};

	const char *newKeys[] = {
		DIST_LSB_ID, DIST_LSB_RELEASE, DIST_LSB_CODENAME, DIST_LSB_DESCRIPTION,
		NULL
	};

	FILE *newFile;

	struct distStore newStore;
	struct stat newStat;
#endif
	struct passwd *newPasswd;
	struct group *newGroup;
#if !defined(__sun__)
	struct utsname nodeNames;
#endif
	memset(&nodeData, 0, sizeof(nodeData));

	if(gethostname(nodeData.node, sizeof(nodeData.node)) != 0) {
#if defined(__sun__)
		if(sysinfo(SI_HOSTNAME, nodeData.node, sizeof(nodeData.node)) == -1) {
			nodeData.node[0] = 0;
		}
#else
		if(uname(&nodeNames) == 0) {
			if(nodeNames.nodename[0] == 0) {
				if(gethostname(nodeData.node, sizeof(nodeData.node)) != 0) {
					nodeData.node[0] = 0;
				}
			}
			else {
				snprintf(nodeData.node, sizeof(nodeData.node), "%s%c", nodeNames.nodename, 0);
			}
		}
		else {
			snprintf(nodeData.node, sizeof(nodeData.node), "%s%c", nodeNames.nodename, 0);
		}
#endif
	}

	if((thisPointer = strchr(nodeData.node, '.')) != NULL) {
		*thisPointer = 0;
	}

#if defined(__sun__)
	if(sysinfo(SI_SRPC_DOMAIN, nodeData.domain, sizeof(nodeData.domain)) == -1) {
		nodeData.domain[0] = 0;
	}
#else
 #ifdef _GNU_SOURCE
	if(nodeNames.domainname[0] == 0) {
		if(getdomainname(nodeData.domain, sizeof(nodeData.domain)) != 0) {
			nodeData.domain[0] = 0;
		}
	}
	else {
		snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", nodeNames.domainname, 0);
	}
 #else
	if(getdomainname(nodeData.domain, sizeof(nodeData.domain)) != 0) {
		nodeData.domain[0] = 0;
	}
 #endif
#endif
#if defined(__sun__)
	if(sysinfo(SI_SYSNAME, nodeData.system, sizeof(nodeData.system)) == -1) {
		nodeData.system[0] = 0;
	}

	if(sysinfo(SI_RELEASE, nodeData.release, sizeof(nodeData.release)) == -1) {
		nodeData.release[0] = 0;
	}

	if(sysinfo(SI_MACHINE, nodeData.machine, sizeof(nodeData.machine)) == -1) {
		nodeData.machine[0] = 0;
	}
#else
	if(uname(&nodeNames) == 0) {
		if(nodeNames.sysname[0] == 0) {
			nodeData.system[0] = 0;
		}
		else {
			snprintf(nodeData.system, sizeof(nodeData.system), "%s%c", nodeNames.sysname, 0);
		}

		if(nodeNames.release[0] == 0) {
			nodeData.release[0] = 0;
		}
		else {
			snprintf(nodeData.release, sizeof(nodeData.release), "%s%c", nodeNames.release, 0);
		}

		if(nodeNames.machine[0] == 0) {
			nodeData.machine[0] = 0;
		}
		else {
			snprintf(nodeData.machine, sizeof(nodeData.machine), "%s%c", nodeNames.machine, 0);
		}
	}
#endif
#if defined(__linux__)
	if(stat(DIST_GENERAL, &newStat) == 0) {
		if((newFile = fopen(DIST_GENERAL, "r")) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
		}
		else {
			memset(&newStore, 0, sizeof(newStore));

			while(fgets(newLine, sizeof(newLine), newFile) != NULL) {
				if(newLine[0] == '\r' || newLine[0] == '\n' || newLine[0] == '#') {
					continue;
				}

				for(i = 0; ; i++) {
					if(newKeys[i] == NULL) {
						break;
					}

					if(strncasecmp(newKeys[i], newLine, strlen(newKeys[i])) == 0) {
						if((newArg = nodeParseArg(newLine)) == NULL) {
							continue;
						}

						if(strncasecmp(newKeys[i], DIST_LSB_ID, strlen(newKeys[i])) == 0) {
							nodeCopyArg(newArg, newStore.id);
						}
						else if(strncasecmp(newKeys[i], DIST_LSB_RELEASE, strlen(newKeys[i])) == 0) {
							nodeCopyArg(newArg, newStore.release);
						}
						else if(strncasecmp(newKeys[i], DIST_LSB_CODENAME, strlen(newKeys[i])) == 0) {
							nodeCopyArg(newArg, newStore.codename);
						}
						else if(strncasecmp(newKeys[i], DIST_LSB_DESCRIPTION, strlen(newKeys[i])) == 0) {
							nodeCopyArg(newArg, newStore.description);
						}

						break;
					}
				}
			}

			if(newStore.id[0] != 0 && newStore.release[0] != 0 && newStore.codename[0] != 0) {
				snprintf(nodeData.distribution, sizeof(nodeData.distribution), "%s %s (%s)%c", newStore.id, newStore.release, newStore.codename, 0);
			}

			if(fclose(newFile) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
			}
		}
	}

	if(nodeData.distribution[0] == 0) {
		for(i = 0; ; i++) {
			if(newDists[i] == NULL || newNames[i] == NULL) {
				break;
			}

			if(stat(newDists[i], &newStat) == -1) {
				continue;
			}

			if(newStat.st_size <= sizeof(newDistname)) {
				if((newFile = fopen(newDists[i], "r")) == NULL) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to open file for reading");
				}
				else {
					if(fread(newDistname, newStat.st_size, 1, newFile) < 1) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to read from file");

						if(fclose(newFile) == -1) {
							warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
						}
					}
					else {
						for(j = 0; j < strlen(newDistname); j++) {
							if(newDistname[j] == 10 || newDistname[j] == 13) {
								newDistname[j] = 0;

								break;
							}
						}

						snprintf(nodeData.distribution, sizeof(nodeData.distribution), "%s %s%c", newNames[i], newDistname, 0);

						if(fclose(newFile) == -1) {
							warningMessage(ERROR_SLIGHT, "Error occurred while trying to close file");
						}

						break;
					}
				}
			}
		}
	}
#endif
	newUid = getuid();
	newGid = getgid();

	newPasswd = getpwuid(newUid);

	if(newPasswd != NULL) {
		if(newPasswd->pw_name[0] == 0) {
			nodeData.useruid[0] = 0;
		}
		else {
			snprintf(nodeData.useruid, sizeof(nodeData.useruid), "%s%c", newPasswd->pw_name, 0);
		}

		if(newPasswd->pw_gecos[0] == 0) {
			nodeData.usergecos[0] = 0;
		}
		else {
			snprintf(nodeData.usergecos, sizeof(nodeData.usergecos), "%s%c", newPasswd->pw_gecos, 0);
		}

		if(newPasswd->pw_dir[0] == 0) {
			nodeData.userhomedir[0] = 0;
		}
		else {
			snprintf(nodeData.userhomedir, sizeof(nodeData.userhomedir), "%s%c", newPasswd->pw_dir, 0);
		}
	}

	if(strlen(nodeData.usergecos) > 1) {
		for(i = strlen(nodeData.usergecos) - 1; i > 0; i--) {
			if(nodeData.usergecos[i] == ',') {
				nodeData.usergecos[i] = 0;
			}
			else {
				break;
			}
		}
	}

	if((newGroup = getgrgid(newGid)) != NULL) {
		if(newGroup->gr_name[0] == 0) {
			nodeData.usergrp[0] = 0;
		}
		else {
			snprintf(nodeData.usergrp, sizeof(nodeData.usergrp), "%s%c", newGroup->gr_name, 0);
		}
	}

	if(nodeData.node[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch local node name");
	}

	if(nodeData.domain[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch local domain name");
	}

	if(nodeData.system[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch local system name");
	}

	if(nodeData.release[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch local system release");
	}

	if(nodeData.machine[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch local system architecture");
	}

	if(nodeData.useruid[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch user unix name");
	}

	if(nodeData.usergecos[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch user real name");
	}

	if(nodeData.userhomedir[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch user home directory");
	}

	if(nodeData.usergrp[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch user primary group");
	}
}

char *nodeFetchNode(void) {
	return(nodeData.node);
}

char *nodeFetchDomain(void) {
	char *confChar;

	if((confChar = configFetch("domain_override")) != NULL) {
		snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", confChar, 0);
	}

	return(nodeData.domain);
}

char *nodeFetchSystem(void) {
	return(nodeData.system);
}

char *nodeFetchRelease(void) {
	return(nodeData.release);
}

char *nodeFetchDistribution(void) {
	return(nodeData.distribution);
}

char *nodeFetchMachine(void) {
	return(nodeData.machine);
}

char *nodeFetchUserLogin(void) {
	return(nodeData.useruid);
}

char *nodeFetchUserName(void) {
	return(nodeData.usergecos);
}

char *nodeFetchUserHome(void) {
	return(nodeData.userhomedir);
}

char *nodeFetchUserGroup(void) {
	return(nodeData.usergrp);
}

char *nodeParseArg(char *confKeyword) {
	char *endLine;

	if((endLine = strchr(confKeyword, '=')) == NULL) {
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

	if(*endLine == '"' || *endLine == 39) {
		endLine++;
	}
	if(endLine[strlen(endLine) - 1] == '"' || endLine[strlen(endLine) - 1] == 39) {
		endLine[strlen(endLine) - 1] = 0;
	}

	if(*endLine == '\r' || *endLine == '\n' || *endLine == 0 || *endLine == EOF || strlen(endLine) < 1) {
		return(NULL);
	}

	return(endLine);
}

void nodeCopyArg(char *confArgument, char *confStore) {
	size_t i;

	i = strlen(confArgument);

	if(i > DATA_STRING_SIZE - 1) {
		i = DATA_STRING_SIZE - 1;
	}

	strncpy(confStore, confArgument, i);

	confStore[i] = 0;
}
