#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iphlpapi.h>

#include "declarations.h"
#include "defines.h"



char *netGetInterfaceData(struct paramInfo * pi) {
	unsigned int i, k, l;

	char *newBuffer, *tmpBuffer;

	size_t newBuflen, newBufcur, newBuffil;

	FARPROC getAdaptersInfo;
	HMODULE modIphlp;
	IP_ADAPTER_INFO newInfo;
	PIP_ADAPTER_INFO newArray, newPointer;
	TCHAR newMac[CONFIG_STRING_SIZE];
	ULONG newLength;

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for network interface buffer");

		return(NULL);
	}

	l = 0;

	if((modIphlp = LoadLibrary("iphlpapi.dll")) != NULL) {
		if((getAdaptersInfo = GetProcAddress(modIphlp, "GetAdaptersInfo")) != NULL) {
			newLength = 1;

			if((getAdaptersInfo)(&newInfo, &newLength) == ERROR_BUFFER_OVERFLOW) {
				if((newArray = malloc(newLength)) != NULL) {
					if((getAdaptersInfo)(newArray, &newLength) == ERROR_SUCCESS) {
						newPointer = newArray;

						while(newPointer) {
							k = 0;

							for(i = 0; i < newPointer->AddressLength; i++) {
								if(i == newPointer->AddressLength - 1) {
									k += _snprintf(newMac + k, sizeof(newMac) - k, "%.2x%c", (int) newPointer->Address[i], 0);
								}
								else {
									k += _snprintf(newMac + k, sizeof(newMac) - k, "%.2x:", (int) newPointer->Address[i]);
								}
							}

							newBufcur = strlen(newPointer->Description) + strlen(newPointer->IpAddressList.IpAddress.String) + strlen(newPointer->IpAddressList.IpMask.String) + strlen(newMac) + 64;

							if(newBuflen - newBuffil <= newBufcur) {
								newBuflen += DATA_BLOCK_SIZE;

								if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for network interface buffer");

									free(newArray);
									free(newBuffer);

									return(NULL);
								}

								newBuffer = tmpBuffer;
							}

							l += _snprintf(newBuffer + l, newBuflen, "%s%c%s%c255.255.255.255%c%s%c%s%c", newPointer->Description, ITEM_SEPARATOR, newPointer->IpAddressList.IpAddress.String, ITEM_SEPARATOR, ITEM_SEPARATOR, newPointer->IpAddressList.IpMask.String, ITEM_SEPARATOR, newMac, ITEM_DELIMITER);

							newBuffil += newBufcur;
							newPointer = newPointer->Next;
						}
					}

					free(newArray);
				}
				else {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for network interface buffer");
				}
			}
		}

		FreeLibrary(modIphlp);
	}

	if(l > 0) {
		l--;
	}

	newBuffer[l] = 0;

	return(newBuffer);
}

void netFreeInterfaceData(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

void netInitOpenPorts(struct paramInfo * pi) {
	int *confScan;

	pi->a = 0;
	pi->b = 0;

	if((confScan = configFetch("start_portscan")) != NULL) {
		pi->a = *confScan;
	}

	if((confScan = configFetch("end_portscan")) != NULL) {
		pi->b = *confScan;
	}
}

char *netGetOpenPorts(struct paramInfo * pi) {
	unsigned int i, j, k;

	char *intBuffer, *tmpBuffer;
	char newBuffer[CONFIG_SPACE_SIZE];

	size_t intBuflen;

	struct in_addr newIAddr;
	struct hostent *newHostent;
	struct sockaddr_in newSockaddr;

	SOCKET newSocket;
	WORD wsaVersion;
	WSADATA wsaData;

	if(pi->a <= 0 || pi->b <= 0 || pi->a > 65536 || pi->b > 65536 || pi->b <= pi->a) {
		return(NULL);
	}

	intBuflen = 5 + 1;

	if((intBuffer = malloc(intBuflen + 1)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for address buffer");

		return(NULL);
	}

	wsaVersion = MAKEWORD(1, 1);

	if(WSAStartup(wsaVersion, &wsaData) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to initialize Winsock library");

		return(NULL);
	}

	memset(&newIAddr, 0, sizeof(newIAddr));
	memset(&newSockaddr, 0, sizeof(newSockaddr));

	k = 0;

	if(gethostname(newBuffer, sizeof(newBuffer)) == 0) {
		if((newHostent = gethostbyname(newBuffer)) != NULL) {
			fd_set newSet;
			TIMEVAL newTime;

			for(i = pi->a; i < pi->b; i++) {
				newSockaddr.sin_family = AF_INET;
				newSockaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr_list[0]))->s_addr;
				newSockaddr.sin_port = htons(i);

				if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
					j = 1;

					if(ioctlsocket(newSocket, 0x8004667e, &j) == 0) {
						if(setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &j, sizeof(j)) == 0) {
							if(connect(newSocket, (struct sockaddr *) &newSockaddr, sizeof(newSockaddr)) != SOCKET_ERROR) {
								k += _snprintf(intBuffer + k, 5 + 1, "%lu%c", i, ITEM_SPLITTER);
							}
							else {
								if(WSAGetLastError() == WSAEWOULDBLOCK) {
									newSet.fd_count = 1;
									newSet.fd_array[0] = newSocket;

									newTime.tv_sec = 0;
									newTime.tv_usec = 0;

									if(select(0, 0, &newSet, 0, &newTime) > 0) {
										k += _snprintf(intBuffer + k, 5 + 1, "%lu%c", i, ITEM_SPLITTER);
									}
								}
							}

							if(k + 16 > intBuflen) {
								intBuflen += 16;

								if((tmpBuffer = realloc(intBuffer, intBuflen)) == NULL) {
									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for address buffer");

									free(intBuffer);
									closesocket(newSocket);

									WSACleanup();

									return(NULL);
								}

								intBuffer = tmpBuffer;
							}
						}
					}

					closesocket(newSocket);
				}
			}
		}
	}

	intBuffer[k] = 0;

	if(k > 1 && intBuffer[k - 1] == ITEM_SPLITTER) {
		intBuffer[k - 1] = 0;
	}

	WSACleanup();

	return(intBuffer);
}

void netFreeOpenPorts(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

void netSendPacket(char *sendBuffer, size_t sendLength) {
	int *confInt;
	char *confChar;

	size_t t, s;

	struct hostent *newHostent;
	struct sockaddr_in newPinaddr;

	SOCKET newSocket;
	WORD wsaVersion;
	WSADATA wsaData;

	if(sendBuffer == NULL || sendBuffer[0] == 0) {
		return;
	}

	if((confChar = configFetch("tellud_server")) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch 'tellud_server' keyword from configuration file");

		return;
	}

	if((confInt = configFetch("tellud_port")) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to fetch 'tellud_port' keyword from configuration file");

		return;
	}

	wsaVersion = MAKEWORD(1, 1);

	if(WSAStartup(wsaVersion, &wsaData) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to initialize Winsock library");

		return;
	}

	if((newHostent = gethostbyname(confChar)) == NULL) {
		if((newHostent = gethostbyaddr(confChar, strlen(confChar), AF_INET)) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to get address for defined server");

			WSACleanup();

			return;
		}
	}

	memset(&newPinaddr, 0, sizeof(newPinaddr));

	newPinaddr.sin_family = PF_INET;
	newPinaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr))->s_addr;
	newPinaddr.sin_port = htons(*confInt);

	if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket for peer");

		WSACleanup();

		return;
	}

	if((connect(newSocket, (void *) &newPinaddr, sizeof(newPinaddr))) == SOCKET_ERROR) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to connect to peer");

		closesocket(newSocket);

		WSACleanup();

		return;
	}

	t = 0;

	while(1) {
		if((s = send(newSocket, sendBuffer, sendLength, 0)) == SOCKET_ERROR) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to send data to peer");

			break;
		}

		t += s;

		if(t >= sendLength) {
			break;
		}
	}

	closesocket(newSocket);

	WSACleanup();
}
