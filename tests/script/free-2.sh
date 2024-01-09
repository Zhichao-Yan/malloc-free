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

if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/free
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/free
fi