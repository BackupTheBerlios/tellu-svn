#define APPLICATION_NAME "tellu"
#define APPLICATION_VERSION "3.0.0-unix"

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

#define DIST_GENERAL "/etc/lsb-release"
#define DIST_DEBIAN1 "/etc/debian_release"
#define DIST_DEBIAN2 "/etc/debian_version"
#define DIST_FEDORA "/etc/fedora-release"
#define DIST_GENTOO "/etc/gentoo-release"
#define DIST_MANDRAKE "/etc/mandrake-release"
#define DIST_REDHAT1 "/etc/redhat-release"
#define DIST_REDHAT2 "/etc/redhat_version"
#define DIST_SLACKWARE1 "/etc/slackware-release"
#define DIST_SLACKWARE2 "/etc/slackware-version"
#define DIST_SUNJDS "/etc/sun-release"
#define DIST_SUSE "/etc/SUSE-release"
#define DIST_UNITED "/etc/UnitedLinux-release"
#define DIST_YELLOWDOG "/etc/yellowdog-release"

#define DIST_NAME_DEBIAN1 "Debian release"
#define DIST_NAME_DEBIAN2 "Debian version"
#define DIST_NAME_FEDORA "Fedora release"
#define DIST_NAME_GENTOO "Gentoo release"
#define DIST_NAME_MANDRAKE "Mandrake release"
#define DIST_NAME_REDHAT1 "Red Hat release"
#define DIST_NAME_REDHAT2 "Red Hat version"
#define DIST_NAME_SLACKWARE1 "Slackware release"
#define DIST_NAME_SLACKWARE2 "Slackware version"
#define DIST_NAME_SUNJDS "Sun JDS release"
#define DIST_NAME_SUSE "Novell SuSE release"
#define DIST_NAME_UNITED "United Linux release"
#define DIST_NAME_YELLOWDOG "Yellow Dog release"

#define DIST_LSB_ID "DISTRIB_ID"
#define DIST_LSB_RELEASE "DISTRIB_RELEASE"
#define DIST_LSB_CODENAME "DISTRIB_CODENAME"
#define DIST_LSB_DESCRIPTION "DISTRIB_DESCRIPTION"

#define DISK_GENERAL "/etc/mtab"

#define CPU_GENERAL "/proc/cpuinfo"

#define CPU_PHYS_ID "physical id"
#define CPU_CORE_ID "core id"
#define CPU_CORES "cpu cores"
#define CPU_SIBLINGS "siblings"
#define CPU_MHZ "cpu MHz"
#define CPU_CACHE "cache size"
#define CPU_MIPS "bogomips"

#define HAL_ACADAPTER "ac_adapter"
#define HAL_BATTERY "battery"
#define HAL_BLUETOOTHACL "bluetooth_acl"
#define HAL_BLUETOOTHHCI "bluetooth_hci"
#define HAL_BLUETOOTHSCO "bluetooth_sco"
#define HAL_BUTTON "button"
#define HAL_CAMERA "camera"
#define HAL_IDE "ide"
#define HAL_IDEHOST "ide_host"
#define HAL_IEEE1394 "ieee1394"
#define HAL_IEEE1394HOST "ieee1394_host"
#define HAL_INPUT "input"
#define HAL_INPUTJOYSTICK "input.joystick"
#define HAL_INPUTKEYBOARD "input.keyboard"
#define HAL_INPUTKEYMAP "input.keymap"
#define HAL_INPUTKEYPAD "input.keypad"
#define HAL_INPUTKEYS "input.keys"
#define HAL_INPUTMOUSE "input.mouse"
#define HAL_INPUTSWITCH "input.switch"
#define HAL_INPUTTABLET "input.tablet"
#define HAL_KILLSWITCH "killswitch"
#define HAL_LAPTOPPANEL "laptop_panel"
#define HAL_LIGHTSENSOR "light_sensor"
#define HAL_MMC "mmc"
#define HAL_MMCHOST "mmc_host"
#define HAL_NET "net"
#define HAL_NET80203 "net.80203"
#define HAL_NET80211 "net.80211"
#define HAL_NET80211CONTROL "net.80211control"
#define HAL_NETBLUETOOTH "net.bluetooth"
#define HAL_NETBRIDGE "net.bridge"
#define HAL_NETIRDA "net.irda"
#define HAL_NETLOOPBACK "net.loopback"
#define HAL_PCMCIASOCKET "pcmcia_socket"
#define HAL_PORTABLEAUDIOPLAYER "portable_audio_player"
#define HAL_POWERMANAGEMENT "power_management"
#define HAL_PRINTER "printer"
#define HAL_PROCESSOR "processor"
#define HAL_SCANNER "scanner"
#define HAL_SCSI "scsi"
#define HAL_SCSIHOST "scsi_host"
#define HAL_SERIAL "serial"
#define HAL_SOUND "sound"
#define HAL_STORAGE "storage"
#define HAL_SYSTEM "system"
#define HAL_TAPE "tape"
#define HAL_VIDEO4LINUX "video4linux"
#define HAL_VOLUME "volume"

#define LOAD_AVERAGE "/proc/loadavg"
#define LOAD_UPTIME "/proc/uptime"

#define MEM_GENERAL "/proc/meminfo"

#define MEM_RAM_TOTAL "MemTotal"
#define MEM_RAM_AVAIL "MemFree"
#define MEM_SWAP_TOTAL "SwapTotal"
#define MEM_SWAP_AVAIL "SwapFree"
#define MEM_BUFFERS "Buffers"
#define MEM_CACHED "Cached"

#define PACK_ENVS "WIDTH=1000"
#define PACK_TEMP "/tmp/tellu"

#define PACK_TABS_LINE 3

#define PACK_DPKG_1 PACK_ENVS " /usr/bin/dpkg-query -W -f='${Package}\t${Version}\t${Installed-Size}\t${Homepage}\n' 2>/dev/null"
#define PACK_DPKG_2 PACK_ENVS " dpkg-query -W -f='${Package}\t${Version}\t${Installed-Size}\t${Homepage}\n' 2>/dev/null"
#define PACK_RPM_1 PACK_ENVS " /usr/bin/rpm -qa --queryformat '%{NAME}\t%{VERSION}\t%{SIZE}\t%{URL}\n' 2>/dev/null"
#define PACK_RPM_2 PACK_ENVS " rpm -qa --queryformat '%{NAME}\t%{VERSION}\t%{SIZE}\t%{URL}\n' 2>/dev/null"
#define PACK_PKG_1 PACK_ENVS " pkg_info -a -I 2>/dev/null | cut -f 1 -d ' ' | while read a; do b=$(pkg_info -d $a 2>/dev/null | grep '^WWW:' | sed -e 's/^WWW://'); c=$(pkg_info -s $a 2>/dev/null | grep 'blocks)$' | sed -e 's/[^0-9].*$//'); echo -e \"$a\t\t$c\t$b\"; done"
#define PACK_PKG_2 PACK_ENVS " /usr/sbin/pkg_info -a -I 2>/dev/null | cut -f 1 -d ' ' | while read a; do b=$(/usr/sbin/pkg_info -d $a 2>/dev/null | grep '^WWW:' | sed -e 's/^WWW://'); c=$(/usr/sbin/pkg_info -s $a 2>/dev/null | grep 'blocks)$' | sed -e 's/[^0-9].*$//'); echo -e \"$a\t\t$c\t$b\"; done"

#define PACK_TYPE_DPKG 1
#define PACK_TYPE_RPM 2
#define PACK_TYPE_PKG 4

#define PROC_GENERAL "/proc"

#define PROC_KERNEL "kernel"

#define PROC_NAME "Name"
#define PROC_STATE "State"
#define PROC_PID "Pid"
#define PROC_PPID "PPid"
#define PROC_UID "Uid"
#define PROC_GID "Gid"
#define PROC_VMPEAK "VmPeak"
#define PROC_VMSIZE "VmSize"
#define PROC_VMHWM "VmHWM"
#define PROC_VMRSS "VmRSS"
#define PROC_VMDATA "VmData"
#define PROC_VMSTK "VmStk"
#define PROC_VMEXE "VmExe"
#define PROC_VMLIB "VmLib"
#define PROC_VMPTE "VmPTE"
#define PROC_THREADS "Threads"

#define PROC_IO_RCHAR "rchar"
#define PROC_IO_WCHAR "wchar"
#define PROC_IO_SYSCR "syscr"
#define PROC_IO_SYSCW "syscw"
#define PROC_IO_RBYTE "read_bytes"
#define PROC_IO_WBYTE "write_bytes"

#define SYS_SB_PRODUCT "system.board.product"
#define SYS_SB_VENDOR "system.board.vendor"
#define SYS_SB_VERSION "system.board.version"
#define SYS_SH_PRODUCT "system.hardware.product"
#define SYS_SH_VENDOR "system.hardware.vendor"
#define SYS_SH_VERSION "system.hardware.version"
