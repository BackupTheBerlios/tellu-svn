#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/times.h>

#include <ldap.h>
#include <mysql.h>

#include "defines.h"



struct mainInfo {
	int allRunning;								// All subsystems initialized
	int theEnd;								// Request main thread to quit
	int threadEnd;								// Request worker threads to quit
	int timerThreadAccess;							// Timer thread access flag
	int rushThreadCounter;							// Thread pool rush counter
};

struct threadCommandInfo {
	size_t s;								// Thread local variables
	char *statBuffer;							// Thread SQL string pointer
	char *esc1Buffer, *esc2Buffer, *esc3Buffer, *esc4Buffer, *esc5Buffer;	// Thread SQL escape string pointers
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

struct threadHandlerInfo {
	char *buffer;								// Thread task data buffer
	size_t size;								// Thread task data buffer size
};

struct threadDirectoryInfo {
	int i, v;								// Thread local variables
	int *a;									// Thread local variables
	int *ldapPort, *ldapBool;						// Thread directory variable pointers
	char *d;								// Thread directory dn pointer
	char *ldapHostname;							// Thread directory hostname pointer
	char *ldapUsername;							// Thread directory bind username pointer
	char *ldapPassword;							// Thread directory bind password pointer
	char *ldapAttr;								// Thread directory bind attribute pointer
	char *ldapBase;								// Thread directory bind base pointer
	char *ldapFilter;							// Thread directory bind search filter pointer
	char errorString[CONFIG_SPACE_SIZE];					// Thread directory error string space
	char errorSpace[CONFIG_SPACE_SIZE];					// Thread directory error string space
	char dnSpace[CONFIG_SPACE_SIZE];					// Thread directory dn string space

	struct timeval timeVal;							// Thread timeval structure

	LDAP *l;								// Thread ldap directory handle
	LDAPMessage *e, *m;							// Thread ldap directory message handles
};

struct threadStorageInfo {
	size_t t, u, v;								// Thread local variables
	int i, j, e, s, p;							// Thread local variables
	int *a;									// Thread local variables
	unsigned int k, l;							// Thread local variables
	unsigned long *h;							// Thread local variables
	unsigned long q, r;							// Thread local variables
	unsigned long mysqlFlags;						// Thread database connection flags
	int *mysqlPort, *mysqlBool;						// Thread database variable pointers
	char *mysqlHostname;							// Thread database hostname pointer
	char *mysqlSocket;							// Thread database socket pointer
	char *mysqlDatabase;							// Thread database name pointer
	char *mysqlUsername;							// Thread database username pointer
	char *mysqlPassword;							// Thread database password pointer
	char *replyBuffer, *tmpBuffer, *queryBuffer;				// Thread database reply and query pointers
	char *esc1Buffer, *esc2Buffer, *esc3Buffer;				// Thread database escape string pointers
	char errorString[CONFIG_SPACE_SIZE];					// Thread database error string space
	char errorSpace[CONFIG_SPACE_SIZE];					// Thread database error string space
	char cookieSpace[SESSION_COOKIE_SIZE];					// Thread session cookie string space

	struct timeval timeVal;							// Thread timeval structure

	FILE *plainFile;							// Thread plain file handle

	MYSQL mysqlHandle;							// Thread mysql database handle
	MYSQL_RES *mysqlResult;							// Thread mysql database result handle
	MYSQL_ROW mysqlRow;							// Thread mysql database row handle
};

struct threadDbInfo {
	int (*connect)(struct threadStorageInfo *);
	void (*disconnect)(struct threadStorageInfo *);
	void (*escape)(struct threadStorageInfo *, char *, char *);
	void (*push)(struct threadStorageInfo *, char *);
	char *(*pull)(struct threadStorageInfo *, char *);
	char *(*round)(struct threadStorageInfo *, char *);
	void (*free)(struct threadStorageInfo *);
	void (*expire)(struct threadStorageInfo *);
	int (*cookie)(char *, int, struct threadStorageInfo *);
	int (*insert)(char *, int, struct threadStorageInfo *);
	int (*login)(char *, char *, int, int, struct threadStorageInfo *);
	int (*logout)(char *, int, struct threadStorageInfo *);
	int (*session)(char *, char *, int, int, struct threadStorageInfo *);
	int (*permission)(int, char *, char *, char *, int, int, int, struct threadStorageInfo *);
};

struct threadInfo {
	size_t s, t;								// Thread local variables
	ssize_t d;								// Thread local variables
	int *a;									// Thread local variables
	int i, j, k, l, m, n, r;						// Thread local variables
	int co, ps, us;								// Thread local variables
	unsigned int o;								// Thread local variables
	int threadSocket;							// Thread socket handle
	unsigned int tmpSeconds;						// Thread timer temporary seconds
	char *dataPacket, *tmpPacket;						// Thread data packet pointer
	char *dataDeflate;							// Thread data packet pointer for decompression
	char *dataPointer, *dataString, *dataBuffer, *sendBuffer;		// Thread data pointers
	char *magicCookie;							// Magick cookie to authenticate with the client
	char magicSpace[DATA_COOKIE_SIZE + 1];					// Thread magick cookie data space
	char dataSpace[DATA_POINTER_SIZE + 1];					// Thread integer conversion data space
	char errorSpace[CONFIG_SPACE_SIZE];					// Thread error string space
	char logSpace[CONFIG_STRING_SIZE];					// Thread log string space

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

	struct threadHandlerInfo handlerArrays[DATA_ARRAYS_COUNT];		// Thread client request structure

	struct mainInfo *pMainInfo;						// Main thread info structure
	struct threadCommandInfo commandInfo;					// Thread command info structure
	struct threadDbInfo dbInfo;						// Thread db info structure
	struct threadDirectoryInfo directoryInfo;				// Thread directory info structure
	struct threadStorageInfo storageInfo;					// Thread storage info structure
	struct threadCompressInfo compressInfo;					// Thread compress info structure
};

struct cmdArray {
	int level;								// Task required privilege level
	char *task;								// Task name
	void (*constructor)(struct threadInfo *);				// Task constructor pointer
	char *(*allocator)(struct threadInfo *);				// Task allocator pointer
	void (*destroyer)(struct threadInfo *);					// Task destroyer pointer
};
