#!/bin/bash

NPROC="$(grep -E -c "^processor" /proc/cpuinfo)"

mkdir ../../build
cd ../../build

cmake -B. -S../qTsConverter
make "-j$NPROC"
