#!/bin/bash

# $1 is source folder with xlsx-files - here ts files will be output, too
# $2 is folder of qTsConverter

exe=$2"qTsConverter"

while IFS= read -r -d '' file; do
      echo "Convert '$file' $file.ts"
     "$exe" "$file" "$file.ts"
done < <(find $1 -type f -name "*.xlsx" -print0)
