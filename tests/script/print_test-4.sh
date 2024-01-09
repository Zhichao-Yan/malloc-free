# !/bin/bash
# Debug print statement
echo "LD_LIBRARY_PATH: $LD_LIBRARY_PATH"

echo "ldd output for ./build/print_test:"
ldd ./build/print_test

echo "Running ldconfig..."
ldconfig

echo "Current working directory: $(pwd)"
echo "Script directory: $(dirname $(readlink -f $0))"
echo "lib: $lib"
echo "os_type: $os_type"

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

