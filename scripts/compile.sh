#!/bin/sh

NPROC="$(grep -E -c "^processor" /proc/cpuinfo)"

mkdir ../../build
cd ../../build

cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -B. -S../qTsConverter
make "-j$NPROC"
