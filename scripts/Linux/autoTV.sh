#!/usr/bin/env bash


function Build {
    ./stop.sh all

    echo
    echo Start build ...

    time ./assembly.sh full all 1>good.build  2>fail.build
    FILENAME=fail.build
    FILESIZE=$(stat -c%s "$FILENAME")

    if [ $FILESIZE != "0" ]
    then
        cat fail.build
        ./send_fail.sh
        cat fail.build
        rm fail.build
    fi

    if [ $FILESIZE == "0" ]
    then
        ./send_good.sh
        rm good.build
    fi

    ./start.sh all    
}

Build

while true
do
    git pull > out.txt
    FILENAME=out.txt
    FILESIZE=$(stat -c%s "$FILENAME")
    if [ $FILESIZE == "20" ]            #  20 - size string "Already up to date."
    then
        Build
    fi
    sleep 1
done
