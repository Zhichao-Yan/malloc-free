#!/bin/bash

# first clean, then compile all files
#make clean all
exec 1>output.txt
lib=../build/liballocator.so

echo "Unix Utilities" \
    "Runs 'ls /'  with custom memory allocator"

if [ -e $lib ]
then
    expected=$(ls /)
    echo "expected result:"
    echo $expected
    actual=$(LD_PRELOAD=$lib ls /)
    echo "actual result:"
    echo $actual
fi