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
lib=../build/liballocator.so
os_type=$(uname)
case $os_type in
    # macOS
    Darwin*)
        export DYLD_INSERT_LIBRARIES=$lib ;;
    # Linux
    Linux*)
        export LD_PRELOAD=$lib ;;
    *)
        echo "Unsupported operating system: $os_type"
        exit 1 ;;
esac

echo "Start testing....."
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
    else
        echo $case"  [ OK ]"
    fi
done
