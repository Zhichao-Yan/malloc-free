# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Test functionality of realloc()"
date

if [ -e $lib ]
then
   ./build/realloc
else
    echo "liballocator.so doesn't exist!!"
fi