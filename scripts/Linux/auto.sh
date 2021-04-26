#!/usr/bin/env bash

while true
do
    git pull > out.txt
    FILENAME=out.txt
    FILESIZE=$(stat -c%s "$FILENAME")
    if [ $FILESIZE != "20" ]
    then
        rm fail.log
        time ./assembly.sh build all 2>> fail.build
        FILENAME=fail.build
        FILESIZE=$(stat -c%s "$FILENAME")
        if [ $FILESIZE != "0" ]
        then
            ./send_fail.sh
        fi
        rm good.log
        if [ $FILESIZE == "0" ]
        then
            time ./assembly.sh build all > good.build
            ./send_good.sh
        fi
    fi
    sleep 1
done
