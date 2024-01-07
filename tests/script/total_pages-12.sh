# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Pages Allocated"
date

if [ -e $lib ]
then
    ./build/total_pages_allocated
else
    echo "liballocator.so doesn't exist!!"
fi