# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path
lib=/Users/Yan/Project/just-do-it/Finished/malloc/build/liballocator.so

echo "Basic First Fit"
date

if [ -e $lib ]
then
    export ALLOCATOR_ALGORITHM=first_fit
    DYLD_INSERT_LIBRARIES=$lib ./build/basic1
else
    echo "liballocator.so doesn't exist!!"
fi