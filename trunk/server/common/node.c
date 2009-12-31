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
#include "defines.h"
#include "node.h"



void nodeInitNames(void) {
	int i;

	uid_t newUid;
	gid_t newGid;

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
	return(nodeData.domain);
}

char *nodeFetchSystem(void) {
	return(nodeData.system);
}

char *nodeFetchRelease(void) {
	return(nodeData.release);
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
