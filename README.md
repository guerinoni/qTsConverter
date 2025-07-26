# qTsConverter

![linux](https://github.com/guerinoni/qTsConverter/workflows/linux/badge.svg?branch=master)
![macos](https://github.com/guerinoni/qTsConverter/workflows/macos/badge.svg?branch=master)
![w10](https://github.com/guerinoni/qTsConverter/workflows/w10/badge.svg)
![GitHub](https://img.shields.io/github/license/guerinoni/qTsConverter)
![GitHub stars](https://img.shields.io/github/stars/guerinoni/qTsConverter)

This tool was born to convert `.ts` file of Qt translation in other format more
editable using an office suite.

## Features

- conversion `.ts` -> `.csv` (and vice-versa)
- conversion `.ts` -> `.xlsx` (and vice-versa)
- automatically detect conversion type
- convert multiple file in input

## Usage (GUI version)

- browse input filename (or multiple input)
- choose output filename (or folder in case of multi input)
- click convert button

### To generate output.csv

![example conversion ts -> csv](./doc/Screenshot.png)

## Usage (CLI version)

You can check the version with `qTsConverter --version`.

Perform a conversion:

```bash
qTsConverter ../../tests/files/scenario_multiline.ts ./lol.csv
```

To create an excelfile without version information / without file locations,
the cli can be invoked with two command line switches.

```bash
qTsConverter --no-version --no-location ../../tests/files/scenario_multiline.ts ./lol.xlsx
```

To create an excel file for each ts file in a folder,
a bash script can be invoked.

```bash
./scripts/ts-to-xlsx.sh /path/to/ts-files ./build/src/
```

To create a ts file for each excel file in a folder,
a bash script can be invoked.

```bash
./scripts/xlsx-to-ts.sh /path/to/xlsx-files ./build/src/
```

## Linux Build

### Prerequisites

```bash
sudo apt update
sudo apt install qtbase5-dev qtbase5-dev-tools qt5-qmake cmake
sudo apt install qml-module-qtquick-controls qtdeclarative5-dev
sudo apt install qtbase5-private-dev
```

### Simple build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Simple build only CLI

```bash
mkdir build
cd build
cmake -DBUILD_CLI:BOOL=ON -DCMAKE_PREFIX_PATH=/home/guerra/Qt/5.15.2/gcc_64/ ..
cmake --build .
```

or alternatively use script

```bash
cd scripts
./compile-cli.sh
```

### Linux: Compile from source and install

```bash
git clone --recursive https://github.com/guerinoni/qTsConverter.git
cd scripts/
./compile.sh
cd ../../build
sudo make install
```

If qTsConverter was installed with ``-DCMAKE_INSTALL_PREFIX=/usr/local`` (like
``compile.sh`` does) the shell variable ``LD_LIBRARY_PATH`` should contain
``/usr/local/lib`` and ``/usr/local/bin`` should be in the ``PATH`` variable.
This allows to locate libraries that qTsConverter depends on and run it from any
path.

To be able to open the output file and the output directory, ``xdg-mime`` must
be set for the following filetypes:

- ``application/excel``
- ``application/csv``
- ``text/csv``
- ``text/xml``

For example:

```bash
xdg-mime default libreoffice-calc.desktop application/csv
```

## Windows Build

### Windows: Compile from source and install

```pwsh
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build_win_release
cmake --build build_win_release --parallel --config Release
```

As Administrator

```pwsh
cmake --install build_win_release
```

##

Example of supported TS file and its features (for reference see <https://doc.qt.io/qt-6/linguist-ts-file-format.html>):

```xml
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de" sourcelanguage="en">
<context>
    <name>context a</name>
    <message id="my-id">
        <location filename="../dir/file.ui" line="26"/>
        <location filename="../dir/file.iu" line="+36"/>
        <location filename="../dir/file.ii" line="-46"/>
        <source>source example</source>
        <comment>comment example</comment>
        <extracomment>extra comment example</extracomment>
        <translatorcomment>translator comment example</translatorcomment>
        <translation>translation example</translation>
        <translation type="unfinished"></translation>
        <translation type="vanished">example 1: type is optional and maximum one type</translation>
        <translation type="obsolete">example 2</translation>
    </message>
</context>
</TS>
```
