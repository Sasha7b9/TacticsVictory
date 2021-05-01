#!/usr/bin/env bash


function Build {
    ./stop.sh all

    echo
    echo Start build ...

    time ./assembly.sh build release 1>good.build  2>fail.build
    FILENAME=fail.build
    FILESIZE=$(stat -c%s "$FILENAME")

    if [ $FILESIZE != "0" ]
    then
        ./send_fail.sh
        rm fail.build
    fi

    if [ $FILESIZE == "0" ]
    then
        ./send_good.sh
        rm good.build
    fi

    ./start.sh all    
}

echo .

Build

while true
do
    git pull > out.txt
    FILENAME=out.txt
    FILESIZE=$(stat -c%s "$FILENAME")
    if [ $FILESIZE != "20" ]            #  20 - size string "Already up to date."
    then
        Build
    fi
    sleep 1
done
