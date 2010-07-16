#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/socket.h>

#if defined(__linux__) || (__FreeBSD__) || (__NetBSD__) || (__OpenBSD__)
#include <net/if.h>
#endif

#include "declarations.h"
#include "network.h"



char *netGetInterfaceData(struct paramInfo * pi) {
#if defined(__linux__) || (__FreeBSD__) || (__NetBSD__) || (__OpenBSD__)
	int i, j, k;
	int newSocket;

	char *intBuffer, *tmpBuffer;
	char *newFace;
	char newName[DATA_STRING_SIZE];

	size_t newBuflen, newBufcur, newBuffil;

	struct ifreq intReq;
	struct sockaddr_in sockAddr;

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((intBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for interface buffer");

		return(NULL);
	}

	if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		free(intBuffer);

		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket");

		return(NULL);
	}

	if((newFace = netGetInterfaceList()) == NULL) {
		free(intBuffer);

		if(close(newSocket) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
		}

		warningMessage(ERROR_SLIGHT, "Error occurred while trying to get interface list");

		return(NULL);
	}

	j = 0;
	k = 0;

	for(i = 0; i <strlen(newFace) + 1; i++) {
		if(newFace[i] == 0 || newFace[i] == ITEM_SEPARATOR) {
			newName[j] = 0;

			newBufcur = DATA_BLOCK_SIZE;

			if(newBuflen - newBuffil <= newBufcur) {
				newBuflen += DATA_BLOCK_SIZE;

				if((tmpBuffer = realloc(intBuffer, newBuflen)) == NULL) {
					free(intBuffer);

					warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for interface buffer");

					return(NULL);
				}

				intBuffer = tmpBuffer;
			}

			j = 0;

			memset(&sockAddr, 0, sizeof(sockAddr));
			memset(&intReq, 0, sizeof(intReq));

			snprintf(intReq.ifr_name, sizeof(intReq.ifr_name), "%s%c", newName, 0);

			ioctl(newSocket, SIOCGIFADDR, (char *) &intReq);

			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "%s%c", intReq.ifr_name, ITEM_SEPARATOR);

			sockAddr = *((struct sockaddr_in *)(&(intReq.ifr_addr)));

			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "%s%c", inet_ntoa(sockAddr.sin_addr), ITEM_SEPARATOR);

			memset(&intReq, 0, sizeof(intReq));

			snprintf(intReq.ifr_name, sizeof(intReq.ifr_name), "%s%c", newName, 0);

			ioctl(newSocket, SIOCGIFBRDADDR, (char *) &intReq);

			sockAddr = *((struct sockaddr_in *)(&(intReq.ifr_addr)));

			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "%s%c", inet_ntoa(sockAddr.sin_addr), ITEM_SEPARATOR);

			memset(&intReq, 0, sizeof(intReq));

			snprintf(intReq.ifr_name, sizeof(intReq.ifr_name), "%s%c", newName, 0);

			ioctl(newSocket, SIOCGIFNETMASK, (char *) &intReq);

			sockAddr = *((struct sockaddr_in *)(&(intReq.ifr_addr)));

			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "%s%c", inet_ntoa(sockAddr.sin_addr), ITEM_SEPARATOR);

			memset(&intReq, 0, sizeof(intReq));

			snprintf(intReq.ifr_name, sizeof(intReq.ifr_name), "%s%c", newName, 0);
#if defined(__linux__)
			ioctl(newSocket, SIOCGIFHWADDR, (char *) &intReq);

			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "%02x:%02x:%02x:%02x:%02x:%02x%c",
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[0],
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[1],
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[2],
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[3],
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[4],
				(int) ((unsigned char *) &intReq.ifr_hwaddr.sa_data)[5], ITEM_DELIMITER);
#else
			k += snprintf(intBuffer + k, DATA_STRING_SIZE, "00:00:00:00:00:00%c", ITEM_DELIMITER);
#endif
			newBuffil += newBufcur;
		}
		else {
			newName[j] = newFace[i];

			j++;
		}
	}

	if(close(newSocket) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
	}

	netFreeInterfaceList(newFace);

	if(k > 0) {
		k--;
	}

	intBuffer[k] = 0;

	return(intBuffer);
#else
	return(NULL);
#endif
}

void netFreeInterfaceData(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

char *netGetInterfaceList(void) {
#if defined(__linux__) || (__FreeBSD__) || (__NetBSD__) || (__OpenBSD__)
	int i, k;

	char *intBuffer, *tmpBuffer;

	size_t intBuflen;

	struct if_nameindex *intNames;

	intBuflen = IFNAMSIZ + 1;

	if((intBuffer = malloc(intBuflen + 1)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for name buffer");

		return(NULL);
	}

	k = 0;

	if((intNames = if_nameindex()) != NULL) {
		for(i = 0; ; i++) {
			if(intNames[i].if_name == NULL) {
				break;
			}

			if(k + IFNAMSIZ + 1 > intBuflen) {
				intBuflen += IFNAMSIZ + 1;

				if((tmpBuffer = realloc(intBuffer, intBuflen)) == NULL) {
					free(intBuffer);

					warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for name buffer");

					return(NULL);
				}

				intBuffer = tmpBuffer;
			}

			k += snprintf(intBuffer + k, IFNAMSIZ + 1, "%s%c", intNames[i].if_name, ITEM_SEPARATOR);
		}

		if_freenameindex(intNames);

	}

	intBuffer[k] = 0;

	if(k > 1 && intBuffer[k - 1] == ITEM_SEPARATOR) {
		intBuffer[k - 1] = 0;
	}

	return(intBuffer);
#else
	return(NULL);
#endif
}

void netFreeInterfaceList(char *intBuffer) {
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
	int i, k;
	int newSocket; // newOptions;

	char *intBuffer, *tmpBuffer;
	char thisName[MAXHOSTNAMELEN];

	fd_set newSet;
	size_t intBuflen;

	struct hostent *newHostent;
	struct sockaddr_in newPinaddr;
	struct timeval newTime;

	if(pi->a <= 0 || pi->b <= 0 || pi->a > 65536 || pi->b > 65536 || pi->b <= pi->a) {
		return(NULL);
	}

	intBuflen = 5 + 1;

	if((intBuffer = malloc(intBuflen + 1)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for address buffer");

		return(NULL);
	}

	k = 0;

	if(gethostname(thisName, sizeof(thisName)) != -1) {
		if((newHostent = gethostbyname(thisName)) != NULL) {
			for(i = pi->a; i < pi->b; i++) {
				memset(&newPinaddr, 0, sizeof(newPinaddr));

				newPinaddr.sin_family = PF_INET;
				newPinaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr))->s_addr;
				newPinaddr.sin_port = htons(i);

				if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket");

					continue;
				}

	//			if((newOptions = fcntl(newSocket, F_GETFL, 0)) == -1) {
	//				warningMessage(ERROR_SLIGHT, "Error occurred while trying to get socket options");

	//				if(close(newSocket) == -1) {
	//					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
	//				}

	//				continue;
	//			}

	//			newOptions |= O_NONBLOCK | O_NDELAY;

	//			if(fcntl(newSocket, F_SETFL, newOptions, 0) == -1) {
	//				warningMessage(ERROR_SLIGHT, "Error occurred while trying to set socket options");

	//				if(close(newSocket) == -1) {
	//					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
	//				}

	//				continue;
	//			}

				if((connect(newSocket, (void *) &newPinaddr, sizeof(newPinaddr))) == 0) {
					if(k + 16 > intBuflen) {
						intBuflen += 16;

						if((tmpBuffer = realloc(intBuffer, intBuflen)) == NULL) {
							free(intBuffer);

							if(close(newSocket) == -1) {
								warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
							}

							warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for address buffer");

							return(NULL);
						}

						intBuffer = tmpBuffer;
					}

					k += snprintf(intBuffer + k, 5 + 1, "%d%c", i, ITEM_SPLITTER);
				}
				else {
					if(errno == EINPROGRESS) {
						FD_ZERO(&newSet);
						FD_SET(newSocket, &newSet);

						newTime.tv_sec = 0;
						newTime.tv_usec = 0;

						if(select(2, 0, &newSet, 0, &newTime) > 0) {
							if(k + 16 > intBuflen) {
								intBuflen += 16;

								if((tmpBuffer = realloc(intBuffer, intBuflen)) == NULL) {
									free(intBuffer);

									if(close(newSocket) == -1) {
										warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
									}

									warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for address buffer");

									return(NULL);
								}

								intBuffer = tmpBuffer;
							}
						}
					}
				}

				if(close(newSocket) == -1) {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
				}
			}
		}
	}

	intBuffer[k] = 0;

	if(k > 1 && intBuffer[k - 1] == ITEM_SPLITTER) {
		intBuffer[k - 1] = 0;
	}

	return(intBuffer);
}

void netFreeOpenPorts(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}

void netSendPacket(char *sendBuffer, size_t sendLength) {
	int newSocket;
	int *confInt;
	char *confChar;

	size_t t;
	ssize_t s;

	struct hostent *newHostent;
	struct sockaddr_in newPinaddr;

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

	if((newHostent = gethostbyname(confChar)) == NULL) {
		if((newHostent = gethostbyaddr(confChar, strlen(confChar), AF_INET)) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to get address for defined server");

			return;
		}
	}

	memset(&newPinaddr, 0, sizeof(newPinaddr));

	newPinaddr.sin_family = PF_INET;
	newPinaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr))->s_addr;
	newPinaddr.sin_port = htons(*confInt);

	if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket for peer");

		return;
	}

	if((connect(newSocket, (void *) &newPinaddr, sizeof(newPinaddr))) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to connect to peer");

		if(close(newSocket) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
		}

		return;
	}

	t = 0;

	while(1) {
		if((s = send(newSocket, sendBuffer, sendLength, 0)) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to send data to peer");

			break;
		}

		t += s;

		if(t >= sendLength) {
			break;
		}
	}

	if(close(newSocket) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
	}
}
