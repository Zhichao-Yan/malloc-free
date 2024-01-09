# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "memory leak check after finish"
date

if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/leak_check
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/leak_check
fi