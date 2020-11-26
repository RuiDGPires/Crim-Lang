#!/bin/bash

RED="\033[1;31m"
GREEN="\033[1;32m"
NC="\033[0m"


# Check if binary file does exist
if [[ ! -f $1 ]]; then
    echo "Error: runTests.sh: Binary file does not exist: $1"
    exit 0
fi

# Check if Input folder does exist
if [[ ! -d "$2" ]]; then
    echo "Error: runTests.sh: Directory does not exist: $2"
    exit 0
fi

# If output folder does not exist, create one
if [[ ! -d "$3" ]]
then
    mkdir $3
fi

files=$(ls ${2})

for file in $files; do
    echo "Testing ${file}"

    ./${1} ${2}/${file} -t s > ${3}/${file%.*}-log.txt

    if [[ $? -eq 1 ]]
    then
        echo "Test failed: ${file}"
        echo "Check log"
        exit 0
    fi
    rm ${3}/${file%.*}-log.txt
done