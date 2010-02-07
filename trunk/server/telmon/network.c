#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "declarations.h"
#include "defines.h"
#include "network.h"



void netFetchChart(struct mainInfo * mi) {
	struct replyInfo ri;

	ri.handler = netFetchChartHandler;
	ri.replyCount = DATA_REPLY_CHART_COUNT;

	netDeliverPacket(chartArrays, &ri, mi);
}

void netFetchDays(struct mainInfo * mi) {
	struct replyInfo ri;

	memset(&mi->hstArrays, 0, sizeof(mi->hstArrays));

	mi->hstDaysCount = 0;

	ri.handler = netFetchDaysHandler;
	ri.replyCount = DATA_REPLY_HIST_COUNT;

	netDeliverPacket(historyArrays, &ri, mi);
}

void netFetchStat(struct mainInfo * mi) {
	int thisFreq;
	int *confFreq;

	struct replyInfo ri;

	memset(&mi->srvWorkersAvailable, 0, sizeof(mi->srvWorkersAvailable));
	memset(&mi->srvServerStarted, 0, sizeof(mi->srvServerStarted));
	memset(&mi->srvLastTask, 0, sizeof(mi->srvLastTask));
	memset(&mi->srvTotalTasks, 0, sizeof(mi->srvTotalTasks));
	memset(&mi->srvInfoTime, 0, sizeof(mi->srvInfoTime));
	memset(&mi->srvWarnTime, 0, sizeof(mi->srvWarnTime));
	memset(&mi->srvInfoMessage, 0, sizeof(mi->srvInfoMessage));
	memset(&mi->srvWarnMessage, 0, sizeof(mi->srvWarnMessage));

	if((confFreq = configFetch("update_frequency")) != NULL) {
		thisFreq = *confFreq;
	}
	else {
		thisFreq = CONFIG_DEFAULT_FREQUENCY;
	}

	thisFreq *= 1000;

	mi->appData.timeOut = XtAppAddTimeOut(mi->appContext, thisFreq, (XtTimerCallbackProc) netFetchStat, (struct mainInfo *) mi);

	ri.handler = netFetchStatHandler;
	ri.replyCount = DATA_REPLY_STAT_COUNT;

	netDeliverPacket(monitorArrays, &ri, mi);

	updateWindow(mi);
}

void netFetchChartHandler(struct mainInfo * mi, char *dataBuffer, size_t s, int n) {
	int i, j;

	char *thisOffset;

	switch(n) {
		case 3:
			i = 0;

			thisOffset = dataBuffer;

			while((thisOffset = strchr(thisOffset, ITEM_DELIMITER)) != NULL) {
				*thisOffset = 0;

				thisOffset++;
				i++;
			}

			if(i != 24) {
				break;
			}

			thisOffset = dataBuffer;

			for(j = 0; j < i; j++) {
				mi->hstDaysStat[j] = atol(thisOffset);

				while(*thisOffset != 0) {
					thisOffset++;
				}

				thisOffset++;
			}

			break;
		default:
			break;
	}
}

void netFetchDaysHandler(struct mainInfo * mi, char *dataBuffer, size_t s, int n) {
	int i, j, k, l, p, o;

	char *thisOffset, *thatOffset;
	char tempBuffer[CONFIG_SPACE_SIZE];

	switch(n) {
		case 3:
			i = 1;

			thisOffset = dataBuffer;

			while((thisOffset = strchr(thisOffset, ITEM_DELIMITER)) != NULL) {
				thisOffset++;
				i++;
			}

			thatOffset = dataBuffer;

			for(j = 0; j < i; j++) {
				k = 0;

				thisOffset = thatOffset;

				while(*thisOffset != ITEM_DELIMITER && *thisOffset != 0) {
					if(*thisOffset == ITEM_SEPARATOR) {
						k++;
					}

					thisOffset++;
				}

				if(k != 4) {
					break;
				}

				l = 0;
				thisOffset = thatOffset;

				for(k = 0; k < 4; k++) {
					switch(k) {
						case 0:
							o = 0;

							while(*thisOffset != ITEM_SEPARATOR && *thisOffset != 0) {
								mi->hstArrays[j].label[l++] = *thisOffset;
								mi->hstArrays[j].dayname[o++] = *thisOffset;

								thisOffset++;
							}

							mi->hstArrays[j].label[l++] = ',';
							mi->hstArrays[j].label[l++] = ' ';
							mi->hstArrays[j].dayname[o] = 0;

							break;
						case 1:
							p = 0;
							o = 0;

							while(*thisOffset != ITEM_SEPARATOR && *thisOffset != 0) {
								tempBuffer[p++] = *thisOffset;
								mi->hstArrays[j].daynum[o++] = *thisOffset;

								thisOffset++;
							}

							tempBuffer[p++] = 0;
							mi->hstArrays[j].daynum[o] = 0;

							l += snprintf(mi->hstArrays[j].label + l, sizeof(mi->hstArrays[j].label) - l, "%.2u. ", atoi(tempBuffer));

							break;
						case 2:
							o = 0;

							while(*thisOffset != ITEM_SEPARATOR && *thisOffset != 0) {
								mi->hstArrays[j].label[l++] = *thisOffset;
								mi->hstArrays[j].monthname[o++] = *thisOffset;

								thisOffset++;
							}

							mi->hstArrays[j].label[l++] = ' ';
							mi->hstArrays[j].monthname[o] = 0;

							break;
						case 3:
							o = 0;

							while(*thisOffset != ITEM_SEPARATOR && *thisOffset != 0) {
								mi->hstArrays[j].label[l++] = *thisOffset;
								mi->hstArrays[j].yearnum[o++] = *thisOffset;

								thisOffset++;
							}

							mi->hstArrays[j].label[l] = 0;
							mi->hstArrays[j].yearnum[o] = 0;

							break;
						default:
							break;
					}

					thisOffset++;
				}

				while(*thatOffset != ITEM_DELIMITER && *thatOffset != 0) {
					thatOffset++;
				}

				thatOffset++;
			}

			break;
		default:
			break;
	}
}

void netFetchStatHandler(struct mainInfo * mi, char *dataBuffer, size_t s, int n) {
	switch(n) {
		case 3:
			strncpy(mi->srvWorkersAvailable, dataBuffer, s);

			break;
		case 4:
			strncpy(mi->srvServerStarted, dataBuffer, s);

			break;
		case 5:
			strncpy(mi->srvLastTask, dataBuffer, s);

			break;
		case 6:
			strncpy(mi->srvTotalTasks, dataBuffer, s);

			break;
		case 7:
			strncpy(mi->srvInfoTime, dataBuffer, s);

			break;
		case 8:
			strncpy(mi->srvWarnTime, dataBuffer, s);

			break;
		case 9:
			strncpy(mi->srvInfoMessage, dataBuffer, s);

			break;
		case 10:
			strncpy(mi->srvWarnMessage, dataBuffer, s);

			break;
		default:
			break;
	}
}

void netGetReply(int thisSocket, struct replyInfo * ri, struct mainInfo * mi) {
	int co, ps, us;

	char *confMagCoo;
	char *dataPacket, *dataDeflate;
	char magicCookie[] = "TELLUTELLUTELLUTELLUTELLUTELLU";
	char dataSpace[DATA_POINTER_SIZE + 1];
	char magicSpace[DATA_COOKIE_SIZE + 1];

	size_t s, t;

	if((confMagCoo = configFetch("server_password")) != NULL) {
		s = strlen(confMagCoo);

		if(s > strlen(magicCookie)) {
			s = strlen(magicCookie);
		}

		strncpy(magicCookie, confMagCoo, s);
	}

	memset(magicSpace, 0, sizeof(magicSpace));

	t = DATA_COOKIE_SIZE;
	s = recv(thisSocket, magicSpace, t, MSG_WAITALL);

	if(s != t || magicSpace[0] == 0 || strncmp(magicCookie, magicSpace, t) != 0) {
		warningMessage(ERROR_SLIGHT, "Reply packet has invalid signature", mi);

		return;
	}

	memset(dataSpace, 0, sizeof(dataSpace));

	s = recv(thisSocket, dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(s != DATA_POINTER_SIZE || dataSpace[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Reply packet has ended unexpectedly", mi);

		return;
	}

	co = atoi(dataSpace);

	memset(dataSpace, 0, sizeof(dataSpace));

	s = recv(thisSocket, dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(s != DATA_POINTER_SIZE || dataSpace[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Reply packet has ended unexpectedly", mi);

		return;
	}

	ps = atoi(dataSpace);

	memset(dataSpace, 0, sizeof(dataSpace));

	s = recv(thisSocket, dataSpace, DATA_POINTER_SIZE, MSG_WAITALL);

	if(s != DATA_POINTER_SIZE || dataSpace[0] == 0) {
		warningMessage(ERROR_SLIGHT, "Reply packet has ended unexpectedly", mi);

		return;
	}

	us = atoi(dataSpace);

	if(ps <= DATA_COOKIE_SIZE || us <= DATA_COOKIE_SIZE) {
		warningMessage(ERROR_SLIGHT, "Reply packet has ended unexpectedly", mi);

		return;
	}

	if((dataPacket = malloc(ps + (DATA_COOKIE_SIZE + 1))) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for reply packet", mi);

		return;
	}

	memcpy(dataPacket, magicSpace, t);

	s = t;

	while(1) {
		if((t = recv(thisSocket, dataPacket + s, ps - DATA_COOKIE_SIZE, MSG_WAITALL)) == -1) {
			warningMessage(ERROR_SLIGHT, "Reply packet has transmission error", mi);

			free(dataPacket);

			return;
		}

		s += t;

		if(s >= ps) {
			break;
		}
	}

	if(s < ps) {
		warningMessage(ERROR_SLIGHT, "Reply packet is too short", mi);

		free(dataPacket);

		return;
	}

	if(s > ps) {
		warningMessage(ERROR_SLIGHT, "Reply packet is too long", mi);

		free(dataPacket);

		return;
	}

	dataPacket[s] = 0;

	switch(co) {
		case DATA_COMPRESS_JIP:
			if((dataDeflate = malloc(us + 16)) == NULL) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for reply packet", mi);

				free(dataPacket);

				return;
			}

			if(jipDeflate((unsigned char *) dataPacket, (unsigned char *) dataDeflate, &mi->compressInfo, ps) != 0) {
				warningMessage(ERROR_SLIGHT, "Reply packet has failed to deflate", mi);

				free(dataPacket);

				return;
			}

			dataDeflate[us] = 0;

			free(dataPacket);

			dataPacket = dataDeflate;

			break;
		default:
			break;
	}

	netSplitReply(dataPacket, ri, mi);
}

void netSplitReply(char *dataPacket, struct replyInfo * ri, struct mainInfo * mi) {
	int i, k, n;

	char *dataBuffer, *dataPointer;
	char dataSpace[DATA_POINTER_SIZE + 1];

	size_t s;

	void (*replyHandler)(struct mainInfo *, char *, size_t, int);

	n = 0;

	dataPointer = dataPacket + DATA_COOKIE_SIZE;

	replyHandler = ri->handler;

	for(i = 0; i < ri->replyCount; i++) {
		memcpy(dataSpace, dataPointer, DATA_POINTER_SIZE);

		dataSpace[DATA_POINTER_SIZE] = 0;
		k = atoi(dataSpace);

		memcpy(dataSpace, dataPointer + DATA_POINTER_SIZE, DATA_POINTER_SIZE);

		dataSpace[DATA_POINTER_SIZE] = 0;
		s = atoi(dataSpace) - k;
		dataPointer += DATA_POINTER_SIZE;

		if(s > 0) {
			if(s > CONFIG_SPACE_SIZE) {
				s = CONFIG_SPACE_SIZE;
			}

			if((dataBuffer = malloc(s + 1)) == NULL) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for reply packet block", mi);

				break;
			}

			memcpy(dataBuffer, dataPacket + k, s);

			dataBuffer[s] = 0;

			replyHandler(mi, dataBuffer, s, n);

			free(dataBuffer);
		}

		n++;
	}

	free(dataPacket);
}

void netDeliverPacket(struct cmdArray * thisArray, struct replyInfo * ri, struct mainInfo * mi) {
	int i, k;
	unsigned int t;

	char *confMagCoo;
	char *dataString, *dataPacket, *tmpPacket;
	char magicCookie[] = "TELLUTELLUTELLUTELLUTELLUTELLU";
	char infoCookie[] = "000000000000000000000000";
	char dataPointer[DATA_POINTER_SIZE + 1];

	size_t s;

	char *(*cmdAllocator)(struct mainInfo *);
	void (*cmdDestroyer)(char *);

	if((confMagCoo = configFetch("server_password")) != NULL) {
		s = strlen(confMagCoo);

		if(s > strlen(magicCookie)) {
			s = strlen(magicCookie);
		}

		strncpy(magicCookie, confMagCoo, s);
	}

	s = DATA_BLOCK_SIZE;

	if((dataPacket = malloc(s)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet", mi);

		return;
	}

	k = strlen(magicCookie);

	memset(dataPacket, 0, s);
	memcpy(dataPacket, magicCookie, k);
	memcpy(dataPacket + k, infoCookie, strlen(infoCookie));

	t = k + (DATA_ARRAYS_COUNT * DATA_POINTER_SIZE);
	k += strlen(infoCookie);

	memset(&dataPointer, 0, sizeof(dataPointer));

	for(i = 0; ; i++) {
		if(thisArray[i].task == NULL) {
			break;
		}

		cmdAllocator = *thisArray[i].allocator;
		cmdDestroyer = *thisArray[i].destroyer;

		snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
		memcpy(dataPacket + k, dataPointer, DATA_POINTER_SIZE);

		k += DATA_POINTER_SIZE;

		if((dataString = (char *) (*cmdAllocator)(mi)) != NULL) {
			s += strlen(dataString);

			if((tmpPacket = realloc(dataPacket, s)) == NULL) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for data packet", mi);

				free(dataPacket);

				return;
			}

			dataPacket = tmpPacket;

			memcpy(dataPacket + t + strlen(infoCookie), dataString, strlen(dataString));

			t += strlen(dataString);

			if(cmdDestroyer != NULL) {
				(void) (*cmdDestroyer)((char *) dataString);
			}
		}
	}

	snprintf(dataPointer, sizeof(dataPointer), "%.8u", DATA_COMPRESS_NONE);
	memcpy(dataPacket + strlen(magicCookie), dataPointer, DATA_POINTER_SIZE);

	snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
	memcpy(dataPacket + strlen(magicCookie) + DATA_POINTER_SIZE, dataPointer, DATA_POINTER_SIZE);

	snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
	memcpy(dataPacket + strlen(magicCookie) + (DATA_POINTER_SIZE * 2), dataPointer, DATA_POINTER_SIZE);

	netSendPacket(dataPacket, t + (DATA_POINTER_SIZE * 3), ri, mi);

	free(dataPacket);
}

void netSendPacket(char *sendBuffer, size_t sendLength, struct replyInfo * ri, struct mainInfo * mi) {
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

	if((confChar = configFetch("telmond_server")) == NULL) {
		infoMessage(ERROR_SLIGHT, "Error occurred while trying to fetch 'telmond_server' keyword from configuration", mi);

		return;
	}

	if((confInt = configFetch("telmond_port")) == NULL) {
		infoMessage(ERROR_SLIGHT, "Error occurred while trying to fetch 'telmond_port' keyword from configuration", mi);

		return;
	}

	if((newHostent = gethostbyname(confChar)) == NULL) {
		if((newHostent = gethostbyaddr(confChar, strlen(confChar), AF_INET)) == NULL) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to get address for defined server", mi);

			return;
		}
	}

	memset(&newPinaddr, 0, sizeof(newPinaddr));

	newPinaddr.sin_family = PF_INET;
	newPinaddr.sin_addr.s_addr = ((struct in_addr *)(newHostent->h_addr))->s_addr;
	newPinaddr.sin_port = htons(*confInt);

	if((newSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to create new socket for peer", mi);

		return;
	}

	if((connect(newSocket, (void *) &newPinaddr, sizeof(newPinaddr))) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to connect to peer", mi);

		if(close(newSocket) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket", mi);
		}

		return;
	}

	t = 0;

	while(1) {
		if((s = send(newSocket, sendBuffer, sendLength, 0)) == -1) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to send data to peer", mi);

			if(close(newSocket) == -1) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket", mi);
			}

			return;
		}

		t += s;

		if(t >= sendLength) {
			break;
		}
	}

	netGetReply(newSocket, ri, mi);

	if(close(newSocket) == -1) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close socket", mi);
	}
}
