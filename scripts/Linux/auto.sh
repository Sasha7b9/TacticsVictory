#!/usr/bin/env bash

while true
do
    git pull > out.txt
    FILENAME=out.txt
    FILESIZE=$(stat -c%s "$FILENAME")
    if [ $FILESIZE != "20" ]
    then
        time ./assembly.sh build all > build.txt
        ./send.sh
    fi
    sleep 1
done
