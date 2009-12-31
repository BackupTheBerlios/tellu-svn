#!/bin/sh

for i in telinfo tellud telmon telmond telskind; do
	(cd $i && ./configure \
		--prefix=/usr/local \
		--with-mysql=/opt/mysql \
		--with-openldap=/opt/openldap \
		--with-motif=/opt/libmotif \
		--with-x11=/usr/X11 && \
		make clean && make ) || exit 1 ;
done

exit 0
