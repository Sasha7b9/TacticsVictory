#!/usr/bin/env bash

while true
do
    git pull > out.txt
    FILENAME=out.txt
    FILESIZE=$(stat -c%s "$FILENAME")
    if [ $FILESIZE != "20" ]
    then
        rm build.log
        time ./assembly.sh build all 2>> build.log
        FILENAME=build.log
        FILESIZE=$(stat -c%s "$FILENAME")
        if [ $FILESIZE != "0" ]
        then
            ./send.sh
        fi
    fi
    sleep 1
done
