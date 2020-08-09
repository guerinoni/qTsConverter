# qTsConverter
![linux](https://github.com/guerinoni/qTsConverter/workflows/linux/badge.svg?branch=master)
![macos](https://github.com/guerinoni/qTsConverter/workflows/macos/badge.svg?branch=master)
![w10](https://github.com/guerinoni/qTsConverter/workflows/w10/badge.svg)

[![Contact me on Codementor](https://www.codementor.io/m-badges/guerinonifederico/contact-me.svg)](https://www.codementor.io/@guerinonifederico?refer=badge)

This tool was born to convert `.ts` file of Qt translation in other format more
editable using an office suite.

## Features

- conversion `.ts` -> `.csv` (and vice-versa)
- conversion `.ts` -> `.xlsx` (and vice-versa)
- automatically detect conversion type

## Usage
- browse input filename
- choose output filename
- click convert button

### To generate output.csv
![example conversion ts -> csv](./doc/Screenshot.png)

## Build

Compile from source and install:

```
$ git clone https://github.com/guerinoni/qTsConverter.git
$ cd scripts/
$ ./compile.sh
$ sudo ./install.sh
$ cd ../../build
$ sudo make install
```

If qTsConverter was installed with ``-DCMAKE_INSTALL_PREFIX=/usr/local`` (like
``compile.sh`` does) the shell variable ``LD_LIBRARY_PATH`` should contain
``/usr/local/lib`` and ``/usr/local/bin`` should be in the ``PATH`` variable.
This allows to locate libraries that qTsConverter depends on and run it from any
path.
