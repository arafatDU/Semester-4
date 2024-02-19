#!/bin/bash

path=$1

if [[ ! -d "$path" ]]; then
	echo "This is not a directory"
	exit 1
fi

# all_files=$(find "$path" -type f -name "*.c")
# echo "$all_files"



echo "filename     size     lineOfCode"
echo "#################################"
for file in $(find $path -type f -name "*.c" -or -name "*.cpp") ; do
	filename=$(basename -- "$file")
	size=$(stat --format=%s "$file")
	lineOfCode=$(wc -l < "$file")

	echo "$filename     $size Bytes     $lineOfCode"
done
