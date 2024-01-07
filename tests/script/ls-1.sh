# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Unix Utilities" \
    "Runs 'ls /'  with custom memory allocator"
date
if [ -e $lib ]
then
    echo "<------expected result------>"
    ls /
else
    echo "liballocator.so doesn't exist!!"
fi