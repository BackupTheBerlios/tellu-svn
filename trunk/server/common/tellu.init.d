#!/bin/sh
# chkconfig: 2345 90 10

### BEGIN INIT INFO
# Provides:          tellud telmond telskind
# Required-Start:    $network $mysql $syslog
# Required-Stop:     $network $mysql $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      1 6
# Description:       Control tellu server
# Short-Description: Control tellu server
### END INIT INFO

PATH="/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/opt/bin:/opt/sbin"

TELLUBIN="tellud"
TELMONBIN="telmond"
TELSKINBIN="telskind"

TELLUSHM="/var/run/tellud.shm"
TELLUPID="/var/run/tellud.pid"
TELMONPID="/var/run/telmond.pid"
TELSKINPID="/var/run/telskind.pid"

case "$1" in
	start)
		$TELLUBIN

		sleep 1

		$TELMONBIN

		sleep 1

		$TELSKINBIN

		;;
	stop)
		seq 1 65535 | while read a; do
			if [ -e "$TELSKINPID.$a" ]; then
				kill `cat $TELSKINPID.$a 2>/dev/null`
			fi

			if [ -e "$TELMONPID.$a" ]; then
				kill `cat $TELMONPID.$a 2>/dev/null`
			fi

			if [ -e "$TELLUPID.$a" ]; then
				kill `cat $TELLUPID.$a 2>/dev/null`
			fi
		done

		ipcrm -m `cat $TELLUSHM 2>/dev/null` >/dev/null 2>&1

		rm -f $TELLUSHM 2>/dev/null

		;;
	restart)
		seq 1 65535 | while read a; do
			if [ -e "$TELSKINPID.$a" ]; then
				kill `cat $TELSKINPID.$a 2>/dev/null`
			fi

			if [ -e "$TELMONPID.$a" ]; then
				kill `cat $TELMONPID.$a 2>/dev/null`
			fi

			if [ -e "$TELLUPID.$a" ]; then
				kill `cat $TELLUPID.$a 2>/dev/null`
			fi
		done

		ipcrm -m `cat $TELLUSHM 2>/dev/null` >/dev/null 2>&1

		rm -f $TELLUSHM 2>/dev/null

		sleep 1

		$TELLUBIN

		sleep 1

		$TELMONBIN

		sleep 1

		$TELSKINBIN

		;;
	status)
		seq 1 65535 | while read a; do
			if [ -e "$TELLUPID.$a" ]; then
				echo "tellud running as pid `cat $TELLUPID.$a 2>/dev/null`, listening port $a"
			fi

			if [ -e "$TELMONPID.$a" ]; then
				echo "telmond running as pid `cat $TELMONPID.$a 2>/dev/null`, listening port $a"
			fi

			if [ -e "$TELSKINPID.$a" ]; then
				echo "telskind running as pid `cat $TELSKINPID.$a 2>/dev/null`, listening port $a"
			fi
		done

		;;
	*)
		echo "Usage: $0 {start|stop|restart|status}"

		;;
esac

exit 0
