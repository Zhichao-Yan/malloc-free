# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Unix Utilities" \
    "Runs 'df' and 'w' with custom memory allocator"
date

echo "<------ df ------>"
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib df
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib df
fi

echo "<------ w ------>"
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib w
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib w
fi