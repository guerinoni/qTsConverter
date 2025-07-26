#!/bin/bash

# $1 is source folder with ts-files - here xlsx files will be output, too
# $2 is folder of qTsConverter

exe=$2"qTsConverter"

while IFS= read -r -d '' file; do
      echo "Convert '$file' $file.xlsx"
     "$exe" "$file" "$file.xlsx"
done < <(find $1 -type f -name "*.ts" -print0)
