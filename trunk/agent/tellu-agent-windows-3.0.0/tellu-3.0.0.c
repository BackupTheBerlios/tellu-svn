#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "declarations.h"
#include "defines.h"
#include "structures.h"
#include "tellu-3.0.0.h"



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	unsigned int i, k, l, t;

	int *confDisFun, *confCompress, *confLoop;

	char *confKey1, *confKey2, *confKey3, *confMagCoo;
	char *dataString, *dataPacket, *compPacket, *tmpPacket;
	char magicCookie[] = "TELLUTELLUTELLUTELLUTELLUTELLU";
	char infoCookie[] = "000000000000000000000000";
	char dataPointer[DATA_POINTER_SIZE + 1];
	char confFile[CONFIG_SPACE_SIZE];

	size_t s;

	struct paramInfo pInfo, *pi;

	void (*cmdConstructor)(struct paramInfo *);
	char *(*cmdAllocator)(struct paramInfo *);
	void (*cmdDestroyer)(char *);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*
	 *
	 * Initialize default values.
	 *
	 */

	pi = &pInfo;

	memset(pi, 0, sizeof(pInfo));

	SetErrorMode(SEM_FAILCRITICALERRORS);

	/*
	 *
	 * Initialize local node and domain names.
	 *
	 */

	nodeInitNames();

	/*
	 *
	 * Read and parse configuration files.
	 *
	 */

	i = 0;

	while(1) {
		if((confKey1 = nodeFetchUserLogin()) != NULL) {
			if((confKey2 = nodeFetchDomain()) != NULL) {
				_snprintf(confFile, sizeof(confFile), "%s.%s.conf%c", confKey1, confKey2, 0);

				if(config(confFile) == 0) {
	 				i++;

					break;
				}
			}
		}

		if((confKey1 = nodeFetchUserLogin()) != NULL) {
			_snprintf(confFile, sizeof(confFile), "%s.conf%c", confKey1, 0);

			if(config(confFile) == 0) {
	 			i++;

				break;
			}
		}

		if((confKey1 = nodeFetchNode()) != NULL) {
			if((confKey2 = nodeFetchDomain()) != NULL) {
				_snprintf(confFile, sizeof(confFile), "%s.%s.conf%c", confKey1, confKey2, 0);

				if(config(confFile) == 0) {
	 				i++;

					break;
				}
			}
		}

		if((confKey1 = nodeFetchNode()) != NULL) {
			_snprintf(confFile, sizeof(confFile), "%s.conf%c", confKey1, 0);

			if(config(confFile) == 0) {
	 			i++;

				break;
			}
		}

		if((confKey1 = nodeFetchDomain()) != NULL) {
			_snprintf(confFile, sizeof(confFile), "%s.conf%c", confKey1, 0);

			if(config(confFile) == 0) {
	 			i++;

				break;
			}
		}

		if((confKey1 = nodeFetchSystem()) != NULL) {
			if((confKey2 = nodeFetchRelease()) != NULL) {
				if((confKey3 = nodeFetchMachine()) != NULL) {
					_snprintf(confFile, sizeof(confFile), "%s-%s.%s.conf%c", confKey1, confKey2, confKey3, 0);

					if(config(confFile) == 0) {
	 					i++;

						break;
					}
				}
			}
		}

		if((confKey1 = nodeFetchSystem()) != NULL) {
			if((confKey2 = nodeFetchRelease()) != NULL) {
				_snprintf(confFile, sizeof(confFile), "%s-%s.conf%c", confKey1, confKey2, 0);

				if(config(confFile) == 0) {
	 				i++;

					break;
				}
			}
		}

		if((confKey1 = nodeFetchSystem()) != NULL) {
			if((confKey2 = nodeFetchMachine()) != NULL) {
				_snprintf(confFile, sizeof(confFile), "%s.%s.conf%c", confKey1, confKey2, 0);

				if(config(confFile) == 0) {
	 				i++;

					break;
				}
			}
		}

		if((confKey1 = nodeFetchSystem()) != NULL) {
			_snprintf(confFile, sizeof(confFile), "%s.conf%c", confKey1, 0);

			if(config(confFile) == 0) {
	 			i++;

				break;
			}
		}

		break;
	}

	if(i == 0) {
		if(config(CONFIG_DEFAULT_FILE) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to open configuration file");
		}
	}

	if((confDisFun = configFetch("disabled_functionality")) != NULL) {
		if(*confDisFun != CONFIG_TYPE_BOOLEAN_NO) {
			ExitProcess(0);
		}
	}

	/*
	 *
	 * Initialize magick cookie.
	 *
	 */

	if((confMagCoo = configFetch("server_password")) != NULL) {
		s = strlen(confMagCoo);

		if(s > strlen(magicCookie)) {
			s = strlen(magicCookie);
		}

		strncpy(magicCookie, confMagCoo, s);
	}

	/*
	 *
	 * Allocate initial memory for data packet.
	 *
	 */

	while(1) {
		s = DATA_BLOCK_SIZE;

		if((dataPacket = malloc(s)) == NULL) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to allocate memory for data packet");
		}

		k = strlen(magicCookie);

		memcpy(dataPacket, magicCookie, k);
		memcpy(dataPacket + k, infoCookie, strlen(infoCookie));

		t = k + (DATA_ARRAYS_COUNT * DATA_POINTER_SIZE);
		k += strlen(infoCookie);

		/*
		 *
		 * Collect machine data.
		 *
		 */

		memset(&dataPointer, 0, sizeof(dataPointer));

		for(i = 0; ; i++) {
			if(cmdArrays[i].task == NULL) {
				break;
			}

			cmdConstructor = *cmdArrays[i].constructor;
			cmdAllocator = *cmdArrays[i].allocator;
			cmdDestroyer = *cmdArrays[i].destroyer;

			_snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
			memcpy(dataPacket + k, dataPointer, DATA_POINTER_SIZE);

			k += DATA_POINTER_SIZE;

			if(cmdConstructor != NULL) {
				(void) (*cmdConstructor)(pi);
			}

			if((dataString = (char *) (*cmdAllocator)(pi)) != NULL) {
				s += strlen(dataString) + 64;

				if((tmpPacket = realloc(dataPacket, s)) == NULL) {
					warningMessage(ERROR_FATAL, "Error occurred while trying to allocate memory for data packet");

					free(dataPacket);
				}

				dataPacket = tmpPacket;

				memcpy(dataPacket + t + strlen(infoCookie), dataString, strlen(dataString));

				t += strlen(dataString);

				if(cmdDestroyer != NULL) {
					(void) (*cmdDestroyer)((char *) dataString);
				}
			}
		}

		_snprintf(dataPointer, sizeof(dataPointer), "%.8u", DATA_COMPRESS_NONE);
		memcpy(dataPacket + strlen(magicCookie), dataPointer, DATA_POINTER_SIZE);

		_snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
		memcpy(dataPacket + strlen(magicCookie) + DATA_POINTER_SIZE, dataPointer, DATA_POINTER_SIZE);

		_snprintf(dataPointer, sizeof(dataPointer), "%.8u", t);
		memcpy(dataPacket + strlen(magicCookie) + (DATA_POINTER_SIZE * 2), dataPointer, DATA_POINTER_SIZE);

		/*
		 *
		 * Send possibly compressed data packet to the server.
		 *
		 */

		if((confCompress = configFetch("compressed_protocol")) != NULL) {
			if(*confCompress != CONFIG_TYPE_BOOLEAN_NO) {
				if((compPacket = malloc((s * 2) + 1)) != NULL) {
					memcpy(compPacket, dataPacket, 54);

					if((k = jipCompress((unsigned char *) dataPacket + 54, (unsigned char *) compPacket + 54, t - 30)) != 0) {
						free(dataPacket);

						dataPacket = compPacket;

						k += 30;
						t = k;

						_snprintf(dataPointer, sizeof(dataPointer), "%.8u", DATA_COMPRESS_JIP);
						memcpy(dataPacket + strlen(magicCookie), dataPointer, DATA_POINTER_SIZE);

						_snprintf(dataPointer, sizeof(dataPointer), "%.8u", k);
						memcpy(dataPacket + strlen(magicCookie) + DATA_POINTER_SIZE, dataPointer, DATA_POINTER_SIZE);
					}
					else {
						warningMessage(ERROR_SLIGHT, "Error occurred while trying to compress data packet");

						free(compPacket);
					}
				}
				else {
					warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for compressed data packet");
				}
			}
		}

		netSendPacket(dataPacket, t + (DATA_POINTER_SIZE * 3));

		free(dataPacket);

		/*
		 *
		 * Loop back if looping mode is requested.
		 *
		 */

		l = 0;

		if((confLoop = configFetch("looping_delay")) != NULL) {
			l = *confLoop;
		}

		if(l == 0 || l > 2592000) {
			break;
		}
		else {
			l *= 60;

			timerWait(l);
		}
	}

	/*
	 *
	 * Terminate program.
	 *
	 */

	return(0);
}
