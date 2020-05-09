# qTsConverter
This tool was born to convert `.ts` file of Qt translation in other format more editable using an office suite.
Now it supports `.ts` -> `.csv/.xlsx` and vice versa. You can also do conversion between `.csv` and `.xlsx` keeping in mind the use of header tags used to retrieve the right information of translation.

[![Build Status](https://travis-ci.org/guerinoni/qt-ts-csv.svg?branch=master)](https://travis-ci.org/guerinoni/qt-ts-csv)

## Build
```
> mkdir build
> cd build
> cmake .. -DCMAKE_PREFIX_PATH=/opt/qt512/
> make
```

## Contributing
[guidelines](./doc/CONTRIBUTING.md)

## Usage

### To generate output.csv  
![example conversion ts -> csv](./doc/Screenshot.png)  

