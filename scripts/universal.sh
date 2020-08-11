#!/bin/sh

[ -z "$1" ] && echo "please provide a version tag" && exit

echo "version tag: $1"
# uncompressed universal package directory
RELEASEDIR="qTsConverter_universal_$1"
# project name
N="qTsConverter"
# install command
C="install -v -Dm"
# path for repo assets
ASSET="$N/src/qml/assets/logos"
# installation prefix
FIX="/usr/local"
# icons install path
ICON="$FIX/share/icons/hicolor/512x512/apps/org.guerinoni.$N"

rm -r ../../$RELEASEDIR
rm ../../"$RELEASEDIR.zip"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir -p build/src
cp ../build/src/$N build/src/$N

# copying scripts
mkdir -p $N/scripts
cp ../$N/scripts/uninstall.sh uninstall.sh

# copying documentation, license
cp ../$N/README.md $N/README.md
cp ../$N/LICENSE $N/LICENSE

# copying desktop
mkdir -p $N/data
cp ../$N/data/$N.desktop $N/data/$N.desktop

# copying icons
mkdir -p $ASSET/vector
cp ../$ASSET/profile.png $ASSET/profile.png
cp ../$ASSET/vector/isolated-layout.svg $ASSET/vector/isolated-layout.svg

# copying dependencies
mkdir -p build/3rd-party/qtxlsx
cp ../build/3rd-party/qtxlsx/libQtXlsxWriter*.so build/3rd-party/qtxlsx/

# creating install.sh that runs wayPreview/scripts/install.sh
echo "#!/bin/sh" > install.sh
echo "${C}755 build/src/$N $FIX/bin/$N" >> install.sh
echo "${C}755 build/3rd-party/qtxlsx/libQtXlsxWriter*.so $FIX/lib/" >> install.sh
echo "${C}644 $N/LICENSE $FIX/share/licenses/$N/LICENSE" >> install.sh
echo "${C}644 $N/README.md $FIX/share/doc/$N/README.md" >> install.sh
echo "${C}644 $N/data/$N.desktop $FIX/share/applications/$N.desktop" >> install.sh
echo "${C}644 $ASSET/vector/isolated-layout.svg $ICON.svg" >> install.sh
echo "${C}644 $ASSET/profile.png $ICON.png" >> install.sh
chmod +x install.sh

cd ..
echo "universal package created: $RELEASEDIR.zip"
zip -r "$RELEASEDIR.zip" "$RELEASEDIR"
