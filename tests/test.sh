#!/bin/bash

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
lib=/Users/Yan/Project/just-do-it/Finished/malloc/build/liballocator.so
os_type=$(uname)
case $os_type in
    # macOS
    Darwin*)
        export DYLD_INSERT_LIBRARIES=$lib ;;
    # Linux
    Linux*)
        export LD_PRLOAD=$lib ;;
    *)
        echo "Unsupported operating system: $os_type"
        exit 1 ;;
esac

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
    else
        echo $case"  [ OK ]"
    fi
done
