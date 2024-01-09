#!/bin/bash
# test/build/ is a directory where you can find your executable of test source file
echo "Building test programs...."
if [ ! -d "build" ]
then
    mkdir build
    make -s
else
    make clean all -s
fi

# test/output/ is a directory where you can find your output file
if [ ! -d "output" ]
then
    mkdir output
fi

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

# importing the lib(liballocator.so) before executing scripts
export lib=../build/liballocator.so
if [ ! -e $lib ]
then
    echo "liballocator.so doesn't exist!!"
    exit 1
fi

export os_type=$(uname)

echo "Start testing....."
for case in $cases
do
    if [ -x $case ]
    then 
        "$case"
    else
        chmod +x "$case"
        "$case"
    fi
    if [ $? -ne 0 ]
    then
        echo $case"  [ FAILED ]"
    else
        echo $case"  [ OK ]"
    fi
done
