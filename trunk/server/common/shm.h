struct statEntry {
	unsigned long long telludEntrySize;					// Size of each structure entry
	unsigned long long telludWorkersAvailable;				// Worker threads available
	unsigned long long telludServerStarted;					// Server starting time
	unsigned long long telludLastTask;					// Agent last connect time
	unsigned long long telludTotalTasks;					// Agents served
	unsigned long long telludTotalServed;					// Agents served by hour
	unsigned long long telludThreadTasks[THREAD_TELLUD];			// Agents served by thread
	unsigned long long telludMessageLength;					// Message length
	unsigned long long telludInfoTime;					// Info message timestamp
	unsigned long long telludErrorTime;					// Error message timestamp
	char telludInfoMessage[CONFIG_SPACE_SIZE];				// Info message
	char telludErrorMessage[CONFIG_SPACE_SIZE];				// Error message

	unsigned long long telmondEntrySize;					// Size of each structure entry
	unsigned long long telmondWorkersAvailable;				// Worker threads available
	unsigned long long telmondServerStarted;				// Server starting time
	unsigned long long telmondLastTask;					// Agent last connect time
	unsigned long long telmondTotalTasks;					// Agents served
	unsigned long long telmondTotalServed;					// Agents served by hour
	unsigned long long telmondThreadTasks[THREAD_TELMOND];			// Agents served by thread
	unsigned long long telmondMessageLength;				// Message length
	unsigned long long telmondInfoTime;					// Info message timestamp
	unsigned long long telmondErrorTime;					// Error message timestamp
	char telmondInfoMessage[CONFIG_SPACE_SIZE];				// Info message
	char telmondErrorMessage[CONFIG_SPACE_SIZE];				// Error message

	unsigned long long telskindEntrySize;					// Size of each structure entry
	unsigned long long telskindWorkersAvailable;				// Worker threads available
	unsigned long long telskindServerStarted;				// Server starting time
	unsigned long long telskindLastTask;					// Agent last connect time
	unsigned long long telskindTotalTasks;					// Agents served
	unsigned long long telskindTotalServed;					// Agents served by hour
	unsigned long long telskindThreadTasks[THREAD_TELSKIND];		// Agents served by thread
	unsigned long long telskindMessageLength;				// Message length
	unsigned long long telskindInfoTime;					// Info message timestamp
	unsigned long long telskindErrorTime;					// Error message timestamp
	char telskindInfoMessage[CONFIG_SPACE_SIZE];				// Info message
	char telskindErrorMessage[CONFIG_SPACE_SIZE];				// Error message
};

struct statEntry *statBuffer;

int shmId;
