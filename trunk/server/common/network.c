#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <asm/param.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "declarations.h"
#include "defines.h"



int netCreateListenSocket(short listenPort) {
	int thisSocket, socketFlag;

	struct sockaddr_in sinadd;

	if((thisSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to create listening socket");
	}

	socketFlag = 1;

	if((setsockopt(thisSocket, SOL_SOCKET, SO_REUSEADDR, &socketFlag, sizeof(socketFlag))) == -1) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to set socket option SO_REUSEADDR");
	}

	memset(&sinadd, 0, sizeof(sinadd));

	sinadd.sin_family = PF_INET;
	sinadd.sin_addr.s_addr = INADDR_ANY;
	sinadd.sin_port = htons(listenPort);

	if((bind(thisSocket, (struct sockaddr *) &sinadd, sizeof(sinadd))) == -1) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to bind socket to requested port");
	}

	if((listen(thisSocket, SOMAXCONN)) == -1) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to set socket to listen state");
	}

	return(thisSocket);
}

void netCloseSocket(int thisSocket) {
	if(close(thisSocket) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
	}
}

int netWaitConnection(int thisSocket, struct threadInfo * ti) {
	int thatSocket;

	char newString[CONFIG_SPACE_SIZE];

	socklen_t s;

	struct sockaddr_in sa;
	struct timeval tv;

	s = sizeof(sa);

	if((thatSocket = accept(thisSocket, (struct sockaddr *) &sa, &s)) != -1) {
		tv.tv_sec = TIMEOUT_SOCKET;
		tv.tv_usec = 0;

		if((setsockopt(thatSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv))) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to set socket option SO_RCVTIMEO");
		}

		if((setsockopt(thatSocket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv))) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to set socket option SO_SNDTIMEO");
		}

		snprintf(newString, sizeof(newString), "Connection from %s at port %d%c", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port), 0);

		infoMessage(ERROR_NOERROR, newString);

		return(thatSocket);
	}

	warningMessage(ERROR_SLIGHT, "Error occurred while trying to accept client, dropping agent");

	return(-1);
}

char *netReadPacket(int thisSocket, struct threadInfo * ti) {
	memset(ti->magicSpace, 0, sizeof(ti->magicSpace));

	// Read magick cookie from the agent
	ti->t = DATA_COOKIE_SIZE;
	ti->s = recv(thisSocket, ti->magicSpace, ti->t, MSG_WAITALL);

	// Check magick cookie
	if(ti->s != ti->t || ti->magicSpace[0] == 0 || strncmp(ti->magicCookie, ti->magicSpace, ti->t) != 0) {
		warningThread(ERROR_SLIGHT, "Data packet has invalid signature, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	// Read packet info part from the agent
	memset(ti->dataSpace, 0, sizeof(ti->dataSpace));

	ti->s = recv(thisSocket, ti->dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(ti->s != DATA_POINTER_SIZE || ti->dataSpace[0] == 0) {
		warningThread(ERROR_SLIGHT, "Data packet has ended unexpectedly, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	ti->co = atoi(ti->dataSpace);

	memset(ti->dataSpace, 0, sizeof(ti->dataSpace));

	ti->s = recv(thisSocket, ti->dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(ti->s != DATA_POINTER_SIZE || ti->dataSpace[0] == 0) {
		warningThread(ERROR_SLIGHT, "Data packet has ended unexpectedly, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	ti->ps = atoi(ti->dataSpace);

	memset(ti->dataSpace, 0, sizeof(ti->dataSpace));

	ti->s = recv(thisSocket, ti->dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(ti->s != DATA_POINTER_SIZE || ti->dataSpace[0] == 0) {
		warningThread(ERROR_SLIGHT, "Data packet has ended unexpectedly, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	ti->us = atoi(ti->dataSpace);

	if(ti->ps <= DATA_COOKIE_SIZE || ti->us <= DATA_COOKIE_SIZE) {
		warningThread(ERROR_SLIGHT, "Data packet has invalid header, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	// Allocate memory for data packet
	if((ti->dataPacket = malloc(ti->ps + (DATA_COOKIE_SIZE + 1))) == NULL) {
		warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		return(NULL);
	}

	memcpy(ti->dataPacket, ti->magicSpace, ti->t);

	ti->s = ti->t;

	// Read data from the agent
	while(1) {
		if((ti->t = recv(thisSocket, ti->dataPacket + ti->s, ti->ps - DATA_COOKIE_SIZE, MSG_WAITALL)) == -1) {
			warningThread(ERROR_SLIGHT, "Data packet has transmission error, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

			free(ti->dataPacket);

			return(NULL);
		}

		ti->s += ti->t;

		if(ti->s >= ti->ps) {
			break;
		}
	}

	if(ti->s < ti->ps) {
		warningThread(ERROR_SLIGHT, "Data packet is too short, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		free(ti->dataPacket);

		return(NULL);
	}

	if(ti->s > ti->ps) {
		warningThread(ERROR_SLIGHT, "Data packet is too long, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

		free(ti->dataPacket);

		return(NULL);
	}

	ti->dataPacket[ti->s] = 0;

	// Handle compressed data if necessary
	switch(ti->co) {
		case DATA_COMPRESS_NONE:
			return(ti->dataPacket);

			break;
		case DATA_COMPRESS_JIP:
			if((ti->dataDeflate = malloc(ti->us + 16)) == NULL) {
				warningThread(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

				free(ti->dataPacket);

				return(NULL);
			}

			if(jipDeflate((unsigned char *) ti->dataPacket, (unsigned char *) ti->dataDeflate, &ti->compressInfo, ti->ps) != 0) {
				warningThread(ERROR_SLIGHT, "Received data packet has failed to deflate, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

				free(ti->dataPacket);

				return(NULL);
			}

			ti->dataDeflate[ti->us] = 0;

			free(ti->dataPacket);

			return(ti->dataDeflate);

			break;
		default:
			warningThread(ERROR_SLIGHT, "Received data packet has unknown compression tag, dropping agent", ti->errorSpace, sizeof(ti->errorSpace), ti->a, &ti->i);

			free(ti->dataPacket);

			return(NULL);

			break;
	}

	return(NULL);
}

void netFreePacket(char *thisPacket) {
	if(thisPacket != NULL) {
		free(thisPacket);
	}
}

void netDummyConnect(void) {
	int i;
	int newSocket;
	int *confPort;
	short thisPort;

	char thisName[MAXHOSTNAMELEN];

	struct hostent *newHostent;
	struct sockaddr_in newPinaddr;

	thisPort = CONFIG_DEFAULT_PORT;

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		thisPort = *confPort;
	}

	if(gethostname(thisName, sizeof(thisName)) != 0) {
		snprintf(thisName, sizeof(thisName), "localhost%c", 0);
	}

	if((newHostent = gethostbyname(thisName)) != NULL) {
		memset(&newPinaddr, 0, sizeof(newPinaddr));

		newPinaddr.sin_family = PF_INET;
		newPinaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr))->s_addr;
		newPinaddr.sin_port = htons(thisPort);

		if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket");
		}
		else {
			if(connect(newSocket, (void *) &newPinaddr, sizeof(newPinaddr)) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to connect to local port");
			}

			if(close(newSocket) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket");
			}
		}
	}
}
