# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "print_memory() function"
date

if [ -e $lib ]
then
    ./build/print_test
else
    echo "liballocator.so doesn't exist!!"
fi