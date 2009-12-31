#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/times.h>

#include <mysql.h>

#include "defines.h"



struct mainInfo {
	int allRunning;								// All subsystems initialized
	int theEnd;								// Request main thread to quit
	int threadEnd;								// Request worker threads to quit
	int timerThreadAccess;							// Timer thread access flag
	int rushThreadCounter;							// Thread pool rush counter
};

struct threadDaemonInfo {
	unsigned long long workersAvailable;					// Worker threads available
	unsigned long long serverStarted;					// Server starting time
	unsigned long long lastTask;						// Agent last connect time
	unsigned long long totalTasks;						// Agents served
	unsigned long long infoTime;						// Info message timestamp
	unsigned long long errorTime;						// Error message timestamp
	char infoMessage[CONFIG_SPACE_SIZE];					// Info message
	char errorMessage[CONFIG_SPACE_SIZE];					// Error message
};

struct threadCompressInfo {
	int i, n;								// Thread local variables
	unsigned int o, w, x;							// Thread local variables
	int jipInput, jipOutput;						// Thread offset variables
	int jipBitBuffer, jipBitCount;						// Thread bitcount variables
	unsigned char *jipAppend;						// Thread append buffer pointer
	unsigned char *jipString;						// Thread string buffer pointer
	unsigned int *jipPrefix;						// Thread prefix buffer pointer
	unsigned char jipDecode[4096];						// Thread decode buffer
};

struct threadStorageInfo {
	size_t t;								// Thread local variables
	int i, s, p;								// Thread local variables
	int *a;									// Thread local variables
	unsigned int k, l;							// Thread local variables
	unsigned long r;							// Thread local variables
	unsigned long mysqlFlags;						// Thread database connection flags
	unsigned long long id;							// Thread database id
	int *mysqlPort, *mysqlBool;						// Thread database variable pointers
	char *mysqlHostname;							// Thread database hostname pointer
	char *mysqlSocket;							// Thread database socket pointer
	char *mysqlDatabase;							// Thread database name pointer
	char *mysqlUsername;							// Thread database username pointer
	char *mysqlPassword;							// Thread database password pointer
	char *replyBuffer;							// Thread database query reply pointer
	char errorString[CONFIG_SPACE_SIZE];					// Thread database error string space
	char errorSpace[CONFIG_SPACE_SIZE];					// Thread database error string space

	FILE *plainFile;							// Thread plain file handle

	MYSQL mysqlHandle;							// Thread mysql database handle
	MYSQL_RES *mysqlResult;							// Thread mysql database result handle
	MYSQL_ROW mysqlRow;							// Thread mysql database row handle
};

struct threadDbInfo {
	int (*connect)(struct threadStorageInfo *);				// Connection routine
	void (*disconnect)(struct threadStorageInfo *);				// Disconnection routine
	void (*escape)(struct threadStorageInfo *, char *, char *);		// String escape routine
	void (*push)(struct threadStorageInfo *, char *);			// String storing routine
	char *(*pull)(struct threadStorageInfo *, char *);			// String fetching routine
	void (*free)(struct threadStorageInfo *);				// String free fetching routine
};

struct threadInfo {
	size_t s, t;								// Thread local variables
	ssize_t d;								// Thread local variables
	int *a;									// Thread local variables
	int i, j, k, l, n, r;							// Thread local variables
	int co, ps, us;								// Thread local variables
	unsigned int o;								// Thread local variables
	int threadSocket;							// Thread socket handle
	unsigned int tmpSeconds;						// Thread timer temporary seconds
	char *dataPacket, *tmpPacket;						// Thread data packet pointer
	char *dataDeflate;							// Thread data packet pointer for decompression
	char *dataPointer, *dataBuffer, *dataString, *sendBuffer, *statBuffer;	// Thread data pointers
	char *magicCookie;							// Magick cookie to authenticate with the client
	char magicSpace[DATA_COOKIE_SIZE + 1];					// Thread magick cookie data space
	char dataSpace[DATA_POINTER_SIZE + 1];					// Thread integer conversion data space
	char errorSpace[CONFIG_SPACE_SIZE];					// Thread error string space
	char itemSpace[CONFIG_SPACE_SIZE];					// Thread item string space

	long ticksPerSec;							// Clock ticks per second
	unsigned int threadReady;						// Thread task finished flag
	unsigned int threadTasks;						// Thread task counter
	pthread_t threadID;							// Thread identification
	pthread_attr_t threadAttr;						// Thread detach state attribute
	pthread_cond_t threadCond;						// Thread condition variable
	pthread_mutex_t threadMutex;						// Thread mutex
	clock_t clockBegin;							// Thread begin clock
	clock_t clockEnd;							// Thread end clock
	struct tms beginClock;							// Thread begin clock structure
	struct tms endClock;							// Thread end clock structure
	struct timeval timeVal;							// Thread timeval structure
	struct tm *timeNow;							// Thread localtime structure

	struct mainInfo *pMainInfo;						// Main thread info structure
	struct threadDaemonInfo daemonInfo;					// Thread daemon info structure
	struct threadDbInfo dbInfo;						// Thread db info structure
	struct threadStorageInfo storageInfo;					// Thread storage info structure
	struct threadCompressInfo compressInfo;					// Thread compress info structure
};

struct cmdArray {
	char *task;								// Task name
	char *(*allocator)(struct threadInfo *);				// Task allocator pointer
	void (*destroyer)(char *);						// Task destroyer pointer
};
