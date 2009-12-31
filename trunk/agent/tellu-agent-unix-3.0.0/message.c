#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "declarations.h"



void dbusMessage(int fatalError, char *infoMessage, DBusError *dbusError) {
	char newString[CONFIG_STRING_SIZE];

	if(infoMessage != NULL) {
		if(dbus_error_is_set(dbusError)) {
			snprintf(newString, sizeof(newString), "%s: %s: %s%c", infoMessage, dbusError->name, dbusError->message, 0);
		}
		else {
			snprintf(newString, sizeof(newString), "%s.%c", infoMessage, 0);
		}
	}
	else {
		if(dbus_error_is_set(dbusError)) {
			snprintf(newString, sizeof(newString), "%s: %s%c", dbusError->name, dbusError->message, 0);
		}
		else {
			return;
		}
	}

	fprintf(stderr, "%s%c%c", newString, 10, 0);

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}

void infoMessage(int fatalError, char *infoMessage) {
	char newString[CONFIG_STRING_SIZE];

	if(infoMessage != NULL) {
		snprintf(newString, sizeof(newString), "%s.%c", infoMessage, 0);
	}
	else {
		return;
	}

	fprintf(stdout, "%s%c%c", newString, 10, 0);

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}

void warningMessage(int fatalError, char *warningMessage) {
	char *newError;
	char newString[CONFIG_STRING_SIZE];

	if(errno == 0) {
		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s.%c", warningMessage, 0);
		}
		else {
			return;
		}
	}
	else {
		newError = strerror(errno);

		if(warningMessage != NULL) {
			snprintf(newString, sizeof(newString), "%s: %s%c", warningMessage, newError, 0);
		}
		else {
			snprintf(newString, sizeof(newString), "%s%c", newError, 0);
		}
	}

	fprintf(stderr, "%s%c%c", newString, 10, 0);

	if(fatalError == ERROR_FATAL) {
		exit(errno);
	}
}
