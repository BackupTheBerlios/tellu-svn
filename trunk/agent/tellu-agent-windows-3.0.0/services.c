#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

#include "declarations.h"
#include "defines.h"



char *servGetCount(struct paramInfo * pi) {
	unsigned int i, k, l;

	char *newBuffer;

	FARPROC closeHandle, createSnapshot, processFirst, processNext;
	HANDLE newSnapshot;
	HMODULE modKernel;
	PROCESSENTRY32 newEntry;

	if((modKernel = LoadLibrary("kernel32.dll")) == NULL) {
		return(NULL);
	}

	closeHandle = GetProcAddress(modKernel, "CloseHandle");
	createSnapshot = GetProcAddress(modKernel, "CreateToolhelp32Snapshot");
	processFirst = GetProcAddress(modKernel, "Process32First");
	processNext = GetProcAddress(modKernel, "Process32Next");

	if(closeHandle == NULL || createSnapshot == NULL || processFirst == NULL || processNext == NULL) {
		FreeLibrary(modKernel);

		return(NULL);
	}

	if((newSnapshot = (HANDLE) (createSnapshot)(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create system snapshot");

		FreeLibrary(modKernel);

		return(NULL);
	}

	k = 0;
	l = 0;

	newEntry.dwSize = sizeof(newEntry);

	if((processFirst)(newSnapshot, &newEntry) == TRUE) {
		l += newEntry.cntThreads;
		k++;

		for(i = 0; i < 65535; i++) {
			newEntry.dwSize = sizeof(newEntry);

			if((processNext)(newSnapshot, &newEntry) == TRUE) {
				l += newEntry.cntThreads;
				k++;
			}
			else {
				break;
			}
		}
	}

	(closeHandle)(newSnapshot);

	FreeLibrary(modKernel);

	if((newBuffer = malloc(DATA_STRING_SIZE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process count buffer");

		return(NULL);
	}

	_snprintf(newBuffer, DATA_STRING_SIZE, "%lu%c%lu%c", k, ITEM_SEPARATOR, l, 0);

	return(newBuffer);
}

void servFreeCount(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *servGetProcesses(struct paramInfo * pi) {
	unsigned int i, k;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	FARPROC closeHandle, createSnapshot, processFirst, processNext, processInfo;
	HANDLE newSnapshot, newProcess;
	HMODULE modKernel, modPsapi;
	PROCESS_MEMORY_COUNTERS newCounter;
	PROCESSENTRY32 newEntry;
	SIZE_T vmPeak, vmSize;

	if((modKernel = LoadLibrary("kernel32.dll")) == NULL) {
		return(NULL);
	}

	closeHandle = GetProcAddress(modKernel, "CloseHandle");
	createSnapshot = GetProcAddress(modKernel, "CreateToolhelp32Snapshot");
	processFirst = GetProcAddress(modKernel, "Process32First");
	processNext = GetProcAddress(modKernel, "Process32Next");

	if(closeHandle == NULL || createSnapshot == NULL || processFirst == NULL || processNext == NULL) {
		FreeLibrary(modKernel);

		return(NULL);
	}

	if((newSnapshot = (HANDLE) (createSnapshot)(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create system snapshot");

		FreeLibrary(modKernel);

		return(NULL);
	}

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process info buffer");

		(closeHandle)(newSnapshot);

		FreeLibrary(modKernel);

		return(NULL);
	}

	modPsapi = NULL;
	processInfo = NULL;

	if((modPsapi = LoadLibrary("psapi.dll")) != NULL) {
		if((processInfo = GetProcAddress(modPsapi, "GetProcessMemoryInfo")) == NULL) {
			processInfo = GetProcAddress(modPsapi, "K32GetProcessMemoryInfo");
		}

		if(processInfo == NULL) {
			FreeLibrary(modPsapi);

			if((modPsapi = LoadLibrary("kernel32.dll")) != NULL) {
				if((processInfo = GetProcAddress(modPsapi, "GetProcessMemoryInfo")) == NULL) {
					processInfo = GetProcAddress(modPsapi, "K32GetProcessMemoryInfo");
				}
			}
		}
	}
	else {
		if((modPsapi = LoadLibrary("kernel32.dll")) != NULL) {
			if((processInfo = GetProcAddress(modPsapi, "GetProcessMemoryInfo")) == NULL) {
				processInfo = GetProcAddress(modPsapi, "K32GetProcessMemoryInfo");
			}
		}
	}

	k = 0;

	newEntry.dwSize = sizeof(newEntry);

	if((processFirst)(newSnapshot, &newEntry) == TRUE) {
		vmPeak = 0;
		vmSize = 0;

		if((newProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, newEntry.th32ProcessID)) != NULL) {
			if((processInfo)(newProcess, &newCounter, sizeof(newCounter)) != 0) {
				vmPeak = newCounter.PeakWorkingSetSize;
				vmSize = newCounter.WorkingSetSize;

				vmPeak /= 1000;
				vmSize /= 1000;
			}

			(closeHandle)(newProcess);
		}

		k += _snprintf(newBuffer + k, newBuflen, "%s%c%s%cS%c%lu%c%lu%c%lu%c0%c0%c0%c0%c%lu%c0%c0%c%lu%c0%c0%c0%c0%c0%c0%c0%c0%c0%c", newEntry.szExeFile, ITEM_SEPARATOR, newEntry.szExeFile, ITEM_SEPARATOR, ITEM_SEPARATOR, newEntry.th32ProcessID, ITEM_SEPARATOR, newEntry.th32ParentProcessID, ITEM_SEPARATOR, newEntry.cntThreads, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, vmPeak, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, vmSize, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_DELIMITER);

		for(i = 0; i < 65535; i++) {
			newEntry.dwSize = sizeof(newEntry);

			if((processNext)(newSnapshot, &newEntry) == TRUE) {
				vmPeak = 0;
				vmSize = 0;

				if((newProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, newEntry.th32ProcessID)) != NULL) {
					if((processInfo)(newProcess, &newCounter, sizeof(newCounter)) != 0) {
						vmPeak = newCounter.PeakWorkingSetSize;
						vmSize = newCounter.WorkingSetSize;

						vmPeak /= 1000;
						vmSize /= 1000;
					}

					(closeHandle)(newProcess);
				}

				newBufcur = strlen(newEntry.szExeFile) + 64;

				if(newBuflen - newBuffil <= newBufcur) {
					newBuflen += DATA_BLOCK_SIZE;

					if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for process info buffer");

						free(newBuffer);

						(closeHandle)(newSnapshot);

						FreeLibrary(modKernel);

						if(modPsapi != NULL) {
							FreeLibrary(modPsapi);
						}

						return(NULL);
					}

					newBuffer = tmpBuffer;
				}

				k += _snprintf(newBuffer + k, newBuflen, "%s%c%s%cS%c%lu%c%lu%c%lu%c0%c0%c0%c0%c%lu%c0%c0%c%lu%c0%c0%c0%c0%c0%c0%c0%c0%c0%c", newEntry.szExeFile, ITEM_SEPARATOR, newEntry.szExeFile, ITEM_SEPARATOR, ITEM_SEPARATOR, newEntry.th32ProcessID, ITEM_SEPARATOR, newEntry.th32ParentProcessID, ITEM_SEPARATOR, newEntry.cntThreads, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, vmPeak, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, vmSize, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_DELIMITER);

				newBuffil += newBufcur;
			}
			else {
				break;
			}
		}
	}

	(closeHandle)(newSnapshot);

	FreeLibrary(modKernel);

	if(modPsapi != NULL) {
		FreeLibrary(modPsapi);
	}

	if(k > 0) {
		k--;
	}

	newBuffer[k] = 0;

	return(newBuffer);
}

void servFreeProcesses(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *servGetServices(struct paramInfo * pi) {
	unsigned int i, k;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	DWORD newDummy, newNeeded, newReturned, newResume;
	FARPROC openManager, closeManager, enumServices;
	HMODULE modAdvapi;
	SC_HANDLE newKey;
	ENUM_SERVICE_STATUS newInfo;
	LPENUM_SERVICE_STATUS newArray;

	if((modAdvapi = LoadLibrary("advapi32.dll")) == NULL) {
		return(NULL);
	}

	openManager = GetProcAddress(modAdvapi, "OpenSCManagerA");
	closeManager = GetProcAddress(modAdvapi, "CloseServiceHandle");
	enumServices = GetProcAddress(modAdvapi, "EnumServicesStatusA");

	if(openManager == NULL || closeManager == NULL || enumServices == NULL) {
		FreeLibrary(modAdvapi);

		return(NULL);
	}

	if((newKey = (SC_HANDLE) (openManager)(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to open service control manager");

		FreeLibrary(modAdvapi);

		return(NULL);
	}

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for service info buffer");

		(closeManager)(newKey);

		FreeLibrary(modAdvapi);

		return(NULL);
	}

	k = 0;
	newResume = 0;

	if((enumServices)(newKey, SERVICE_WIN32, SERVICE_ACTIVE, &newInfo, 1, &newNeeded, &newReturned, &newResume) == 0) {
		if(GetLastError() == ERROR_MORE_DATA) {
			if((newArray = malloc(newNeeded)) != NULL) {
				newResume = 0;

				if((enumServices)(newKey, SERVICE_WIN32, SERVICE_ACTIVE, newArray, newNeeded, &newDummy, &newReturned, &newResume) == 0) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
				}
				else {
					for(i = 0; i < newReturned; i++) {
						if(newArray[i].lpDisplayName != NULL && newArray[i].lpDisplayName[0] != 0 && newArray[i].lpServiceName != NULL && newArray[i].lpServiceName[0] != 0) {
							newBufcur = strlen(newArray[i].lpDisplayName) + strlen(newArray[i].lpServiceName) + 64;

							if(newBuflen - newBuffil <= newBufcur) {
								newBuflen += DATA_BLOCK_SIZE;

								if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for service info buffer");

									free(newArray);
									free(newBuffer);

									(closeManager)(newKey);

									FreeLibrary(modAdvapi);

									return(NULL);
								}

								newBuffer = tmpBuffer;
							}

							k += _snprintf(newBuffer + k, newBuflen, "%s%c%s%cA%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c", newArray[i].lpServiceName, ITEM_SEPARATOR, newArray[i].lpDisplayName, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_DELIMITER);

							newBuffil += newBufcur;
						}
					}
				}

				free(newArray);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for service info buffer");
			}
		}
		else {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
		}
	}
	else {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
	}

	newResume = 0;

	if((enumServices)(newKey, SERVICE_WIN32, SERVICE_INACTIVE, &newInfo, 1, &newNeeded, &newReturned, &newResume) == 0) {
		if(GetLastError() == ERROR_MORE_DATA) {
			if((newArray = malloc(newNeeded)) != NULL) {
				newResume = 0;

				if((enumServices)(newKey, SERVICE_WIN32, SERVICE_INACTIVE, newArray, newNeeded, &newDummy, &newReturned, &newResume) == 0) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
				}
				else {
					for(i = 0; i < newReturned; i++) {
						if(newArray[i].lpDisplayName != NULL && newArray[i].lpDisplayName[0] != 0 && newArray[i].lpServiceName != NULL && newArray[i].lpServiceName[0] != 0) {
							newBufcur = strlen(newArray[i].lpDisplayName) + strlen(newArray[i].lpServiceName) + 64;

							if(newBuflen - newBuffil <= newBufcur) {
								newBuflen += DATA_BLOCK_SIZE;

								if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for service info buffer");

									free(newArray);
									free(newBuffer);

									(closeManager)(newKey);

									FreeLibrary(modAdvapi);

									return(NULL);
								}

								newBuffer = tmpBuffer;
							}

							k += _snprintf(newBuffer + k, newBuflen, "%s%c%s%cS%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c0%c", newArray[i].lpServiceName, ITEM_SEPARATOR, newArray[i].lpDisplayName, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_SEPARATOR, ITEM_DELIMITER);

							newBuffil += newBufcur;
						}
					}
				}

				free(newArray);
			}
			else {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for service info buffer");
			}
		}
		else {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
		}
	}
	else {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch running services");
	}

	(closeManager)(newKey);

	FreeLibrary(modAdvapi);

	if(k > 0) {
		k--;
	}

	newBuffer[k] = 0;

	return(newBuffer);
}

void servFreeServices(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
