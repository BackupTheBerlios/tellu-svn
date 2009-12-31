#!/bin/sh

VERSION="3.0.0"

DIR="tellu-server-$VERSION"
TAR="tellu-server-$VERSION.tar"
ZIP="tellu-server-$VERSION.tar.gz"

if [ -e $ZIP ]; then
	rm -f $ZIP || exit 1
fi

echo "Cleaning garbage..."

for a in $DIR/telinfo $DIR/tellud $DIR/telmon $DIR/telmond $DIR/telskind; do
	( cd "$a" && rm -f Makefile ; rm -f defines.h ; rm -rf autom4te.cache ; autoconf )
done

echo "Creating tarball..."

find $DIR/ | egrep 'AUTHOR$|INSTALL$|LICENSE$|README$|configure$|install-sh$|\.c$|\.d$|\.h$|\.in$|\.conf$|\.sql$' | while read a; do
	tar -rf $TAR "$a" || exit 1
done

echo "Compressing tarball..."

gzip -9 $TAR || exit 1

echo "Done."

exit 0
