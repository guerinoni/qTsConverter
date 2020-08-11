#!/bin/sh

[ -z "$1" ] && echo "please provide a version tag" && exit

echo "version tag: $1"
RELEASEDIR="qTsConverter_debian_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir -p usr/bin
cp ../build/src/qTsConverter usr/bin/qTsConverter

# copying documentation and license
mkdir -p usr/share/doc/qTsConverter
cp ../qTsConverter/README.md usr/share/doc/qTsConverter/README.md
mkdir -p usr/share/licenses/qTsConverter
cp ../qTsConverter/LICENSE usr/share/licenses/qTsConverter/LICENSE

# desktop and icon
mkdir -p usr/share/pixmaps/
cp ../qTsConverter/src/qml/assets/logos/profile.png usr/share/pixmaps/org.guerinoni.qTsConverter.png
cp ../qTsConverter/src/qml/assets/logos/vector/isolated-layout.svg usr/share/pixmaps/org.guerinoni.qTsConverter.svg
mkdir -p usr/share/applications
cp ../qTsConverter/data/qTsConverter.desktop usr/share/applications/qTsConverter.desktop

# dependency
mkdir -p usr/lib
cp ../build/3rd-party/qtxlsx/libQtXlsxWriter.so usr/lib/libQtXlsxWriter.so

# debian stff
mkdir DEBIAN
echo "Package: qTsConverter" > DEBIAN/control
echo "Version: $$1" >> DEBIAN/control
echo "Section: custom" >> DEBIAN/control
echo "Priority: optional" >> DEBIAN/control
echo "Architecture: all" >> DEBIAN/control
echo "Essential: no" >> DEBIAN/control
echo "Maintainer: Stivvo" >> DEBIAN/control
echo "Description: A simple tool to convert qt translation file (ts) to other format (xlsx / csv) and vice versa" >> DEBIAN/control

cd ..
dpkg-deb --build "$RELEASEDIR"
