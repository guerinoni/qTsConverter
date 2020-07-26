#!/bin/bash

[ -z "$1" ] && echo "please provide a version tag" && exit

echo "version tag: $1"
RELEASEDIR="qTsConverter_universal_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir -p build/src
cp ../build/src/qTsConverter build/src/qTsConverter

# copying scripts
mkdir qTsConverter qTsConverter/scripts
cp ../qTsConverter/scripts/install.sh qTsConverter/scripts/install.sh
cp ../qTsConverter/scripts/uninstall.sh uninstall.sh

# copying documentation, license, desktop, icons
cp ../qTsConverter/README.md qTsConverter/README.md
cp ../qTsConverter/LICENSE qTsConverter/LICENSE
cp ../qTsConverter/scripts/qTsConverter.desktop qTsConverter/scripts/qTsConverter.desktop
mkdir -p qTsConverter/src/qml/assets/logos/vector
cp ../qTsConverter/src/qml/assets/logos/profile.png qTsConverter/src/qml/assets/logos/profile.png
cp ../qTsConverter/src/qml/assets/logos/vector/isolated-layout.svg qTsConverter/src/qml/assets/logos/vector/isolated-layout.svg

# creating install.sh that runs wayPreview/scripts/install.sh
echo "#!/bin/sh" > install.sh
echo "cd qTsConverter/scripts/" >> install.sh
echo "./install.sh" >> install.sh

cd ..
rm "$RELEASEDIR.zip"
zip -r "$RELEASEDIR.zip" "$RELEASEDIR"
echo "universal package created: $RELEASEDIR.zip"

