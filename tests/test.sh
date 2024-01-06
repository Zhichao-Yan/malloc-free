#!/bin/bash

# first clean, then compile all files

cases=""
# echo $@
if [ $# -eq 0 ]
then
    cases=$(ls -1 ./script/*-*.sh)
else
    for num in "$@"
    do
        test_id=$(printf "%d" $num)
        file=$(ls -1 ./script/*-$test_id.sh)
        cases=$cases$file$'\n'
    done
fi
# echo $cases

echo "Building test programs...."
make clean all -s

for case in $cases
do
    if [ -x $case ]
    then 
        ${case}
    else
        chmod +x "$case"
        ${case}
    fi
    if [ $? -ne 0 ]
    then
        echo $case"  [ FAILED ]"
    # else
    #     #echo $case"  [ OK ]"
    fi
done
