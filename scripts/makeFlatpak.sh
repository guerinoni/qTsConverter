#!/bin/sh

cd ../../
exec flatpak-builder -v -y --force-clean --install-deps-from=flathub --user --install flatpak_build qTsConverter/scripts/org.guerinoni.qTsConverter.yml
