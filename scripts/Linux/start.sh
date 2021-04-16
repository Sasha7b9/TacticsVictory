#!/usr/bin/env bash

# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
function ShowHint {
    echo "    Usage:"
    echo "          ./stop.sh [ master | uploader | all ]"
}

function Start {
    if [ $1 -eq 1 ]
    then
        if [[ $(pidof $2) != "" ]]
        then
            kill -9 $(pidof $2)
        fi
        ./$2 &
    fi
}

# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set -e              # Немедленно выйти, если команда завершается с ненулевым статусом

startMaster=0
startUploader=0


if [[ $# -ne 1 ]]
then
    ShowHint
    exit
fi

case $1 in
    "master"   ) startMaster=1   ;;

    "uploader" ) startUploader=1 ;;

    "all"      ) startMaster=1
                 startUploader=1 ;;

    *          ) ShowHint
                 exit           ;;
esac

dir=$PWD

cd ../../out/release

Start $startUploader Uploader
Start $startMaster Master

cd $dir
