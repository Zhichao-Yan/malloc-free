# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Pages Allocated"
date

if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/total_pages_allocated
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/total_pages_allocated
fi