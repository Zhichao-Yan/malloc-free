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

echo "<------expected result------>"
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ls /
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ls /
fi