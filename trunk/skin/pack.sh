#!/bin/sh

VERSION="3.0.0"

DIR="tellu-skin-$VERSION"
TAR="tellu-skin-$VERSION.tar"
ZIP="tellu-skin-$VERSION.tar.gz"

if [ -e $ZIP ]; then
	rm -f $ZIP || exit 1
fi

rm -rf /tmp/$DIR >/dev/null 2>&1
mkdir /tmp/$DIR && cp -a AUTHOR INSTALL LICENSE README cgi-bin files html templates install.sh /tmp/$DIR/

echo "Creating tarball..."

cd /tmp >/dev/null && tar -rf $TAR $DIR || exit 1

echo "Compressing tarball..."

gzip -9 $TAR || exit 1

cd - >/dev/null && mv -f /tmp/$ZIP .
rm -rf /tmp/$DIR >/dev/null 2>&1

echo "Done."

exit 0
