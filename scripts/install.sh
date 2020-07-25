#!/bin/sh

install -Dm755 ../../build/src/qTsConverter /usr/bin/qTsConverter
install -Dm644 ../LICENSE /usr/share/licenses/qTsConverter
install -Dm644 ../README.md /usr/share/doc/qTsConverter
install -Dm644 ../qTsConverter.desktop /usr/share/applications/qTsConverter.desktop
install -Dm644 ../src/qml/assets/logos/vector/isolated-layout.svg /usr/share/applications/qTsConverter.svg
