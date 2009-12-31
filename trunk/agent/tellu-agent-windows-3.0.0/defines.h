#define APPLICATION_NAME "tellu"
#define APPLICATION_VERSION "3.0.0-windows"

#define CONFIG_DEFAULT_FILE "tellu.conf"

#define CONFIG_SPACE_SIZE 1024
#define CONFIG_STRING_SIZE 10240

#define CONFIG_TYPE_BOOLEAN 1
#define CONFIG_TYPE_INTEGER 2
#define CONFIG_TYPE_STRING 3

#define CONFIG_TYPE_BOOLEAN_NO 0
#define CONFIG_TYPE_BOOLEAN_YES 1

#define DATA_BLOCK_SIZE 1024
#define DATA_STRING_SIZE 256

#define DATA_ARRAYS_COUNT 18
#define DATA_POINTER_SIZE 8

#define DATA_COMPRESS_NONE 0
#define DATA_COMPRESS_JIP 1

#define DATA_PACKET_COLLECT "collection"
#define DATA_PACKET_REALTIME "realtime"

#define ERROR_NOERROR 1
#define ERROR_SLIGHT 2
#define ERROR_FATAL 3

#define ITEM_DELIMITER 27
#define ITEM_SEPARATOR 26
#define ITEM_SPLITTER '|'

#define JIP_CCBITS 14
#define JIP_MAXVAL (1 << JIP_CCBITS) - 1
#define JIP_MAXCOD JIP_MAXVAL - 1

#if JIP_CCBITS == 14
	#define JIP_TBSIZE 18041
#endif
#if JIP_CCBITS == 13
	#define JIP_TBSIZE 9029
#endif
#if JIP_CCBITS <= 12
	#define JIP_TBSIZE 5021
#endif

#define PACK_TYPE_MSI 100

#ifndef WINVER
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0400
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0200
#endif
