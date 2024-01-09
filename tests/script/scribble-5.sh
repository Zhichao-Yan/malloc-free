# !/bin/bash

script_name=$(basename $0)
extracted_number=${script_name##*-}
id=${extracted_number%.sh}
filename=$(printf "output-%d.txt" $id)
path=./output/$filename
exec 1>$path

echo "Memory Scribbling"
date

expected=$(cat <<EOM
Printing uninitialized variables:
-1431655766
-1431655766
-1431655766
12297829382473034410
aaaaaaaa
aaaaaaaaaaaaaaaa
Totalling up uninitialized arrays:
850000
calloc should still zero out the memory:
0
EOM
)

echo "<------expected result------>"
echo $expected
echo "<------actual result-------->"
if [[ $os_type == Darwin* ]]
then
    DYLD_INSERT_LIBRARIES=$lib ./build/scribble
elif [[ $os_type == Linux* ]]
then
    LD_PRELOAD=$lib ./build/scribble
fi