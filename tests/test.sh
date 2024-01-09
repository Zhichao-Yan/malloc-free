#!/bin/bash
# test/build/ is a directory where you can find your executable of test source file
echo "Building test programs...."

# test/output/ is a directory where you can find your output file
# test/build/ is a directory where you can find your test program
[ -d "./build" ] || mkdir ./build
[ -d "./output" ] || mkdir ./output

# compile test source file
make clean all -s

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
#script_dir=$(dirname $(readlink -f $0))
# 获取脚本所在目录的绝对路径
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export lib=$script_dir/../build/liballocator.so

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
