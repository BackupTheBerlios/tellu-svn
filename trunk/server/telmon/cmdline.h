void cmdProcHelp(char *);
void cmdProcVersion(char *);
void cmdProcLicense(char *);
void cmdProcConfig(char *);
void cmdProcServer(char *);
void cmdProcPort(char *);
void cmdProcFreq(char *);
void cmdProcPassword(char *);
void cmdProcInfostdout(char *);
void cmdProcInfostderr(char *);
void cmdProcInfosyslog(char *);
void cmdProcWarnstdout(char *);
void cmdProcWarnstderr(char *);
void cmdProcWarnsyslog(char *);

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
	{ "-s", "--server", "Telmond server name to connect", CONFIG_DEFAULT_SERVER, CONFIG_OPTION_REQUIRED, cmdProcServer },
	{ "-o", "--port", "Telmond server port to connect", CONFIG_DEFAULT_PORT_S, CONFIG_OPTION_REQUIRED, cmdProcPort },
	{ "-f", "--frequency", "Update frequency in seconds", CONFIG_DEFAULT_FREQUENCY_S, CONFIG_OPTION_REQUIRED, cmdProcFreq },
	{ "-w", "--password", "Server password", "", CONFIG_OPTION_REQUIRED, cmdProcPassword },

	{ "", "", "Output options", "", 0, NULL },

	{ "-io", "--infostdout", "Write information to stdout", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfostdout },
	{ "-ie", "--infostderr", "Write information to stderr", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfostderr },
	{ "-is", "--infosyslog", "Write information to syslog", "", CONFIG_OPTION_NOTREQUIRED, cmdProcInfosyslog },
	{ "-wo", "--warnstdout", "Write warnings and errors to stdout", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnstdout },
	{ "-we", "--warnstderr", "Write warnings and errors to stderr", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnstderr },
	{ "-ws", "--warnsyslog", "Write warnings and errors to syslog", "", CONFIG_OPTION_NOTREQUIRED, cmdProcWarnsyslog },

	{ NULL, NULL, NULL, NULL, 0, NULL }
};
