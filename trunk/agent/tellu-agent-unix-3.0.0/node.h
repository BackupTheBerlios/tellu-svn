char *nodeParseArg(char *);
void nodeCopyArg(char *, char *);

struct nodeStore {
	char node[DATA_STRING_SIZE];
	char domain[DATA_STRING_SIZE];
	char system[DATA_STRING_SIZE];
	char release[DATA_STRING_SIZE];
	char distribution[DATA_STRING_SIZE];
	char machine[DATA_STRING_SIZE];
	char useruid[DATA_STRING_SIZE];
	char usergrp[DATA_STRING_SIZE];
	char usergecos[DATA_STRING_SIZE];
	char userhomedir[DATA_STRING_SIZE];
};

struct distStore {
	char id[DATA_STRING_SIZE];
	char release[DATA_STRING_SIZE];
	char codename[DATA_STRING_SIZE];
	char description[DATA_STRING_SIZE];
};

struct nodeStore nodeData;
