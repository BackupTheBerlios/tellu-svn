int configBoolean(char *, int *);
int configInteger(char *, int *);
int configString(char *, char *);
char *configParse(char *);

char configAppName[CONFIG_SPACE_SIZE];
char configAppVersion[CONFIG_SPACE_SIZE];
char configConfigFile[CONFIG_SPACE_SIZE];
char configServer[CONFIG_SPACE_SIZE];
char configAgentPassword[CONFIG_SPACE_SIZE];

struct mainConfig {
	char *confKeyword;
	char *confArgStr;
	int confArgInt;
	int confArgType;
};

struct mainConfig mainConfigs[] = {
	{ "application_name", configAppName, 0, CONFIG_TYPE_STRING },
	{ "application_version", configAppVersion, 0, CONFIG_TYPE_STRING },

	{ "config_file", configConfigFile, 0, CONFIG_TYPE_STRING },

	{ "telmond_server", configServer, 0, CONFIG_TYPE_STRING },
	{ "telmond_port", NULL, CONFIG_DEFAULT_PORT, CONFIG_TYPE_INTEGER },

	{ "update_frequency", NULL, CONFIG_DEFAULT_FREQUENCY, CONFIG_TYPE_INTEGER },

	{ "server_password", configAgentPassword, 0, CONFIG_TYPE_STRING },

	{ "monitor_server", NULL, DAEMON_TELLUD, CONFIG_TYPE_INTEGER },
	{ "save_settings", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_INTEGER },

	{ "info_stdout", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "info_stderr", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "info_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ "warn_stdout", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "warn_stderr", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "warn_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ NULL, NULL, 0, 0 }
};
