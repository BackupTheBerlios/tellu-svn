char **halDevices;

DBusConnection *dbusConnection;
DBusError dbusError;

LibHalContext *halContext;
LibHalPropertyType halPropertyType;
LibHalPropertySetIterator halIterator;

struct sysPointer {
	char *name;
	int ptr;
};

struct sysPointer sysPointers[] = {
	{ "system.board.vendor", 0 },
	{ "system.board.product", DATA_STRING_SIZE },
	{ "system.board.version", DATA_STRING_SIZE * 2 },
	{ "system.hardware.vendor", DATA_STRING_SIZE * 3 },
	{ "system.hardware.product", DATA_STRING_SIZE * 4 },
	{ "system.hardware.version", DATA_STRING_SIZE * 5 },
	{ NULL, 0 }
};
