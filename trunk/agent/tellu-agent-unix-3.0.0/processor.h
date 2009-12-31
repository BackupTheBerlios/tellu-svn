char *cpuParseArg(char *);
void cpuCopyArg(char *, char *);

struct cpuStore {
	char cpus[DATA_STRING_SIZE];
	char cores[DATA_STRING_SIZE];
	char siblings[DATA_STRING_SIZE];
	char mhz[DATA_STRING_SIZE];
	char cache[DATA_STRING_SIZE];
	char mips[DATA_STRING_SIZE];
};
