#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"
#include "banner.h"
#include "cmdline.h"



void cmdRead(char **argv, int argc) {
	int i, j;

	char *thisOption;

	size_t s;

	void (*cmd)(char *);

	for(i = 1; i < argc; i++) {
		for(j = 0; ; j++) {
			if(mainCmdlines[j].optShort == NULL) {
				break;
			}

			if(mainCmdlines[j].optShort[0] == 0) {
				continue;
			}

			s = strlen(mainCmdlines[j].optShort);

			if(strlen(argv[i]) > s) {
				s = strlen(argv[i]);
			}

			if(strncmp(mainCmdlines[j].optShort, argv[i], s) == 0) {
				cmd = *mainCmdlines[j].fp;
				thisOption = NULL;

				if(mainCmdlines[j].optRequired == CONFIG_OPTION_REQUIRED) {
					thisOption = argv[++i];

					if(thisOption == NULL) {
						fprintf(stderr, "Parameter is mandatory for option '%s'.%c", argv[i - 1], CONFIG_LINEFEED);

						exitProcess(0);
					}
				}

				(void) (*cmd)((char *) thisOption);

				break;
			}

			s = strlen(mainCmdlines[j].optLong);

			if(strlen(argv[i]) > s) {
				s = strlen(argv[i]);
			}

			if(strncmp(mainCmdlines[j].optLong, argv[i], s) == 0) {
				cmd = *mainCmdlines[j].fp;
				thisOption = NULL;

				if(mainCmdlines[j].optRequired == CONFIG_OPTION_REQUIRED) {
					thisOption = argv[++i];

					if(thisOption == NULL) {
						fprintf(stderr, "Parameter is mandatory for option '%s'.%c", argv[i - 1], CONFIG_LINEFEED);

						exitProcess(0);
					}
				}

				(void) (*cmd)((char *) thisOption);

				break;
			}
		}
	}
}

void cmdProcHelp(char *thisOption) {
	int i;

	for(i = 0; ; i++) {
		if(mainCmdlines[i].optShort == NULL) {
			break;
		}

		if(mainCmdlines[i].optShort[0] == 0) {
			fprintf(stdout, "%c%s:%c", CONFIG_LINEFEED, mainCmdlines[i].optDesc, CONFIG_LINEFEED);

			continue;
		}

		fprintf(stdout, " %s, %s", mainCmdlines[i].optShort, mainCmdlines[i].optLong);

		if(mainCmdlines[i].optRequired == CONFIG_OPTION_REQUIRED) {
			fprintf(stdout, " <parameter>");
		}

		if(mainCmdlines[i].optDefault != NULL && mainCmdlines[i].optDefault[0] != 0) {
			fprintf(stdout, " (default: %s)", mainCmdlines[i].optDefault);
		}

		fprintf(stdout, "%c        %s%c", CONFIG_LINEFEED, mainCmdlines[i].optDesc, CONFIG_LINEFEED);
	}

	exitProcess(0);
}

void cmdProcVersion(char *thisOption) {
	fprintf(stdout, "%s%c", BANNER_VERSION, CONFIG_LINEFEED);

	exitProcess(0);
}

void cmdProcLicense(char *thisOption) {
	fprintf(stdout, "%s%c", BANNER_LICENSE, CONFIG_LINEFEED);

	exitProcess(0);
}

void cmdProcConfig(char *thisOption) {
	configUpdateString("config_file", thisOption);
}

void cmdProcUser(char *thisOption) {
	configUpdateInteger("user_id", thisOption);
}

void cmdProcGroup(char *thisOption) {
	configUpdateInteger("group_id", thisOption);
}

void cmdProcPid(char *thisOption) {
	configUpdateString("pid_file", thisOption);
}

void cmdProcShm(char *thisOption) {
	configUpdateString("shm_file", thisOption);
}

void cmdProcListen(char *thisOption) {
	configUpdateInteger("listen_port", thisOption);
}

void cmdProcPassword(char *thisOption) {
	configUpdateString("agent_password", thisOption);
}

void cmdProcInfostdout(char *thisOption) {
	configUpdateBoolean("info_stdout", thisOption);
}

void cmdProcInfostderr(char *thisOption) {
	configUpdateBoolean("info_stderr", thisOption);
}

void cmdProcInfosyslog(char *thisOption) {
	configUpdateBoolean("info_syslog", thisOption);
}

void cmdProcWarnstdout(char *thisOption) {
	configUpdateBoolean("warn_stdout", thisOption);
}

void cmdProcWarnstderr(char *thisOption) {
	configUpdateBoolean("warn_stderr", thisOption);
}

void cmdProcWarnsyslog(char *thisOption) {
	configUpdateBoolean("warn_syslog", thisOption);
}

void cmdProcbackend(char *thisOption) {
	configUpdateString("storage_engine", thisOption);
}

void cmdProcplainfile(char *thisOption) {
	configUpdateString("plain_file", thisOption);
}

void cmdProcmysqlhost(char *thisOption) {
	configUpdateString("mysql_hostname", thisOption);
}

void cmdProcmysqlsocket(char *thisOption) {
	configUpdateString("mysql_socket", thisOption);
}

void cmdProcmysqlport(char *thisOption) {
	configUpdateInteger("mysql_port", thisOption);
}

void cmdProcmysqldatabase(char *thisOption) {
	configUpdateString("mysql_database", thisOption);
}

void cmdProcmysqluser(char *thisOption) {
	configUpdateString("mysql_username", thisOption);
}

void cmdProcmysqlpassword(char *thisOption) {
	configUpdateString("mysql_password", thisOption);
}

void cmdProcmysqlcompression(char *thisOption) {
	configUpdateBoolean("mysql_compression", thisOption);
}

void cmdProcmysqlencryption(char *thisOption) {
	configUpdateBoolean("mysql_encryption", thisOption);
}
