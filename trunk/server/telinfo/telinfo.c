#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



int main(int argc, char *argv[]) {
	int i;

	char *confConfig;

	/*
	 *
	 * Read command line and parse configuration file.
	 *
	 */

	cmdRead(argv, argc);

	if((confConfig = configFetch("config_file", &i)) != NULL) {
		if(configRead(confConfig) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}
	else {
		if(configRead(CONFIG_DEFAULT_FILE) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}

	cmdRead(argv, argc);

	/*
	 *
	 * Initialize main thread.
	 *
	 */

	configSetUmask(0077);

	if(configSetLocale(CONFIG_DEFAULT_LOCALE) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to set default locale");
	}

	if(configChangeRoot(CONFIG_DEFAULT_ROOT) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to change root directory");
	}

	if(configCloseInput() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close standard input");
	}

	/*
	 *
	 * Get shared memory info.
	 *
	 */

	shmInfo();

	/*
	 *
	 * Free allocated resources and terminate program.
	 *
	 */

	exit(0);
}
