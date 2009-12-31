#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "structures.h"
#include "hal.h"



int halFetchInit(void) {
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
}

void halFetchFree(void) {
	if(halDevices != NULL) {
		libhal_free_string_array(halDevices);

		halDevices = NULL;
	}

	if(halContext != NULL) {
		libhal_ctx_shutdown(halContext, &dbusError);
		libhal_ctx_free(halContext);

		halContext = NULL;
	}
}

struct halStore *halFetchItem(int halIteration) {
	int i, k, l, p;

	unsigned int halElements;
	int halInt32;
	long long halInt64;
	double halDouble;
	dbus_bool_t halBool;

	char *halKey, *halString;
	char **halStrings, **tmpStrings;

	LibHalPropertySet *halProperty;

	struct halStore *pHalStore;

	pHalStore = NULL;

	halProperty = libhal_device_get_all_properties(halContext, halDevices[halIteration], &dbusError);
	halElements = libhal_property_set_get_num_elems(halProperty);

	if(halElements > 0) {
		if((pHalStore = (struct halStore *) malloc(sizeof(struct halStore))) == NULL) {
			return(NULL);
		}

		memset(pHalStore, 0, sizeof(struct halStore));

		libhal_psi_init(&halIterator, halProperty);

		while(libhal_psi_has_more(&halIterator) == TRUE) {
			halKey = libhal_psi_get_key(&halIterator);

			k = 0;
			p = 0;

			for(i = 0; ; i++) {
				if(halPointers[i].name == NULL) {
					break;
				}

				if(strncasecmp(halPointers[i].name, halKey, strlen(halPointers[i].name)) == 0) {
					p = halPointers[i].ptr;

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
				case LIBHAL_PROPERTY_TYPE_INT32:
					halInt32 = libhal_device_get_property_int(halContext, halDevices[halIteration], halKey, &dbusError);

					snprintf((char *) pHalStore + p, DATA_STRING_SIZE, "%d%c", halInt32, 0);

					break;
				case LIBHAL_PROPERTY_TYPE_UINT64:
					halInt64 = libhal_device_get_property_uint64(halContext, halDevices[halIteration], halKey, &dbusError);

					snprintf((char *) pHalStore + p, DATA_STRING_SIZE, "%lld%c", halInt64, 0);

					break;
				case LIBHAL_PROPERTY_TYPE_DOUBLE:
					halDouble = libhal_device_get_property_double(halContext, halDevices[halIteration], halKey, &dbusError);

					snprintf((char *) pHalStore + p, DATA_STRING_SIZE, "%f%c", halDouble, 0);

					break;
				case LIBHAL_PROPERTY_TYPE_BOOLEAN:
					halBool = libhal_device_get_property_bool(halContext, halDevices[halIteration], halKey, &dbusError);

					snprintf((char *) pHalStore + p, DATA_STRING_SIZE, "%d%c", halBool, 0);

					break;
				case LIBHAL_PROPERTY_TYPE_STRING:
					halString = libhal_device_get_property_string(halContext, halDevices[halIteration], halKey, &dbusError);

					snprintf((char *) pHalStore + p, DATA_STRING_SIZE, "%s%c", halString, 0);

					break;
				case LIBHAL_PROPERTY_TYPE_STRLIST:
					halStrings = libhal_device_get_property_strlist(halContext, halDevices[halIteration], halKey, &dbusError);

					if(halStrings != NULL) {
						tmpStrings = halStrings;

						l = 0;

						while(*tmpStrings != NULL) {
							l += snprintf((char *) pHalStore + p + l, DATA_STRING_SIZE, "%s%c", *tmpStrings, ITEM_SPLITTER);

							tmpStrings++;
						}

						snprintf((char *) pHalStore + p + l, DATA_STRING_SIZE, "%c", 0);

						libhal_free_string_array(halStrings);
					}

					break;
				default:
					break;
			}

			libhal_psi_next(&halIterator);
		}
	}

	libhal_free_property_set(halProperty);

	return(pHalStore);
}

char *halGetDevices(struct paramInfo * pi) {
	int i, k, l;

	char *newBuffer, *tmpBuffer;

	size_t t;
	size_t newBuflen, newBuffil;

	struct halStore *pHalStore;

	newBuffil = 0;
	newBuflen = DATA_BLOCK_SIZE;

	if((newBuffer = malloc(newBuflen)) == NULL) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for device info buffer");

		return(NULL);
	}

	pHalStore = NULL;

	k = halFetchInit();
	l = 0;

	for(i = 0; i < k; i++) {
		if((pHalStore = halFetchItem(i)) == NULL) {
			break;
		}

		if(pHalStore->info_category[0] == 0) {
			pHalStore = NULL;

			continue;
		}

		if(newBuflen - newBuffil <= DATA_BLOCK_SIZE) {
			newBuflen += DATA_BLOCK_SIZE * 20;

			if((tmpBuffer = realloc(newBuffer, newBuflen)) == NULL) {
				free(newBuffer);

				warningMessage(ERROR_SLIGHT, "Error occurred while trying to allocate memory for device info buffer");

				return(NULL);
			}

			newBuffer = tmpBuffer;
		}

		newBuffil += DATA_BLOCK_SIZE * 20;

		t = strlen(HAL_ACADAPTER);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_ACADAPTER, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "acadapter%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_BATTERY);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_BATTERY, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "battery%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_BLUETOOTHACL);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_BLUETOOTHACL, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "btacl%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_BLUETOOTHHCI);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_BLUETOOTHHCI, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "bthci%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_BLUETOOTHSCO);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_BLUETOOTHSCO, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "btsco%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_BUTTON);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_BUTTON, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "button%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_CAMERA);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_CAMERA, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "camera%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_IDE);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_IDE, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "ide%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_IDEHOST);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_IDEHOST, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "idehost%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_IEEE1394);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_IEEE1394, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "ieee1394%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_IEEE1394HOST);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_IEEE1394HOST, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "ieee1394host%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUT);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUT, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "input%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTJOYSTICK);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTJOYSTICK, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputjoystick%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTKEYBOARD);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTKEYBOARD, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputkeyboard%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTKEYMAP);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTKEYMAP, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputkeymap%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTKEYPAD);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTKEYPAD, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputkeypad%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTKEYS);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTKEYS, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputkeys%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTMOUSE);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTMOUSE, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputmouse%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTSWITCH);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTSWITCH, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputswitch%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_INPUTTABLET);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_INPUTTABLET, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "inputtablet%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->input_device);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_KILLSWITCH);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_KILLSWITCH, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "killswitch%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_LAPTOPPANEL);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_LAPTOPPANEL, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "panel%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_LIGHTSENSOR);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_LIGHTSENSOR, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "lightsensor%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_MMC);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_MMC, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "mmc%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_MMCHOST);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_MMCHOST, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "mmchost%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NET);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NET, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "net%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface, ITEM_SPLITTER, pHalStore->net_80203_mac_address);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NET80203);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NET80203, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "net80203%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface, ITEM_SPLITTER, pHalStore->net_80203_mac_address);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NET80211);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NET80211, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "net80211%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NET80211CONTROL);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NET80211CONTROL, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "net80211ctrl%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NETBLUETOOTH);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NETBLUETOOTH, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "netbluetooth%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NETBRIDGE);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NETBRIDGE, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "netbridge%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NETIRDA);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NETIRDA, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "netirda%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_NETLOOPBACK);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_NETLOOPBACK, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "netloopback%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_PCMCIASOCKET);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_PCMCIASOCKET, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "pcmciasocket%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_PORTABLEAUDIOPLAYER);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_PORTABLEAUDIOPLAYER, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "portableaudioplayer%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_POWERMANAGEMENT);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_POWERMANAGEMENT, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "powermanagement%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_PRINTER);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_PRINTER, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "printer%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_PROCESSOR);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_PROCESSOR, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "processor%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s", ITEM_SEPARATOR, pHalStore->processor_number, ITEM_SPLITTER, pHalStore->processor_can_throttle);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SCANNER);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SCANNER, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "scanner%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->net_address, ITEM_SPLITTER, pHalStore->net_arp_proto_hw_id, ITEM_SPLITTER, pHalStore->net_interface);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SCSI);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SCSI, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "scsi%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->scsi_host_host);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SCSIHOST);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SCSIHOST, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "scsihost%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->scsi_host_host);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SERIAL);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SERIAL, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "serial%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SOUND);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SOUND, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "sound%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s", ITEM_SEPARATOR, pHalStore->sound_card);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_STORAGE);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_STORAGE, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "storage%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->storage_automount_enabled_hint, ITEM_SPLITTER, pHalStore->storage_bus, ITEM_SPLITTER, pHalStore->storage_drive_type, ITEM_SPLITTER, pHalStore->storage_hotpluggable, ITEM_SPLITTER, pHalStore->storage_media_check_enabled, ITEM_SPLITTER, pHalStore->storage_model, ITEM_SPLITTER, pHalStore->storage_no_partitions_hint, ITEM_SPLITTER, pHalStore->storage_removable, ITEM_SPLITTER, pHalStore->storage_requires_eject, ITEM_SPLITTER, pHalStore->storage_size, ITEM_SPLITTER, pHalStore->block_is_volume);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_SYSTEM);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_SYSTEM, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "system%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->storage_automount_enabled_hint, ITEM_SPLITTER, pHalStore->storage_bus, ITEM_SPLITTER, pHalStore->storage_drive_type, ITEM_SPLITTER, pHalStore->storage_hotpluggable, ITEM_SPLITTER, pHalStore->storage_media_check_enabled, ITEM_SPLITTER, pHalStore->storage_model, ITEM_SPLITTER, pHalStore->storage_no_partitions_hint, ITEM_SPLITTER, pHalStore->storage_removable, ITEM_SPLITTER, pHalStore->storage_requires_eject, ITEM_SPLITTER, pHalStore->storage_size, ITEM_SPLITTER, pHalStore->block_is_volume);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_TAPE);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_TAPE, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "tape%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->storage_automount_enabled_hint, ITEM_SPLITTER, pHalStore->storage_bus, ITEM_SPLITTER, pHalStore->storage_drive_type, ITEM_SPLITTER, pHalStore->storage_hotpluggable, ITEM_SPLITTER, pHalStore->storage_media_check_enabled, ITEM_SPLITTER, pHalStore->storage_model, ITEM_SPLITTER, pHalStore->storage_no_partitions_hint, ITEM_SPLITTER, pHalStore->storage_removable, ITEM_SPLITTER, pHalStore->storage_requires_eject, ITEM_SPLITTER, pHalStore->storage_size, ITEM_SPLITTER, pHalStore->block_is_volume);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_VIDEO4LINUX);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_VIDEO4LINUX, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "v4l%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}

		t = strlen(HAL_VOLUME);

		if(strlen(pHalStore->info_category) > t) {
			t = strlen(pHalStore->info_category);
		}

		if((strncasecmp(pHalStore->info_category, HAL_VOLUME, t)) == 0) {
			l += snprintf(newBuffer + l, newBuflen, "volume%c", ITEM_SEPARATOR);
			l += snprintf(newBuffer + l, newBuflen, "%s%c%s%c%s%c%s", pHalStore->info_product, ITEM_SEPARATOR, pHalStore->info_subsystem, ITEM_SEPARATOR, pHalStore->info_capabilities, ITEM_SEPARATOR, pHalStore->info_vendor);
			l += snprintf(newBuffer + l, newBuflen, "%c%s%c%s%c%s%c%s", ITEM_SEPARATOR, pHalStore->block_device, ITEM_SPLITTER, pHalStore->block_is_volume, ITEM_SPLITTER, pHalStore->block_major, ITEM_SPLITTER, pHalStore->block_minor);
			l += snprintf(newBuffer + l, newBuflen, "%c", ITEM_DELIMITER);

			free(pHalStore);

			pHalStore = NULL;

			continue;
		}
	}

	if(pHalStore != NULL) {
		free(pHalStore);

		pHalStore = NULL;
	}

	halFetchFree();

	if(l > 0) {
		l--;
	}

	newBuffer[l] = 0;

	return(newBuffer);
}

void halFreeDevices(char *intBuffer) {
	if(intBuffer != NULL) {
		free(intBuffer);
	}
}
