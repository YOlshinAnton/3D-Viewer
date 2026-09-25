#!/bin/bash

if [ -d $1 ];
then
	FILES=$(find $1 -type f \( -name '*.cpp' -or -name '*.cc' -or -name '*.h' \) -and ! -name '*gif*')
else
	echo "USAGE: ./format.sh <dir_to_format>"
fi

for f in $FILES
do
	eval clang-format -style=Google $2 $f
	echo "$f formatted"
done

