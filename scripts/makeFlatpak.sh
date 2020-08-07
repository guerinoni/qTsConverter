#!/bin/sh

cd ../../
flatpak-builder --force-clean qTsConverter_flatpak qTsConverter/scripts/org.guerinoni.qTsConverter.yml
