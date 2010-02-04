struct cmdArray cmdArrays[] = {
	{ PRIVILEGE_LEVEL_READ, "pullMisc", NULL, pullMisc, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listMachine", NULL, listMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullMachine", NULL, pullMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullMachineByID", NULL, pullMachineByID, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newMachine", NULL, newMachine, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushMachine", NULL, pushMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchMachine", NULL, searchMachine, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteMachine", NULL, deleteMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listDisposedMachine", NULL, listDisposedMachine, replyFree },
	{ PRIVILEGE_LEVEL_RESTORE, "restoreDisposedMachine", NULL, restoreDisposedMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullDisposedMachine", NULL, pullDisposedMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullDisposedMachineByID", NULL, pullDisposedMachineByID, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushDisposedMachine", NULL, pushDisposedMachine, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchDisposedMachine", NULL, searchDisposedMachine, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteDisposedMachine", NULL, deleteDisposedMachine, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listFaction", NULL, listFaction, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listMyFaction", NULL, listMyFaction, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullFaction", NULL, pullFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newFaction", NULL, newFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushFaction", NULL, pushFaction, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchFaction", NULL, searchFaction, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteFaction", NULL, deleteFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachFaction", NULL, attachFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainFaction", NULL, attachDomainFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalFaction", NULL, attachGlobalFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeFaction", NULL, removeFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainFaction", NULL, removeDomainFaction, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalFaction", NULL, removeGlobalFaction, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedFaction", NULL, attachedFaction, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listFile", NULL, listFile, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listMyFile", NULL, listMyFile, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullFile", NULL, pullFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newFile", NULL, newFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushFile", NULL, pushFile, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchFile", NULL, searchFile, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteFile", NULL, deleteFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachFile", NULL, attachFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainFile", NULL, attachDomainFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalFile", NULL, attachGlobalFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeFile", NULL, removeFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainFile", NULL, removeDomainFile, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalFile", NULL, removeGlobalFile, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedFile", NULL, attachedFile, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listPassword", NULL, listPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listMyPassword", NULL, listMyPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullPassword", NULL, pullPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newPassword", NULL, newPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushPassword", NULL, pushPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "encryptPassword", NULL, encryptPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "decryptPassword", NULL, decryptPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchPassword", NULL, searchPassword, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deletePassword", NULL, deletePassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachPassword", NULL, attachPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainPassword", NULL, attachDomainPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalPassword", NULL, attachGlobalPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removePassword", NULL, removePassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainPassword", NULL, removeDomainPassword, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalPassword", NULL, removeGlobalPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedPassword", NULL, attachedPassword, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listDevice", NULL, listDevice, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullDevice", NULL, pullDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newDevice", NULL, newDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushDevice", NULL, pushDevice, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchDevice", NULL, searchDevice, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteDevice", NULL, deleteDevice, replyFree },
	{ PRIVILEGE_LEVEL_RESTORE, "restoreDevice", NULL, restoreDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDevice", NULL, attachDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainDevice", NULL, attachDomainDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalDevice", NULL, attachGlobalDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDeviceToDevice", NULL, attachDeviceToDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalDeviceToDevice", NULL, attachGlobalDeviceToDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDeviceToPeripheral", NULL, attachDeviceToPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalDeviceToPeripheral", NULL, attachGlobalDeviceToPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDevice", NULL, removeDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainDevice", NULL, removeDomainDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalDevice", NULL, removeGlobalDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDeviceFromDevice", NULL, removeDeviceFromDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalDeviceFromDevice", NULL, removeGlobalDeviceFromDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDeviceFromPeripheral", NULL, removeDeviceFromPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalDeviceFromPeripheral", NULL, removeGlobalDeviceFromPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedDevice", NULL, attachedDevice, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedDeviceDevice", NULL, attachedDeviceDevice, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedDevicePeripheral", NULL, attachedDevicePeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listDisposedDevice", NULL, listDisposedDevice, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listPeripheral", NULL, listPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullPeripheral", NULL, pullPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newPeripheral", NULL, newPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushPeripheral", NULL, pushPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchPeripheral", NULL, searchPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deletePeripheral", NULL, deletePeripheral, replyFree },
	{ PRIVILEGE_LEVEL_RESTORE, "restorePeripheral", NULL, restorePeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachPeripheral", NULL, attachPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainPeripheral", NULL, attachDomainPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalPeripheral", NULL, attachGlobalPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachPeripheralToDevice", NULL, attachPeripheralToDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalPeripheralToDevice", NULL, attachGlobalPeripheralToDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachPeripheralToPeripheral", NULL, attachPeripheralToPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalPeripheralToPeripheral", NULL, attachGlobalPeripheralToPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removePeripheral", NULL, removePeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainPeripheral", NULL, removeDomainPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalPeripheral", NULL, removeGlobalPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removePeripheralFromDevice", NULL, removePeripheralFromDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalPeripheralFromDevice", NULL, removeGlobalPeripheralFromDevice, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removePeripheralFromPeripheral", NULL, removePeripheralFromPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalPeripheralFromPeripheral", NULL, removeGlobalPeripheralFromPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedPeripheral", NULL, attachedPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedPeripheralDevice", NULL, attachedPeripheralDevice, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedPeripheralPeripheral", NULL, attachedPeripheralPeripheral, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listDisposedPeripheral", NULL, listDisposedPeripheral, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listService", NULL, listService, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listProvider", NULL, listProvider, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullService", NULL, pullService, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullProvider", NULL, pullProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newService", NULL, newService, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "newProvider", NULL, newProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushService", NULL, pushService, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "pushProvider", NULL, pushProvider, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchService", NULL, searchService, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchProvider", NULL, searchProvider, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteService", NULL, deleteService, replyFree },
	{ PRIVILEGE_LEVEL_DELETE, "deleteProvider", NULL, deleteProvider, replyFree },
	{ PRIVILEGE_LEVEL_RESTORE, "restoreService", NULL, restoreService, replyFree },
	{ PRIVILEGE_LEVEL_RESTORE, "restoreProvider", NULL, restoreProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachProvider", NULL, attachProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachDomainProvider", NULL, attachDomainProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "attachGlobalProvider", NULL, attachGlobalProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeProvider", NULL, removeProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeDomainProvider", NULL, removeDomainProvider, replyFree },
	{ PRIVILEGE_LEVEL_WRITE, "removeGlobalProvider", NULL, removeGlobalProvider, replyFree },
	{ PRIVILEGE_LEVEL_READ, "attachedProvider", NULL, attachedProvider, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listDisposedService", NULL, listDisposedService, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listDisposedProvider", NULL, listDisposedProvider, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listHelp", NULL, listHelp, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullHelp", NULL, pullHelp, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchHelp", NULL, searchHelp, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listTCP", NULL, listTCP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullTCP", NULL, pullTCP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchTCP", NULL, searchTCP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "listUDP", NULL, listUDP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullUDP", NULL, pullUDP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchUDP", NULL, searchUDP, replyFree },

	{ PRIVILEGE_LEVEL_READ, "listRGB", NULL, listRGB, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullRGB", NULL, pullRGB, replyFree },
	{ PRIVILEGE_LEVEL_READ, "searchRGB", NULL, searchRGB, replyFree },

	{ PRIVILEGE_LEVEL_SUPERVISOR, "listLog", NULL, listLog, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullLog", NULL, pullLog, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "searchLog", NULL, searchLog, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "listHistory", NULL, listHistory, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullHistory", NULL, pullHistory, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "searchHistory", NULL, searchHistory, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullDatabaseStatus", NULL, pullDatabaseStatus, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullDatabaseVariables", NULL, pullDatabaseVariables, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullDatabaseErrors", NULL, pullDatabaseErrors, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullDatabaseWarnings", NULL, pullDatabaseWarnings, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullDatabaseTablestatus", NULL, pullDatabaseTablestatus, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "listSession", NULL, listSession, replyFree },

	{ PRIVILEGE_LEVEL_SUPERVISOR, "listUser", NULL, listUser, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pullUser", NULL, pullUser, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "searchUser", NULL, searchUser, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "newUser", NULL, newUser, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pushUser", NULL, pushOwnUser, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pushUserUser", NULL, pushUserUser, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "deleteUser", NULL, deleteUser, replyFree },

	{ PRIVILEGE_LEVEL_PREAUTH, "tryLogin", NULL, tryLogin, replyFree },
	{ PRIVILEGE_LEVEL_PREAUTH, "tryLogout", NULL, tryLogout, replyFree },
	{ PRIVILEGE_LEVEL_READ, "changePassword", NULL, changeOwnPassword, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "changeUserPassword", NULL, changeUserPassword, replyFree },
	{ PRIVILEGE_LEVEL_READ, "isAuthLDAP", NULL, isAuthLDAP, replyFree },
	{ PRIVILEGE_LEVEL_READ, "isUserAdmin", NULL, isUserAdmin, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pullPrivilegeLevel", NULL, pullPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "newPrivilegeLevel", NULL, newPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "newDefaultPrivilegeLevel", NULL, newDefaultPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pushPrivilegeLevel", NULL, pushPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "pushDefaultPrivilegeLevel", NULL, pushDefaultPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "checkDefaultPrivilegeLevel", NULL, checkDefaultPrivilegeLevel, replyFree },
	{ PRIVILEGE_LEVEL_SUPERVISOR, "deletePrivilegeLevel", NULL, deletePrivilegeLevel, replyFree },

	{ PRIVILEGE_LEVEL_READ, "pullTemp", NULL, pullTemp, replyFree },
	{ PRIVILEGE_LEVEL_READ, "pushTemp", NULL, pushTemp, replyFree },

	{ PRIVILEGE_LEVEL_NONE, NULL, NULL, NULL, NULL }
};

struct cmdArray sessArrays[] = {
	{ PRIVILEGE_LEVEL_NONE, "needLogin", NULL, needLogin, replyFree },
	{ PRIVILEGE_LEVEL_NONE, "needPerms", NULL, needPerms, replyFree },
	{ PRIVILEGE_LEVEL_NONE, NULL, NULL, NULL, NULL }
};

struct cmdArray replyArrays[] = {
	{ PRIVILEGE_LEVEL_NONE, "appn", NULL, appGetName, NULL },
	{ PRIVILEGE_LEVEL_NONE, "appv", NULL, appGetVersion, NULL },
	{ PRIVILEGE_LEVEL_NONE, "type", NULL, appGetDataPacket, NULL },
	{ PRIVILEGE_LEVEL_NONE, "rply", NULL, replyThis, NULL },
	{ PRIVILEGE_LEVEL_NONE, "term", NULL, termNull, NULL },
	{ PRIVILEGE_LEVEL_NONE, NULL, NULL, NULL, NULL }
};
