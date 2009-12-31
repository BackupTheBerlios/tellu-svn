#!/bin/sh

VERSION="3.0.0"

if [ ! "$1" ]; then
	echo "Usage: $0 noarch | unix | windows"

	exit 1
fi

DIR="tellu-agent-$1-$VERSION"
TAR="tellu-agent-$1-$VERSION.tar"
ZIP="tellu-agent-$1-$VERSION.tar.gz"

if [ -e $ZIP ]; then
	rm -f $ZIP || exit 1
fi

echo "Cleaning garbage..."

for a in $DIR; do
	( cd "$a" && rm -f Makefile ; rm -rf autom4te.cache ; autoconf )
done

echo "Creating tarball..."

find $DIR/ | egrep 'AUTHOR$|INSTALL$|LICENSE$|README$|configure$|install-sh$|\.c$|\.d$|\.h$|\.in$|\.conf$|\.pl$|\.rc$|\.ico$|\.sln$|\.vcproj$|\.exe$' | while read a; do
	tar -rf $TAR "$a" || exit 1
done

echo "Compressing tarball..."

gzip -9 $TAR || exit 1

echo "Done."

exit 0
