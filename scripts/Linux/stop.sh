#!/usr/bin/env bash

# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
function ShowHint {
    echo "    Usage:"
    echo "          ./stop.sh [ master | uploader | all ]"
}

function Stop {
    if [ $1 -eq 1 ]
    then
        if [[ $(pidof $2) != "" ]]
        then
            kill -9 $(pidof $2)
        fi
    fi
}

# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set -e              # Немедленно выйти, если команда завершается с ненулевым статусом

stopMaster=0
stopUploader=0


if [[ $# -ne 1 ]]
then
    ShowHint
    exit
fi

case $1 in
    "master"   ) stopMaster=1   ;;

    "uploader" ) stopUploader=1 ;;

    "all"      ) stopMaster=1
                 stopUploader=1 ;;

    *          ) ShowHint
                 exit           ;;
esac

Stop $stopUploader Uploader
Stop $stopMaster Master
