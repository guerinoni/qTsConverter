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
You can check te version with `qTsConverter --version`.

Perform a conversion:
```bash
qTsConverter ../../tests/files/scenario_multiline.ts ./lol.csv
```


## Build

Simple build
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Simple build only CLI
```bash
mkdir build
cd build
cmake .. -DBUILD_CLI=ON
cmake --build .
```

Compile from source and install:

```
$ git clone --recursive https://github.com/guerinoni/qTsConverter.git
$ cd scripts/
$ ./compile.sh
$ cd ../../build
$ sudo make install
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
