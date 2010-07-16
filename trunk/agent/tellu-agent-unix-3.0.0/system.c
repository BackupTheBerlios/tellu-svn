#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#ifdef TELLU_USE_HAL
#include "system.h"
#endif



int sysFetchInit(void) {
#ifdef TELLU_USE_HAL
	int i;

	dbus_error_init(&dbusError);

	if((dbusConnection = dbus_bus_get(DBUS_BUS_SYSTEM, &dbusError)) == FALSE) {
		dbusMessage(ERROR_SLIGHT, "Error occurred while trying to initialize DBUS connection", &dbusError);

		return(0);
	}

	halContext = libhal_ctx_new();

	if(!libhal_ctx_set_dbus_connection(halContext, dbusConnection)) {
		dbusMessage(ERROR_SLIGHT, "Error occurred while trying to connect to DBUS", &dbusError);

		return(0);
	}

	if(!libhal_ctx_init(halContext, &dbusError)) {
		dbusMessage(ERROR_SLIGHT, "Error occurred while trying to initialize HAL context", &dbusError);

		return(0);
	}

	if((halDevices = libhal_get_all_devices(halContext, &i, &dbusError)) == NULL) {
		dbusMessage(ERROR_SLIGHT, "Error occurred while trying to read device list", &dbusError);

		return(0);
	}

	return(i);
#else
	return(0);
#endif
}

void sysFetchFree(void) {
#ifdef TELLU_USE_HAL
	if(halDevices != NULL) {
		libhal_free_string_array(halDevices);

		halDevices = NULL;
	}

	if(halContext != NULL) {
		libhal_ctx_shutdown(halContext, &dbusError);
		libhal_ctx_free(halContext);

		halContext = NULL;
	}
#endif
}

void sysFetchItem(struct sysInfo * si, int halIteration) {
#ifdef TELLU_USE_HAL
	int i, k;
	unsigned int halElements;

	char *halKey, *halString;

	size_t t;

	LibHalPropertySet *halProperty;

	halProperty = libhal_device_get_all_properties(halContext, halDevices[halIteration], &dbusError);
	halElements = libhal_property_set_get_num_elems(halProperty);

	if(halElements > 0) {
		libhal_psi_init(&halIterator, halProperty);

		while(libhal_psi_has_more(&halIterator) == TRUE) {
			halKey = libhal_psi_get_key(&halIterator);

			k = 0;

			for(i = 0; ; i++) {
				if(sysPointers[i].name == NULL) {
					break;
				}

				if(strncasecmp(sysPointers[i].name, halKey, strlen(sysPointers[i].name)) == 0) {
					k++;

					break;
				}
			}

			if(k == 0) {
				libhal_psi_next(&halIterator);

				continue;
			}

			halPropertyType = libhal_psi_get_type(&halIterator);

			switch(halPropertyType) {
				case LIBHAL_PROPERTY_TYPE_STRING:
					halString = libhal_device_get_property_string(halContext, halDevices[halIteration], halKey, &dbusError);

					t = strlen(SYS_SB_PRODUCT);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SB_PRODUCT, t)) == 0) {
						snprintf(si->bbproduct, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					t = strlen(SYS_SB_VENDOR);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SB_VENDOR, t)) == 0) {
						snprintf(si->bbmanufacturer, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					t = strlen(SYS_SB_VERSION);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SB_VERSION, t)) == 0) {
						snprintf(si->bbversion, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					t = strlen(SYS_SH_PRODUCT);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SH_PRODUCT, t)) == 0) {
						snprintf(si->sysproduct, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					t = strlen(SYS_SH_VENDOR);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SH_VENDOR, t)) == 0) {
						snprintf(si->sysmanufacturer, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					t = strlen(SYS_SH_VERSION);

					if(strlen(halKey) > t) {
						t = strlen(halKey);
					}

					if((strncasecmp(halKey, SYS_SH_VERSION, t)) == 0) {
						snprintf(si->sysversion, DATA_STRING_SIZE, "%s%c", halString, 0);

						break;
					}

					break;
				default:
					break;
			}

			libhal_psi_next(&halIterator);
		}
	}

	libhal_free_property_set(halProperty);
#endif
}

char *sysGetSystem(struct paramInfo * pi) {
#ifdef TELLU_USE_HAL
	int i, k;

	char *newBuffer;

	size_t newBuflen;

	struct sysInfo newInfo;

	memset(&newInfo, 0, sizeof(newInfo));

	k = sysFetchInit();

	for(i = 0; i < k; i++) {
		sysFetchItem(&newInfo, i);
	}

	sysFetchFree();

	newBuflen = strlen(newInfo.bbmanufacturer) + strlen(newInfo.bbproduct) + strlen(newInfo.bbversion) + strlen(newInfo.sysfamily) + strlen(newInfo.sysmanufacturer) + strlen(newInfo.sysproduct) + strlen(newInfo.sysversion) + 7;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for system info buffer");

		return(NULL);
	}

	snprintf(newBuffer, newBuflen, "%s%c%s%c%s%c%s%c%s%c%s%c%s%c", newInfo.bbmanufacturer, ITEM_SEPARATOR, newInfo.bbproduct, ITEM_SEPARATOR, newInfo.bbversion, ITEM_SEPARATOR, newInfo.sysfamily, ITEM_SEPARATOR, newInfo.sysmanufacturer, ITEM_SEPARATOR, newInfo.sysproduct, ITEM_SEPARATOR, newInfo.sysversion, 0);

	return(newBuffer);
#else
	return(NULL);
#endif
}

void sysFreeSystem(char *intBuffer) {
#ifdef TELLU_USE_HAL
	if(intBuffer != NULL) {
		free(intBuffer);
	}
#endif
}
