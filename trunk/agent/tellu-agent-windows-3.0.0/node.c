#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dsgetdc.h>
#include <lm.h>
#include <lmcons.h>

#include "declarations.h"
#include "defines.h"
#include "node.h"



void nodeInitNames(void) {
	unsigned int k;

	DWORD newLength, newLevel, newProduct;
	FARPROC apiBufferFree, getDcName, getProductInfo, userGetInfo, multiByteToWideChar, wideCharToMultiByte;
	HKEY newKey;
	HMODULE modKernel, modNetapi;
	LPUSER_INFO_10 newBuffer;
	OSVERSIONINFO newVersion;
	OSVERSIONINFOEX newVersionEx;
	PDOMAIN_CONTROLLER_INFO newInfo;
	SYSTEM_INFO newMachine;
	TCHAR newString[CONFIG_SPACE_SIZE];
	WCHAR newWString[CONFIG_SPACE_SIZE];

	memset(&nodeData, 0, sizeof(nodeData));

	newLength = sizeof(nodeData.node);

	// Resolve node name

	if(GetComputerName(nodeData.node, &newLength) == 0) {
		nodeData.node[0] = 0;
	}

	// Resolve domain name

	if((modNetapi = LoadLibrary("netapi32.dll")) != NULL) {
		getDcName = GetProcAddress(modNetapi, "DsGetDcNameA");
		apiBufferFree = GetProcAddress(modNetapi, "NetApiBufferFree");

		if(getDcName != NULL && apiBufferFree != NULL) {
			if((getDcName)(NULL, NULL, NULL, NULL, NULL, &newInfo) == NO_ERROR) {
				if(newInfo->DomainName != NULL) {
					if(newInfo->DomainName[0] != 0) {
						_snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", newInfo->DomainName, 0);
					}
				}

				(apiBufferFree)(newInfo);
			}
		}

		FreeLibrary(modNetapi);
	}

	if(nodeData.domain[0] == 0) {
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
			newLength = sizeof(newString);

			if(RegQueryValueEx(newKey, "Domain", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
				if(newLength > 0) {
					_snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", newString, 0);
				}
			}

			RegCloseKey(newKey);
		}
		else if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\VxD\\MSTCP", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
			newLength = sizeof(newString);

			if(RegQueryValueEx(newKey, "Domain", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
				if(newLength > 0) {
					_snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", newString, 0);
				}
			}

			RegCloseKey(newKey);
		}
		else {
			nodeData.domain[0] = 0;
		}
	}

	// Resolve system type and release

	newVersionEx.dwOSVersionInfoSize = sizeof(newVersionEx);

	if(GetVersionEx(&newVersionEx) != 0) {
		switch(newVersionEx.dwPlatformId) {
			case VER_PLATFORM_WIN32_NT:
				if(newVersionEx.dwMajorVersion <= 4) {
					_snprintf(nodeData.system, sizeof(nodeData.system), "Windows NT%c", 0);

					if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
						newLength = sizeof(newString);

						if(RegQueryValueEx(newKey, "ProductType", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							if(lstrcmpi("WinNT", newString) == 0) {
								if(newVersionEx.dwMajorVersion <= 4) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Workstation%c", 0);
								}
								else if(newVersionEx.dwMajorVersion == 5) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional%c", 0);
								}
							}
							else if((lstrcmpi("ServerNT", newString) == 0) || (lstrcmpi("LanmanNT", newString) == 0)) {
								_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server%c", 0);
							}
						}

						RegCloseKey(newKey);
					}
				}
				else if(newVersionEx.dwMajorVersion == 5) {
					if(newVersionEx.dwMinorVersion == 0) {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2000%c", 0);
					}
					else if(newVersionEx.dwMinorVersion == 1) {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows XP%c", 0);
					}
					else if(newVersionEx.dwMinorVersion == 2) {
						if(GetSystemMetrics(SM_SERVERR2) != 0) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2003 R2%c", 0);
						}
						else {
							if(newVersionEx.wSuiteMask == 0x00008000) {
								_snprintf(nodeData.system, sizeof(nodeData.system), "Windows Home%c", 0);
							}
							else {
								_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2003%c", 0);
							}
						}
					}
					else {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
					}

					if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
						newLength = sizeof(newString);

						if(RegQueryValueEx(newKey, "ProductType", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							if(lstrcmpi("WinNT", newString) == 0) {
								if(newVersionEx.dwMajorVersion <= 4) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Workstation%c", 0);
								}
								else if(newVersionEx.dwMajorVersion == 5) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional%c", 0);
								}
							}
							else if((lstrcmpi("ServerNT", newString) == 0) || (lstrcmpi("LanmanNT", newString) == 0)) {
								_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server%c", 0);
							}
						}

						RegCloseKey(newKey);
					}
				}
				else if(newVersionEx.dwMajorVersion == 6) {
					if(newVersionEx.dwMinorVersion == 0) {
						if(newVersionEx.wProductType == VER_NT_WORKSTATION) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows Vista%c", 0);
						}
						else {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2008%c", 0);
						}
					}
					else if(newVersionEx.dwMinorVersion == 1) {
						if(newVersionEx.wProductType == VER_NT_WORKSTATION) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 7%c", 0);
						}
						else {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2008 R2%c", 0);
						}
					}
					else {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
					}

					newProduct = 0;

					if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
						if((getProductInfo = GetProcAddress(modKernel, "GetProductInfo")) != NULL) {
							if((getProductInfo)(newVersionEx.dwMajorVersion, newVersionEx.dwMinorVersion, 0, 0, &newProduct) != 0) {
								switch(newProduct) {
									case 0x00000006:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business%c", 0);

										break;
									case 0x00000010:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business N%c", 0);

										break;
									case 0x00000012:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "HPC Edition%c", 0);

										break;
									case 0x00000008:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Datacenter%c", 0);

										break;
									case 0x0000000c:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Datacenter%c", 0);

										break;
									case 0x00000027:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Datacenter w/o Hyper-V%c", 0);

										break;
									case 0x00000025:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Datacenter w/o Hyper-V%c", 0);

										break;
									case 0x00000004:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Enterprise%c", 0);

										break;
									case 0x00000046:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Enterprise E%c", 0);

										break;
									case 0x0000001b:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Enterprise N%c", 0);

										break;
									case 0x0000000a:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Enterprise%c", 0);

										break;
									case 0x0000000e:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Enterprise%c", 0);

										break;
									case 0x00000029:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Enterprise w/o Hyper-V%c", 0);

										break;
									case 0x0000000f:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Enterprise%c", 0);

										break;
									case 0x00000026:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Enterprise w/o Hyper-V%c", 0);

										break;
									case 0x00000002:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Basic%c", 0);

										break;
									case 0x00000043:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Basic E%c", 0);

										break;
									case 0x00000005:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Basic N%c", 0);

										break;
									case 0x00000003:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Premium%c", 0);

										break;
									case 0x00000044:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Premium E%c", 0);

										break;
									case 0x0000001a:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Home Premium N%c", 0);

										break;
									case 0x0000002a:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Hyper-V Server%c", 0);

										break;
									case 0x0000001e:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business Management Server%c", 0);

										break;
									case 0x00000020:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business Messaging Server%c", 0);

										break;
									case 0x0000001f:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business Security Server%c", 0);

										break;
									case 0x00000030:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional%c", 0);

										break;
									case 0x00000045:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional E%c", 0);

										break;
									case 0x00000031:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional N%c", 0);

										break;
									case 0x00000018:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business Server%c", 0);

										break;
									case 0x00000023:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Business Server w/o Hyper-V%c", 0);

										break;
									case 0x00000021:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server Foundation%c", 0);

										break;
									case 0x00000009:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Small Business Server%c", 0);

										break;
									case 0x00000007:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Standard Server%c", 0);

										break;
									case 0x0000000d:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Standard Server%c", 0);

										break;
									case 0x00000028:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Standard Server w/o Hyper-V%c", 0);

										break;
									case 0x00000024:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Standard Server w/o Hyper-V%c", 0);

										break;
									case 0x0000000b:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Starter%c", 0);

										break;
									case 0x00000042:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Starter E%c", 0);

										break;
									case 0x0000002f:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Starter N%c", 0);

										break;
									case 0x00000017:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Enterprise Storage Server%c", 0);

										break;
									case 0x00000014:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Express Storage Server%c", 0);

										break;
									case 0x00000015:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Standard Storage Server%c", 0);

										break;
									case 0x00000016:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Workgroup Storage Server%c", 0);

										break;
									case 0x00000001:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Ultimate%c", 0);

										break;
									case 0x00000047:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Ultimate E%c", 0);

										break;
									case 0x0000001c:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Ultimate N%c", 0);

										break;
									case 0x00000011:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Web Server%c", 0);

										break;
									case 0x0000001d:
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Web Server%c", 0);

										break;
									default:
										newProduct = 0;

										break;
								}
							}
							else {
								newProduct = 0;
							}
						}

						FreeLibrary(modKernel);
					}

					if(newProduct == 0) {
						if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
							newLength = sizeof(newString);

							if(RegQueryValueEx(newKey, "ProductType", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
								if(lstrcmpi("WinNT", newString) == 0) {
									if(newVersionEx.dwMajorVersion <= 4) {
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Workstation%c", 0);
									}
									else if(newVersionEx.dwMajorVersion == 5) {
										_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional%c", 0);
									}
								}
								else if((lstrcmpi("ServerNT", newString) == 0) || (lstrcmpi("LanmanNT", newString) == 0)) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server%c", 0);
								}
							}

							RegCloseKey(newKey);
						}
					}
				}
				else {
					_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
				}

				if(nodeData.system[0] == 0) {
					if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
						newLength = sizeof(newString);

						if(RegQueryValueEx(newKey, "ProductName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "%s%c", newString, 0);
						}

						RegCloseKey(newKey);
					}
					else if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
						newLength = sizeof(newString);

						if(RegQueryValueEx(newKey, "ProductName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "%s%c", newString, 0);
						}

						RegCloseKey(newKey);
					}
					else {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
					}
				}

				_snprintf(nodeData.release, sizeof(nodeData.release), "%lu.%lu%c", newVersionEx.dwMajorVersion, newVersionEx.dwMinorVersion, 0);

				break;
			case VER_PLATFORM_WIN32_WINDOWS:
				if((newVersionEx.dwMajorVersion > 4) || ((newVersionEx.dwMajorVersion == 4) && (newVersionEx.dwMinorVersion > 0))) {
					_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 98%c", 0);
				}
				else {
					_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 95%c", 0);
				}

				_snprintf(nodeData.release, sizeof(nodeData.release), "%lu.%lu%c", (DWORD)(HIBYTE(HIWORD(newVersionEx.dwBuildNumber))), (DWORD)(LOBYTE(HIWORD(newVersionEx.dwBuildNumber))), 0);

				break;
			default:
				_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);

				break;
		}

		k = strlen(nodeData.release);

		if(newVersionEx.szCSDVersion[0] != 0) {
			if(nodeData.release[0] == 0) {
				k += _snprintf(nodeData.release + k, sizeof(nodeData.release) - k, "%s%c", newVersionEx.szCSDVersion, 0);
			}
			else {
				k += _snprintf(nodeData.release + k, sizeof(nodeData.release) - k, ", %s%c", newVersionEx.szCSDVersion, 0);
			}
		}
	}
	else {
		newVersion.dwOSVersionInfoSize = sizeof(newVersion);

		if(GetVersionEx(&newVersion) != 0) {
			switch(newVersion.dwPlatformId) {
				case VER_PLATFORM_WIN32_NT:
					if(newVersion.dwMajorVersion <= 4) {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows NT%c", 0);
					}
					else if(newVersion.dwMajorVersion == 5) {
						if(newVersion.dwMinorVersion == 0) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2000%c", 0);
						}
						else if(newVersion.dwMinorVersion == 1) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows XP%c", 0);
						}
						else if(newVersion.dwMinorVersion == 2) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 2003%c", 0);
						}
						else {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
						}
					}
					else if(newVersion.dwMajorVersion == 6) {
						if(newVersion.dwMinorVersion == 0) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows Vista%c", 0);
						}
						else if(newVersion.dwMinorVersion == 1) {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 7%c", 0);
						}
						else {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
						}
					}
					else {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
					}

					if(nodeData.system[0] == 0) {
						if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
							newLength = sizeof(newString);

							if(RegQueryValueEx(newKey, "ProductName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
								_snprintf(nodeData.system, sizeof(nodeData.system), "%s%c", newString, 0);
							}

							RegCloseKey(newKey);
						}
						else if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
							newLength = sizeof(newString);

							if(RegQueryValueEx(newKey, "ProductName", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
								_snprintf(nodeData.system, sizeof(nodeData.system), "%s%c", newString, 0);
							}

							RegCloseKey(newKey);
						}
						else {
							_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);
						}
					}

					if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\ProductOptions", 0, KEY_QUERY_VALUE, &newKey) == ERROR_SUCCESS) {
						newLength = sizeof(newString);

						if(RegQueryValueEx(newKey, "ProductType", NULL, NULL, (LPBYTE) &newString, &newLength) == ERROR_SUCCESS) {
							if(lstrcmpi("WinNT", newString) == 0) {
								if(newVersion.dwMajorVersion <= 4) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Workstation%c", 0);
								}
								else if(newVersion.dwMajorVersion == 5) {
									_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Professional%c", 0);
								}
							}
							else if((lstrcmpi("ServerNT", newString) == 0) || (lstrcmpi("LanmanNT", newString) == 0)) {
								_snprintf(nodeData.distribution, sizeof(nodeData.distribution), "Server%c", 0);
							}
						}

						RegCloseKey(newKey);
					}

					_snprintf(nodeData.release, sizeof(nodeData.release), "%lu.%lu%c", newVersion.dwMajorVersion, newVersion.dwMinorVersion, 0);

					break;
				case VER_PLATFORM_WIN32_WINDOWS:
					if((newVersion.dwMajorVersion > 4) || ((newVersion.dwMajorVersion == 4) && (newVersion.dwMinorVersion > 0))) {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 98%c", 0);
					}
					else {
						_snprintf(nodeData.system, sizeof(nodeData.system), "Windows 95%c", 0);
					}

					_snprintf(nodeData.release, sizeof(nodeData.release), "%lu.%lu%c", (DWORD)(HIBYTE(HIWORD(newVersion.dwBuildNumber))), (DWORD)(LOBYTE(HIWORD(newVersion.dwBuildNumber))), 0);

					break;
				default:
					_snprintf(nodeData.system, sizeof(nodeData.system), "Windows%c", 0);

					break;
			}
		}

		k = strlen(nodeData.release);

		if(newVersion.szCSDVersion[0] != 0) {
			if(nodeData.release[0] == 0) {
				k += _snprintf(nodeData.release + k, sizeof(nodeData.release) - k, "%s%c", newVersion.szCSDVersion, 0);
			}
			else {
				k += _snprintf(nodeData.release + k, sizeof(nodeData.release) - k, ", %s%c", newVersion.szCSDVersion, 0);
			}
		}
	}

	// Resolve system architecture

	GetSystemInfo(&newMachine);

	switch(newMachine.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_ARM:
			_snprintf(nodeData.machine, sizeof(nodeData.machine), "ARM%c", 0);

			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			_snprintf(nodeData.machine, sizeof(nodeData.machine), "x86%c", 0);

			break;
		case PROCESSOR_ARCHITECTURE_MIPS:
			_snprintf(nodeData.machine, sizeof(nodeData.machine), "MIPS%c", 0);

			break;
		case PROCESSOR_ARCHITECTURE_SHX:
			_snprintf(nodeData.machine, sizeof(nodeData.machine), "Hitachi%c", 0);

			break;
		default:
			_snprintf(nodeData.machine, sizeof(nodeData.machine), "%c", 0);

			break;
	}

	// Resolve user uid

	newLength = sizeof(nodeData.useruid);

	if(GetUserName(nodeData.useruid, &newLength) == 0) {
		nodeData.useruid[0] = 0;
	}

	// Resolve user real name

	if((modNetapi = LoadLibrary("netapi32.dll")) != NULL) {
		if((modKernel = LoadLibrary("kernel32.dll")) != NULL) {
			userGetInfo = GetProcAddress(modNetapi, "NetUserGetInfo");
			apiBufferFree = GetProcAddress(modNetapi, "NetApiBufferFree");
			multiByteToWideChar = GetProcAddress(modKernel, "MultiByteToWideChar");
			wideCharToMultiByte = GetProcAddress(modKernel, "WideCharToMultiByte");

			if(userGetInfo != NULL && apiBufferFree != NULL && multiByteToWideChar != NULL && wideCharToMultiByte != NULL) {
				if(nodeData.useruid[0] != 0) {
					if((multiByteToWideChar)(0, 0, nodeData.useruid, -1, newWString, sizeof(newWString)) != 0) {
						newLevel = 10;

						if((userGetInfo)(NULL, newWString, newLevel, (LPBYTE *) &newBuffer) == NERR_Success) {
							if(newBuffer != NULL) {
								if((wideCharToMultiByte)(0, 0, newBuffer->usri10_full_name, -1, nodeData.usergecos, sizeof(nodeData.usergecos), 0, 0) == 0) {
									nodeData.usergecos[0] = 0;
								}

								(apiBufferFree)(newBuffer);
							}
						}
					}
				}
			}

			FreeLibrary(modKernel);
		}

		FreeLibrary(modNetapi);
	}
}

char *nodeFetchNode(void) {
	if(nodeData.node[0] == 0 && nodeData.nodeWhined == 0) {
		warningMessage(ERROR_NOERROR, "Error occurred while trying to fetch local node name");

		nodeData.nodeWhined++;
	}

	return(nodeData.node);
}

char *nodeFetchDomain(void) {
	char *confChar;

	if((confChar = configFetch("domain_override")) != NULL) {
		_snprintf(nodeData.domain, sizeof(nodeData.domain), "%s%c", confChar, 0);
	}

	if(nodeData.domain[0] == 0 && nodeData.domainWhined == 0) {
		warningMessage(ERROR_NOERROR, "Error occurred while trying to fetch local domain name, it may be necessary to set it in configuration");

		nodeData.domainWhined++;
	}

	return(nodeData.domain);
}

char *nodeFetchSystem(void) {
	return(nodeData.system);
}

char *nodeFetchRelease(void) {
	return(nodeData.release);
}

char *nodeFetchDistribution(void) {
	return(nodeData.distribution);
}

char *nodeFetchMachine(void) {
	return(nodeData.machine);
}

char *nodeFetchUserLogin(void) {
	return(nodeData.useruid);
}

char *nodeFetchUserName(void) {
	return(nodeData.usergecos);
}

char *nodeFetchUserHome(void) {
	return(nodeData.userhomedir);
}

char *nodeFetchUserGroup(void) {
	return(nodeData.usergrp);
}
