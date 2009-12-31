int configBoolean(char *, int *);
int configInteger(char *, int *);
int configString(char *, char *);
char *configParse(char *);

char configConfigFile[CONFIG_SPACE_SIZE];
char configShmFile[CONFIG_SPACE_SIZE];

struct mainConfig {
	char *confKeyword;
	char *confArgStr;
	int confArgInt;
	int confArgType;
};

struct mainConfig mainConfigs[] = {
	{ "config_file", configConfigFile, 0, CONFIG_TYPE_STRING },
	{ "shm_file", configShmFile, 0, CONFIG_TYPE_STRING },

	{ "info_stdout", NULL, CONFIG_TYPE_BOOLEAN_YES, CONFIG_TYPE_BOOLEAN },
	{ "info_stderr", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "info_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ "warn_stdout", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "warn_stderr", NULL, CONFIG_TYPE_BOOLEAN_YES, CONFIG_TYPE_BOOLEAN },
	{ "warn_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ NULL, NULL, 0, 0 }
};
