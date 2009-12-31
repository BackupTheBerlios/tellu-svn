struct nodeStore {
	char node[CONFIG_SPACE_SIZE];
	char domain[CONFIG_SPACE_SIZE];
	char system[CONFIG_SPACE_SIZE];
	char release[CONFIG_SPACE_SIZE];
	char machine[CONFIG_SPACE_SIZE];
	char useruid[CONFIG_SPACE_SIZE];
	char usergrp[CONFIG_SPACE_SIZE];
	char usergecos[CONFIG_SPACE_SIZE];
	char userhomedir[CONFIG_SPACE_SIZE];
};

struct nodeStore nodeData;
