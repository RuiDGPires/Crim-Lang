#!/bin/bash

RED="\033[1;31m"
GREEN="\033[1;32m"
NC="\033[0m"


# Check if binary file does exist
if [[ ! -f $1 ]]; then
    echo "Error: runTests.sh: Binary file does not exist: $1"
    exit 0
fi

files=$(ls inputs)

for file in $files; do
    echo "Testing ${file}"

    ./${1} inputs/${file} -t s > outputs/${file%.*}-log.txt

    if [[ $? -eq 1 ]]
    then
        echo "Test failed: ${file}, check log"
    else
        rm outputs/${file%.*}-log.txt
    fi
    
done