#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "declarations.h"
#include "defines.h"



int mysqlConnect(struct threadStorageInfo * db) {
	if(mysql_init(&db->mysqlHandle) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to initialize database connection", NULL);

		return(-1);
	}

	if((db->mysqlHostname = configFetch("mysql_hostname", &db->i)) == NULL) {
		db->mysqlHostname = MYSQL_HOSTNAME;
	}

	if((db->mysqlSocket = configFetch("mysql_socket", &db->i)) == NULL) {
		db->mysqlSocket = MYSQL_SOCKET;
	}

	if((db->mysqlPort = configFetch("mysql_port", &db->i)) == NULL) {
		*db->mysqlPort = MYSQL_PORT;
	}

	if((db->mysqlDatabase = configFetch("mysql_database", &db->i)) == NULL) {
		db->mysqlDatabase = MYSQL_DATABASE;
	}

	if((db->mysqlUsername = configFetch("mysql_username", &db->i)) == NULL) {
		db->mysqlUsername = MYSQL_USERNAME;
	}

	if((db->mysqlPassword = configFetch("mysql_password", &db->i)) == NULL) {
		db->mysqlPassword = MYSQL_PASSWORD;
	}

	db->mysqlFlags = 0;

	if((db->mysqlBool = configFetch("mysql_compression", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->mysqlFlags |= CLIENT_COMPRESS;
		}
	}

	if((db->mysqlBool = configFetch("mysql_encryption", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->mysqlFlags |= CLIENT_SSL;
		}
	}

	if(mysql_real_connect(&db->mysqlHandle, db->mysqlHostname, db->mysqlUsername, db->mysqlPassword, db->mysqlDatabase, *db->mysqlPort, db->mysqlSocket, 0) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to establish database connection", NULL);

		return(-1);
	}

	return(0);
}

void mysqlDisconnect(struct threadStorageInfo * db) {
	mysql_close(&db->mysqlHandle);
}

void mysqlEscape(struct threadStorageInfo * db, char *destString, char *srcString) {
	mysql_real_escape_string(&db->mysqlHandle, destString, srcString, strlen(srcString));
}

void mysqlMessage(struct threadStorageInfo * db, int fatalError, char *infoMessage, char *sqlString) {
	if(sqlString != NULL) {
		snprintf(db->errorString, sizeof(db->errorString), "%s: %s: %s%c", infoMessage, sqlString, mysql_error(&db->mysqlHandle), 0);
	}
	else {
		snprintf(db->errorString, sizeof(db->errorString), "%s: %s%c", infoMessage, mysql_error(&db->mysqlHandle), 0);
	}

	warningThread(fatalError, db->errorString, db->errorSpace, sizeof(db->errorSpace), db->a, &db->i);
}

void mysqlPush(struct threadStorageInfo * db, char *thisString) {
	db->r = strlen(thisString);

	if((db->s = mysql_real_query(&db->mysqlHandle, thisString, db->r)) != 0) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to push data to database", thisString);

		return;
	}
}

char *mysqlPull(struct threadStorageInfo * db, char *thisString) {
	db->t = CONFIG_STRING_SIZE;

	if((db->replyBuffer = malloc(db->t)) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", NULL);

		return(NULL);
	}

	if(mysql_real_query(&db->mysqlHandle, thisString, strlen(thisString)) != 0) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", thisString);

		return(NULL);
	}

	if((db->mysqlResult = mysql_use_result(&db->mysqlHandle)) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", NULL);

		return(NULL);
	}

	db->p = 0;
	db->q = 0;
	db->l = mysql_num_fields(db->mysqlResult);

	while((db->mysqlRow = mysql_fetch_row(db->mysqlResult))) {
		if((db->h = mysql_fetch_lengths(db->mysqlResult)) == NULL) {
			mysql_free_result(db->mysqlResult);

			free(db->replyBuffer);

			return(NULL);
		}

		for(db->k = 0; db->k < db->l; db->k++) {
			db->q += db->h[db->k];
		}

		if(db->t - db->p <= db->q) {
			db->t += CONFIG_STRING_SIZE;

			if((db->tmpBuffer = realloc(db->replyBuffer, db->t)) == NULL) {
				mysql_free_result(db->mysqlResult);

				free(db->replyBuffer);

				return(NULL);
			}

			db->replyBuffer = db->tmpBuffer;
		}

		for(db->k = 0; db->k < db->l; db->k++) {
			if(db->mysqlRow[db->k] == NULL || db->mysqlRow[db->k][0] == 0) {
				db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%c", ITEM_SEPARATOR);
			}
			else {
				db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%s%c", db->mysqlRow[db->k], ITEM_SEPARATOR);
			}
		}

		db->p += snprintf(db->replyBuffer + db->p, db->t - db->p, "%c", ITEM_DELIMITER);
	}

	mysql_free_result(db->mysqlResult);

	if(db->p > 1) {
		if(db->replyBuffer[db->p - 2] == ITEM_SEPARATOR) {
			db->replyBuffer[db->p - 2] = 0;
		}

		if(db->replyBuffer[db->p - 1] == ITEM_DELIMITER) {
			db->replyBuffer[db->p - 1] = 0;
		}
	}

	db->replyBuffer[db->p] = 0;

	return(db->replyBuffer);
}

char *mysqlRound(struct threadStorageInfo * db, char *thisString) {
	db->t = CONFIG_STRING_SIZE;

	if((db->replyBuffer = malloc(db->t)) == NULL) {
		mysqlMessage(db, ERROR_SLIGHT, "Error occurred while trying to pull data from database", NULL);

		return(NULL);
	}

	mysqlPush(db, thisString);

	snprintf(db->replyBuffer, db->t, "%llu%c", mysql_insert_id(&db->mysqlHandle), 0);

	return(db->replyBuffer);
}

void mysqlFree(struct threadStorageInfo * db) {
	if(db->replyBuffer != NULL) {
		free(db->replyBuffer);

		db->replyBuffer = NULL;
	}
}

void mysqlExpire(struct threadStorageInfo * db) {
	const char *newItems[] = {
		TABLE_AGENT, TABLE_AGENT, TABLE_AGENT,
		TABLECOL_MACHINE_CPU, TABLECOL_MACHINE_DAEMON, TABLECOL_MACHINE_DEV, TABLECOL_MACHINE_DISK,
		TABLECOL_MACHINE_MEM, TABLECOL_MACHINE_NIC, TABLECOL_MACHINE_PORT, TABLECOL_MACHINE_PROC,
		TABLECOL_MACHINE_RUN, TABLECOL_MACHINE_SOFTWARE, TABLECOL_MACHINE_USER, TABLECOL_MACHINE_UTIL,
		TABLECOL_MACHINE_MACHINE,
		NULL
	};

	if(mysqlConnect(db) == 0) {
		if((db->queryBuffer = malloc(CONFIG_SPACE_SIZE + 1)) != NULL) {
			// Flush expired session entries
			snprintf(
				db->queryBuffer,
				CONFIG_SPACE_SIZE,
				"DELETE FROM " TABLE_SESSION " WHERE UNIX_TIMESTAMP(" TABLECOL_SESSION_ACCESS ") < UNIX_TIMESTAMP() - " TIMER_RESOLUTION_SESSION_FLUSH "%c",
				0
			);

			mysqlPush(db, db->queryBuffer);

			// Flush expired temp entries
			snprintf(
				db->queryBuffer,
				CONFIG_SPACE_SIZE,
				"DELETE FROM " TABLE_TEMP " WHERE UNIX_TIMESTAMP(" TABLECOL_TEMP_CREATED ") < UNIX_TIMESTAMP() - " TIMER_RESOLUTION_TEMP_FLUSH "%c",
				0
			);

			mysqlPush(db, db->queryBuffer);

			// Flush disposed machines
			for(db->j = 0; ; db->j++) {
				if(newItems[db->j] == NULL) {
					break;
				}

				snprintf(
					db->queryBuffer,
					CONFIG_SPACE_SIZE,
					"DELETE FROM %s WHERE " TABLECOL_MACHINE_NID " IN (SELECT DISTINCT " TABLECOL_MACHINE_NID " FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " >= '2')%c",
					newItems[db->j],
					0
				);

				mysqlPush(db, db->queryBuffer);
			}

			snprintf(
				db->queryBuffer,
				CONFIG_SPACE_SIZE,
				"DELETE FROM " TABLECOL_MACHINE_NODE " WHERE " TABLECOL_MACHINE_DISPOSED " >= '2'%c",
				0
			);

			mysqlPush(db, db->queryBuffer);

			// Flush disposed services

			snprintf(
				db->queryBuffer,
				CONFIG_SPACE_SIZE,
				"DELETE FROM " TABLE_SERVICE " WHERE " TABLECOL_SERVICE_DISPOSED " >= '2'%c",
				0
			);

			mysqlPush(db, db->queryBuffer);

			snprintf(
				db->queryBuffer,
				CONFIG_SPACE_SIZE,
				"DELETE FROM " TABLE_SERVICE_DATA " WHERE " TABLECOL_SERVICE_DATA_DISPOSED " >= '2'%c",
				0
			);

			mysqlPush(db, db->queryBuffer);

			free(db->queryBuffer);
		}

		mysqlDisconnect(db);
	}
}

int mysqlCookie(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	memset(&db->cookieSpace, 0, sizeof(db->cookieSpace));

	db->v = (thisUidLength * 2) + CONFIG_SPACE_SIZE;

	if((db->tmpBuffer = malloc(db->v + 1)) != NULL) {
		if((db->esc3Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
			mysqlEscape(db, db->esc3Buffer, thisUid);

			db->s = 0;

			for(db->i = 0; db->i < 16; db->i++) {
				db->s += snprintf(
					db->cookieSpace + db->s,
					sizeof(db->cookieSpace) - db->s,
					"%.4x",
					randRandom(65535, &db->timeVal)
				);
			}

			db->cookieSpace[db->s] = 0;

			snprintf(
				db->tmpBuffer,
				db->v,
				"INSERT INTO " TABLE_SESSION " (" TABLECOL_SESSION_UID ", " TABLECOL_SESSION_COOKIE ") VALUES('%s', '%s')%c",
				db->esc3Buffer,
				db->cookieSpace,
				0
			);

			mysqlPush(db, db->tmpBuffer);

			free(db->tmpBuffer);
			free(db->esc3Buffer);

			return(0);
		}
		else {
			free(db->tmpBuffer);

			return(-1);
		}
	}
	else {
		return(-1);
	}
}

int mysqlInsert(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	db->v = (thisUidLength * 2) + CONFIG_SPACE_SIZE;

	if((db->tmpBuffer = malloc(db->v + 1)) != NULL) {
		if((db->esc3Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
			mysqlEscape(db, db->esc3Buffer, thisUid);

			snprintf(
				db->tmpBuffer,
				db->v,
				"SELECT " TABLECOL_USER_UID " FROM " TABLE_USERS" WHERE " TABLECOL_USER_UID " = '%s'%c",
				db->esc3Buffer,
				0
			);

			if(mysqlPull(db, db->tmpBuffer) != NULL) {
				if(strcmp(db->replyBuffer, thisUid) == 0) {
					mysqlFree(db);
				}
				else {
					mysqlFree(db);

					snprintf(
						db->tmpBuffer,
						db->v,
						"INSERT INTO " TABLE_USERS " (" TABLECOL_USER_UID ") VALUES('%s')%c",
						db->esc3Buffer,
						0
					);

					mysqlPush(db, db->tmpBuffer);
				}

				free(db->tmpBuffer);
				free(db->esc3Buffer);

				return(0);
			}
			else {
				free(db->tmpBuffer);
				free(db->esc3Buffer);

				return(-1);
			}
		}
		else {
			free(db->tmpBuffer);

			return(-1);
		}
	}
	else {
		return(-1);
	}
}

int mysqlLogin(char *thisUid, char *thisPwd, int thisUidLength, int thisPwdLength, struct threadStorageInfo * db) {
	db->e = -1;

	if(thisUid == NULL || thisUid[0] == 0) {
		return(db->e);
	}

	if(mysqlConnect(db) == 0) {
		db->u = (thisUidLength * 2) + (thisPwdLength * 2) + CONFIG_SPACE_SIZE;

		if((db->queryBuffer = malloc(db->u + 1)) != NULL) {
			if((db->esc1Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
				if((db->esc2Buffer = malloc((thisPwdLength * 2) + 1)) != NULL) {
					mysqlEscape(db, db->esc1Buffer, thisUid);

					if(thisPwd == NULL || thisPwd[0] == 0) {
						snprintf(
							db->queryBuffer,
							db->u,
							"SELECT DISTINCT " TABLECOL_USER_UID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s' AND " TABLECOL_USER_PWD " = '' AND " TABLECOL_USER_LOCKED " = '0'%c",
							db->esc1Buffer,
							0
						);
					}
					else {
						mysqlEscape(db, db->esc2Buffer, thisPwd);

						snprintf(
							db->queryBuffer,
							db->u,
							"SELECT DISTINCT " TABLECOL_USER_UID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s' AND " TABLECOL_USER_PWD " = " TABLE_PWD_HASH "('%s') AND " TABLECOL_USER_LOCKED " = '0'%c",
							db->esc1Buffer,
							db->esc2Buffer,
							0
						);
					}

					if(mysqlPull(db, db->queryBuffer) != NULL) {
						if(strcmp(db->replyBuffer, thisUid) == 0) {
							mysqlFree(db);

							mysqlCookie(thisUid, thisUidLength, db);

							db->e = 0;
						}
						else {
							mysqlFree(db);

							snprintf(
								db->queryBuffer,
								db->u,
								"DELETE FROM " TABLE_SESSION " WHERE " TABLECOL_SESSION_UID " = '%s'%c",
								db->esc1Buffer,
								0
							);

							mysqlPush(db, db->queryBuffer);
						}
					}

					memset(db->esc2Buffer, 0, (thisPwdLength * 2) + 1);

					free(db->esc2Buffer);
				}

				memset(db->esc1Buffer, 0, (thisUidLength * 2) + 1);

				free(db->esc1Buffer);
			}

			memset(db->queryBuffer, 0, db->u);

			free(db->queryBuffer);
		}

		mysqlDisconnect(db);
	}

	return(db->e);
}

int mysqlLogout(char *thisUid, int thisUidLength, struct threadStorageInfo * db) {
	db->e = -1;

	if(thisUid == NULL || thisUid[0] == 0) {
		return(db->e);
	}

	if(mysqlConnect(db) == 0) {
		db->u = (thisUidLength * 2) + CONFIG_SPACE_SIZE;

		if((db->queryBuffer = malloc(db->u + 1)) != NULL) {
			if((db->esc1Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
				mysqlEscape(db, db->esc1Buffer, thisUid);

				snprintf(
					db->queryBuffer,
					db->u,
					"DELETE FROM " TABLE_SESSION " WHERE " TABLECOL_SESSION_UID " = '%s'%c",
					db->esc1Buffer,
					0
				);

				mysqlPush(db, db->queryBuffer);

				memset(db->esc1Buffer, 0, (thisUidLength * 2) + 1);

				free(db->esc1Buffer);

				db->e = 0;
			}

			memset(db->queryBuffer, 0, db->u);

			free(db->queryBuffer);
		}

		mysqlDisconnect(db);
	}

	return(db->e);
}

int mysqlSession(char *thisCookie, char *thisUid, int thisCookieLength, int thisUidLength, struct threadStorageInfo * db) {
	db->e = 0;

	if((db->mysqlBool = configFetch("auth_ldap", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->e++;
		}
	}

	if((db->mysqlBool = configFetch("auth_internal", &db->i)) != NULL) {
		if(*db->mysqlBool == CONFIG_TYPE_BOOLEAN_YES) {
			db->e++;
		}
	}

	if(db->e == 0) {
		return(0);
	}

	db->e = -1;

	if(thisUid == NULL || thisUid[0] == 0 || thisUidLength == 0 || thisCookie == NULL || thisCookie[0] == 0 || thisCookieLength == 0) {
		return(db->e);
	}

	if(mysqlConnect(db) == 0) {
		db->u = (thisCookieLength * 2) + (thisUidLength * 2) + CONFIG_SPACE_SIZE;

		if((db->queryBuffer = malloc(db->u + 1)) != NULL) {
			if((db->esc1Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
				if((db->esc2Buffer = malloc((thisCookieLength * 2) + 1)) != NULL) {
					mysqlEscape(db, db->esc1Buffer, thisUid);
					mysqlEscape(db, db->esc2Buffer, thisCookie);

					snprintf(
						db->queryBuffer,
						db->u,
						"SELECT DISTINCT " TABLECOL_SESSION_UID " FROM " TABLE_SESSION " WHERE " TABLECOL_SESSION_COOKIE " = '%s' AND " TABLECOL_SESSION_UID " = '%s'%c",
						db->esc2Buffer,
						db->esc1Buffer,
						0
					);

					if(mysqlPull(db, db->queryBuffer) != NULL) {
						if(strcmp(db->replyBuffer, thisUid) == 0) {
							mysqlFree(db);

							snprintf(
								db->queryBuffer,
								db->u,
								"UPDATE " TABLE_SESSION " SET " TABLECOL_SESSION_ACCESS " = NOW(), " TABLECOL_SESSION_COUNT " = " TABLECOL_SESSION_COUNT " + 1 WHERE " TABLECOL_SESSION_COOKIE " = '%s' AND " TABLECOL_SESSION_UID " = '%s'%c",
								db->esc2Buffer,
								db->esc1Buffer,
								0
							);

							mysqlPush(db, db->queryBuffer);

							db->e = 0;
						}
						else {
							mysqlFree(db);
						}
					}

					memset(db->esc2Buffer, 0, (thisCookieLength * 2) + 1);

					free(db->esc2Buffer);
				}

				memset(db->esc1Buffer, 0, (thisUidLength * 2) + 1);

				free(db->esc1Buffer);
			}

			memset(db->queryBuffer, 0, db->u);

			free(db->queryBuffer);
		}

		mysqlDisconnect(db);
	}

	return(db->e);
}

int mysqlPermission(unsigned long long thisLevel, char *thisUid, char *thisItem, char *thisDomain, int thisUidLength, int thisItemLength, int thisDomainLength, struct threadStorageInfo * db) {
	if(thisUid == NULL || thisUid[0] == 0 || thisUidLength == 0) {
		return(-1);
	}

	// Always grant access if requested level is below threshold
	if(thisLevel != PRIVILEGE_LEVEL_NONE && thisLevel <= PRIVILEGE_LEVEL_DEFAULT) {
		return(0);
	}

	db->e = -1;

	// Otherwise check if access is allowed
	if(mysqlConnect(db) == 0) {
		db->u = (thisUidLength * 2) + (thisDomainLength * 2) + CONFIG_SPACE_SIZE;

		if((db->queryBuffer = malloc(db->u + 1)) != NULL) {
			if((db->esc1Buffer = malloc((thisUidLength * 2) + 1)) != NULL) {
				if((db->esc2Buffer = malloc((thisDomainLength * 2) + 1)) != NULL) {
					mysqlEscape(db, db->esc1Buffer, thisUid);

					if(thisDomain == NULL || thisDomain[0] == 0) {
						// Check for explicit permissions
						snprintf(
							db->queryBuffer,
							db->u,
							"SELECT MAX(" TABLECOL_USER_PERM ") AS " TABLECOL_USER_PERM " FROM " TABLE_PERM_NODES " WHERE " TABLECOL_USER_USID " IN (SELECT DISTINCT " TABLECOL_USER_ID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s') AND " TABLECOL_USER_DOMAIN " = ''%c",
							db->esc1Buffer,
							0
						);

						if(mysqlPull(db, db->queryBuffer) != NULL) {
							if(db->replyBuffer[0] == 0) {
								if(thisLevel != PRIVILEGE_LEVEL_NONE && PRIVILEGE_LEVEL_DEFAULT >= thisLevel) {
									db->e = 0;
								}
							}
							else {
								if(thisLevel != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) >= thisLevel) {
									db->e = 0;
								}
							}

							mysqlFree(db);
						}
					}
					else {
						mysqlEscape(db, db->esc2Buffer, thisDomain);

						// Check if requested domain has explicit permissions
						snprintf(
							db->queryBuffer,
							db->u,
							"SELECT MAX(" TABLECOL_USER_PERM ") AS " TABLECOL_USER_PERM " FROM " TABLE_PERM_NODES " WHERE " TABLECOL_USER_USID " IN (SELECT DISTINCT " TABLECOL_USER_ID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s') AND " TABLECOL_USER_DOMAIN " = '%s'%c",
							db->esc1Buffer,
							db->esc2Buffer,
							0
						);

						if(mysqlPull(db, db->queryBuffer) != NULL) {
							if(db->replyBuffer[0] == 0) {
								mysqlFree(db);

								// Check for explicit permissions
								snprintf(
									db->queryBuffer,
									db->u,
									"SELECT MAX(" TABLECOL_USER_PERM ") AS " TABLECOL_USER_PERM " FROM " TABLE_PERM_NODES " WHERE " TABLECOL_USER_USID " IN (SELECT DISTINCT " TABLECOL_USER_ID " FROM " TABLE_USERS " WHERE " TABLECOL_USER_UID " = '%s') AND " TABLECOL_USER_DOMAIN " = ''%c",
									db->esc1Buffer,
									0
								);

								if(mysqlPull(db, db->queryBuffer) != NULL) {
									if(db->replyBuffer[0] == 0) {
										if(thisLevel != PRIVILEGE_LEVEL_NONE && PRIVILEGE_LEVEL_DEFAULT >= thisLevel) {
											db->e = 0;
										}
									}
									else {
										if(thisLevel != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) >= thisLevel) {
											db->e = 0;
										}
									}

									mysqlFree(db);
								}
							}
							else {
								if(thisLevel != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) != PRIVILEGE_LEVEL_NONE && (unsigned long long) atoll(db->replyBuffer) >= thisLevel) {
									db->e = 0;
								}

								mysqlFree(db);
							}
						}
					}

					memset(db->esc2Buffer, 0, (thisDomainLength * 2) + 1);

					free(db->esc2Buffer);
				}

				memset(db->esc1Buffer, 0, (thisUidLength * 2) + 1);

				free(db->esc1Buffer);
			}

			memset(db->queryBuffer, 0, db->u);

			free(db->queryBuffer);
		}

		mysqlDisconnect(db);
	}

	return(db->e);
}
