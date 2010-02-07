#include <sys/types.h>
#include <sys/stat.h>

// cmdline.c
extern void cmdRead(char **, int);

// config.c
extern int configRead(char *);
extern void *configFetch(char *, int *);
extern void configUpdateBoolean(char *, char *);
extern void configUpdateInteger(char *, char *);
extern void configUpdateString(char *, char *);
extern int configChangeRoot(char *);
extern int configCloseInput(void);
extern int configSetLocale(char *);
extern void configSetUmask(mode_t);

// messages.c
extern void infoMessage(int, char *);
extern void warningMessage(int, char *);

// shm.c
extern void shmInfo(void);
extern void shmTell(unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long, unsigned long long *, char *, char *, char *);
