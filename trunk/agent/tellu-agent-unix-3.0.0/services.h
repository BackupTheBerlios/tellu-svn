char *servParseArg(char *);
void servCopyArg(char *, char *);

struct servStore {
	char cmdline[DATA_STRING_SIZE];
	char name[DATA_STRING_SIZE];
	char state[DATA_STRING_SIZE];
	char pid[DATA_STRING_SIZE];
	char ppid[DATA_STRING_SIZE];
	char uid[DATA_STRING_SIZE];
	char gid[DATA_STRING_SIZE];
	char threads[DATA_STRING_SIZE];
	char vmdata[DATA_STRING_SIZE];
	char vmexe[DATA_STRING_SIZE];
	char vmhwm[DATA_STRING_SIZE];
	char vmlib[DATA_STRING_SIZE];
	char vmpeak[DATA_STRING_SIZE];
	char vmpte[DATA_STRING_SIZE];
	char vmrss[DATA_STRING_SIZE];
	char vmsize[DATA_STRING_SIZE];
	char vmstk[DATA_STRING_SIZE];
	char rchar[DATA_STRING_SIZE];
	char wchar[DATA_STRING_SIZE];
	char syscr[DATA_STRING_SIZE];
	char syscw[DATA_STRING_SIZE];
	char rbyte[DATA_STRING_SIZE];
	char wbyte[DATA_STRING_SIZE];
};
