#!/bin/sh

[ -z "$1" ] && echo "please provide a version tag" && exit

echo "version tag: $1"
RELEASEDIR="qTsConverter_debian_$1"

# cleanup
rm -r ../../$RELEASEDIR ../../$RELEASEDIR.deb

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
cd DEBIAN
echo "Package: qTsConverter" > control
echo "Version: $1" >> control
echo "Section: custom" >> control
echo "Priority: optional" >> control
echo "Architecture: x86-64" >> control
echo "Essential: no" >> control
echo "Maintainer: Stivvo" >> control
echo "Description: A simple tool to convert qt translation file (ts) to other format (xlsx / csv) and vice versa" >> control
cd ../..
dpkg-deb --build "$RELEASEDIR"
