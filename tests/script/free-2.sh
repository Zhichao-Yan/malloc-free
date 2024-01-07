# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Test free() functionality" \
    "Makes a large amount of random allocations and frees them"
date

if [ -e $lib ]
then
    ./build/free
else
    echo "liballocator.so doesn't exist!!"
fi