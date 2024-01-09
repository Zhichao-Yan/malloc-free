# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "print_memory() function"
date
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/print_test
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/print_test
fi
