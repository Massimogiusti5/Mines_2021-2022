#!/usr/bin/env bash

filename=${1}

if [ -z ${filename} ]; then
    echo "Error: Did not pass filename"
    exit 1
fi

chars=$(wc -m ${filename} | tr -d [a-z] | tr -d [:blank:] | tr -d [A-Z] | tr -d [.]])
echo "This file has ${chars} characters in it."

chars=$(cat ${filename} | tr -d ['\n'] | wc -m | tr -d [:blank:])
echo "This file has ${chars} characters not counting the newline."

chars=$(cat ${filename} | sort | uniq -c | head -1 | tr -d [:blank:])
echo "This file has ${chars} empty lines."

chars=$(cat ${filename} | tr -d [:blank:] | tr -d ['\n'] | wc -m | tr -d [:blank:])
echo "This file has ${chars} alphanumeric characters"