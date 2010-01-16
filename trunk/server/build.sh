#!/bin/sh

for i in telinfo tellud telmon telmond telskind; do
	(cd $i && ./configure \
		--prefix=/usr/local \
		--with-mysql=/usr \
		--with-openldap=/usr \
		--with-motif=/usr \
		--with-x11=/usr && \
		make clean && make ) || exit 1 ;
done

exit 0
