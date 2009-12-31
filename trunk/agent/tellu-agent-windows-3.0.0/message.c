#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"



void infoMessage(int fatalError, LPCSTR infoMessage) {
	MessageBox(NULL, infoMessage, APPLICATION_NAME " " APPLICATION_VERSION " information", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);

	if(fatalError == ERROR_FATAL) {
		ExitProcess(fatalError);
	}
}

void warningMessage(int fatalError, LPCSTR warningMessage) {
	LPVOID newString;
	TCHAR newMessage[CONFIG_STRING_SIZE];

	if(fatalError == ERROR_NOERROR) {
		MessageBox(NULL, warningMessage, APPLICATION_NAME " " APPLICATION_VERSION " warning", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}
	else {
		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &newString, 0, NULL)) {
			_snprintf(newMessage, sizeof(newMessage), "%s:%c%c%s%c", warningMessage, 13, 10, newString, 0);

			MessageBox(NULL, newMessage, APPLICATION_NAME " " APPLICATION_VERSION " warning", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

			LocalFree(newString);
		}
		else {
			MessageBox(NULL, warningMessage, APPLICATION_NAME " " APPLICATION_VERSION " warning", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		}

		if(fatalError == ERROR_FATAL) {
			ExitProcess(fatalError);
		}
	}
}
