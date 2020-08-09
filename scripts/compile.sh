#!/bin/bash

NPROC="$(grep -E -c "^processor" /proc/cpuinfo)"

mkdir ../../build
cd ../../build

cmake -DCMAKE_BUILD_TYPE=Release -B. -S../qTsConverter
make "-j$NPROC"
