# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Basic Best Fit"
date

export ALLOCATOR_ALGORITHM=best_fit
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/basic1
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/basic1
fi