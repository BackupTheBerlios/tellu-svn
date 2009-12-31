int configBoolean(char *, int *);
int configInteger(char *, int *);
int configString(char *, char *);
char *configParse(char *);

char configServer[CONFIG_SPACE_SIZE];
char configDomain[CONFIG_SPACE_SIZE];
char configPassword[CONFIG_SPACE_SIZE];

struct mainConfig {
	char *confKeyword;
	char *confArgStr;
	int confArgInt;
	int confArgType;
};

struct mainConfig mainConfigs[] = {
	{ "tellud_server", configServer, 0, CONFIG_TYPE_STRING },
	{ "tellud_port", NULL, 1700, CONFIG_TYPE_INTEGER },

	{ "domain_override", configDomain, 0, CONFIG_TYPE_STRING },
	{ "server_password", configPassword, 0, CONFIG_TYPE_STRING },

	{ "start_portscan", NULL, 0, CONFIG_TYPE_INTEGER },
	{ "end_portscan", NULL, 0, CONFIG_TYPE_INTEGER },

	{ "disabled_functionality", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "compressed_protocol", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "looping_delay", NULL, 0, CONFIG_TYPE_INTEGER },

	{ NULL, NULL, 0, 0 }
};
