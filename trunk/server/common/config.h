int configBoolean(char *, int *);
int configInteger(char *, int *);
int configString(char *, char *);
char *configParse(char *);

char configConfigFile[CONFIG_SPACE_SIZE];
char configPidFile[CONFIG_SPACE_SIZE];
char configShmFile[CONFIG_SPACE_SIZE];
char configAgentPassword[CONFIG_SPACE_SIZE];
char configStorageEngine[CONFIG_SPACE_SIZE];
char configPlainFile[CONFIG_SPACE_SIZE];

char configLdapHostname[CONFIG_SPACE_SIZE];
char configLdapUsername[CONFIG_SPACE_SIZE];
char configLdapPassword[CONFIG_SPACE_SIZE];
char configLdapAttr[CONFIG_SPACE_SIZE];
char configLdapBase[CONFIG_SPACE_SIZE];
char configLdapFilter[CONFIG_SPACE_SIZE];

char configMysqlHostname[CONFIG_SPACE_SIZE];
char configMysqlSocket[CONFIG_SPACE_SIZE];
char configMysqlDatabase[CONFIG_SPACE_SIZE];
char configMysqlUsername[CONFIG_SPACE_SIZE];
char configMysqlPassword[CONFIG_SPACE_SIZE];

struct mainConfig {
	char *confKeyword;
	char *confArgStr;
	int confArgInt;
	int confArgType;
};

struct mainConfig mainConfigs[] = {
	{ "user_id", NULL, CONFIG_DEFAULT_UID, CONFIG_TYPE_INTEGER },
	{ "group_id", NULL, CONFIG_DEFAULT_GID, CONFIG_TYPE_INTEGER },

	{ "config_file", configConfigFile, 0, CONFIG_TYPE_STRING },
	{ "pid_file", configPidFile, 0, CONFIG_TYPE_STRING },
	{ "shm_file", configShmFile, 0, CONFIG_TYPE_STRING },

	{ "listen_port", NULL, CONFIG_DEFAULT_PORT, CONFIG_TYPE_INTEGER },

	{ "agent_password", configAgentPassword, 0, CONFIG_TYPE_STRING },

	{ "auth_ldap", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "auth_internal", NULL, CONFIG_TYPE_BOOLEAN_YES, CONFIG_TYPE_BOOLEAN },

	{ "ldap_hostname", configLdapHostname, 0, CONFIG_TYPE_STRING },
	{ "ldap_port", NULL, 389, CONFIG_TYPE_INTEGER },
	{ "ldap_username", configLdapUsername, 0, CONFIG_TYPE_STRING },
	{ "ldap_password", configLdapPassword, 0, CONFIG_TYPE_STRING },
	{ "ldap_searchattr", configLdapAttr, 0, CONFIG_TYPE_STRING },
	{ "ldap_searchbase", configLdapBase, 0, CONFIG_TYPE_STRING },
	{ "ldap_searchfilter", configLdapFilter, 0, CONFIG_TYPE_STRING },

	{ "info_stdout", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "info_stderr", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "info_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ "warn_stdout", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "warn_stderr", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "warn_syslog", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ "storage_engine", configStorageEngine, 0, CONFIG_TYPE_STRING },

	{ "plain_file", configPlainFile, 0, CONFIG_TYPE_STRING },

	{ "mysql_hostname", configMysqlHostname, 0, CONFIG_TYPE_STRING },
	{ "mysql_socket", configMysqlSocket, 0, CONFIG_TYPE_STRING },
	{ "mysql_port", NULL, MYSQL_PORT, CONFIG_TYPE_INTEGER },
	{ "mysql_database", configMysqlDatabase, 0, CONFIG_TYPE_STRING },
	{ "mysql_username", configMysqlUsername, 0, CONFIG_TYPE_STRING },
	{ "mysql_password", configMysqlPassword, 0, CONFIG_TYPE_STRING },
	{ "mysql_compression", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },
	{ "mysql_encryption", NULL, CONFIG_TYPE_BOOLEAN_NO, CONFIG_TYPE_BOOLEAN },

	{ NULL, NULL, 0, 0 }
};
