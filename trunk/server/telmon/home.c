#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

#include "declarations.h"
#include "defines.h"



char *getHome(void) {
	char *dirHome;

	if((dirHome = getenv("HOME")) == NULL) {
		struct passwd *pwdEntry;

		if((pwdEntry = getpwuid(getuid())) == NULL) {
			return(NULL);
		}

		dirHome = pwdEntry->pw_dir;
	}

	return(dirHome);
}
