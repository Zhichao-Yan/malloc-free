# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Basic First Fit"
date

if [ -e $lib ]
then
    export ALLOCATOR_ALGORITHM=worst_fit
    ./build/basic0
else
    echo "liballocator.so doesn't exist!!"
fi