#!/bin/sh

for i in tellu-agent-unix-3.0.0; do
	(cd $i && ./configure \
		--prefix=/usr/local \
		--with-dbus=/opt/libdbus \
		--with-hal=/opt/libhal && \
		make clean && make ) || exit 1 ;
done

exit 0
