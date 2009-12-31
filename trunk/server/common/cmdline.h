void cmdProcHelp(char *);
void cmdProcVersion(char *);
void cmdProcLicense(char *);
void cmdProcConfig(char *);
void cmdProcUser(char *);
void cmdProcGroup(char *);
void cmdProcPid(char *);
void cmdProcShm(char *);
void cmdProcListen(char *);
void cmdProcPassword(char *);
void cmdProcInfostdout(char *);
void cmdProcInfostderr(char *);
void cmdProcInfosyslog(char *);
void cmdProcWarnstdout(char *);
void cmdProcWarnstderr(char *);
void cmdProcWarnsyslog(char *);
void cmdProcbackend(char *);
void cmdProcplainfile(char *);
void cmdProcmysqlhost(char *);
void cmdProcmysqlsocket(char *);
void cmdProcmysqlport(char *);
void cmdProcmysqldatabase(char *);
void cmdProcmysqluser(char *);
void cmdProcmysqlpassword(char *);
void cmdProcmysqlcompression(char *);
void cmdProcmysqlencryption(char *);

struct mainCmdline {
	char *optShort;
	char *optLong;
	char *optDesc;
	char *optDefault;
	int optRequired;
	void (*fp)(char *);
};

struct mainCmdline mainCmdlines[] = {
	{ "", "", "Helpful options", "", 0, NULL },

	{ "-h", "--help", "Display help page", "", CONFIG_OPTION_NOTREQUIRED, cmdProcHelp },
	{ "-v", "--version", "Display version information", "", CONFIG_OPTION_NOTREQUIRED, cmdProcVersion },
	{ "-l", "--license", "Display license information", "", CONFIG_OPTION_NOTREQUIRED, cmdProcLicense },

	{ "", "", "Common options", "", 0, NULL },

	{ "-c", "--config", "Config file to use", CONFIG_DEFAULT_FILE, CONFIG_OPTION_REQUIRED, cmdProcConfig },
	{ "-u", "--user", "Switch to this user id", "", CONFIG_OPTION_REQUIRED, cmdProcUser },
	{ "-g", "--group", "Switch to this group id", "", CONFIG_OPTION_REQUIRED, cmdProcGroup },
	{ "-p", "--pid", "Process id file to use", CONFIG_DEFAULT_PID, CONFIG_OPTION_REQUIRED, cmdProcPid },
	{ "-s", "--shm", "Process shared memory id file to use", CONFIG_DEFAULT_SHM, CONFIG_OPTION_REQUIRED, cmdProcShm },
	{ "-o", "--port", "Port to listen", CONFIG_DEFAULT_PORT_S, CONFIG_OPTION_REQUIRED, cmdProcListen },
	{ "-w", "--password", "Agent password", "", CONFIG_OPTION_REQUIRED, cmdProcPassword },

	{ "", "", "Output options", "", 0, NULL },

	{ "-io", "--infostdout", "Write information to stdout", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfostdout },
	{ "-ie", "--infostderr", "Write information to stderr", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfostderr },
	{ "-is", "--infosyslog", "Write information to syslog", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfosyslog },
	{ "-wo", "--warnstdout", "Write warnings and errors to stdout", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnstdout },
	{ "-we", "--warnstderr", "Write warnings and errors to stderr", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnstderr },
	{ "-ws", "--warnsyslog", "Write warnings and errors to syslog", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnsyslog },

	{ "", "", "Storage engine options", "", 0, NULL },

	{ "-e", "--engine", "Storage engine to use, '" CONFIG_DEFAULT_ENGINEMYSQL "' or '" CONFIG_DEFAULT_ENGINEPLAIN "'", CONFIG_DEFAULT_ENGINE, CONFIG_OPTION_REQUIRED, cmdProcbackend },

	{ "", "", "Plain storage engine options", "", 0, NULL },

	{ "-pf", "--plainfile", "File for saving plain data", CONFIG_DEFAULT_PLAINFILE, CONFIG_OPTION_REQUIRED, cmdProcplainfile },

	{ "", "", "MySQL storage engine options", "", 0, NULL },

	{ "-mh", "--mysqlhost", "MySQL hostname", MYSQL_HOSTNAME, CONFIG_OPTION_REQUIRED, cmdProcmysqlhost },
	{ "-ms", "--mysqlsocket", "MySQL socket", MYSQL_SOCKET, CONFIG_OPTION_REQUIRED, cmdProcmysqlsocket },
	{ "-mp", "--mysqlport", "MySQL port", MYSQL_PORT_S, CONFIG_OPTION_REQUIRED, cmdProcmysqlport },
	{ "-md", "--mysqldatabase", "MySQL database", MYSQL_DATABASE, CONFIG_OPTION_REQUIRED, cmdProcmysqldatabase },
	{ "-mu", "--mysqluser", "MySQL username", MYSQL_USERNAME, CONFIG_OPTION_REQUIRED, cmdProcmysqluser },
	{ "-mw", "--mysqlpassword", "MySQL password", MYSQL_PASSWORD, CONFIG_OPTION_REQUIRED, cmdProcmysqlpassword },
	{ "-mc", "--mysqlcompression", "MySQL compressed protocol", "", CONFIG_OPTION_NOTREQUIRED, cmdProcmysqlcompression },
	{ "-me", "--mysqlencryption", "MySQL SSL encrypted protocol", "", CONFIG_OPTION_NOTREQUIRED, cmdProcmysqlencryption },

	{ NULL, NULL, NULL, NULL, 0, NULL }
};
