# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path
lib=/Users/Yan/Project/just-do-it/Finished/malloc/build/liballocator.so

echo "Unix Utilities" \
    "Runs 'ls /'  with custom memory allocator"
date
if [ -e $lib ]
then
    echo "<------expected result------>"
    ls /
    echo "<------actual result-------->"
    DYLD_INSERT_LIBRARIES=$lib ls /
else
    echo "liballocator.so doesn't exist!!"
fi