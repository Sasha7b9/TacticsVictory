#!/usr/bin/env bash

# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

function ShowHint {
    echo "    Usage :"
    echo "        assembly.sh [make|build|full] [debug|release|all]"
}


function MakeProject {
    rm -R -f ../../generated/$1/VictoryU3D
    cmake ../../src/CMakeLists.txt -G "CodeBlocks - Unix Makefiles" -B../../generated/$1/VictoryU3D -DCMAKE_BUILD_TYPE=$2
}


function MakeProjects {

# $1 - debug make
# $2 - release make

    if [ $1 -eq 1 ]
    then
        MakeProject "debug" "Debug"
    fi

    if [ $2 -eq 1 ]
    then
        MakeProject "release" "Release"
    fi
}


function BuildProject {
    dir=$PWD
    cd ../../generated/$1/VictoryU3D
    make -j$(nproc)
    make install
    cp remote/Master/Master         ../../../out/$1
    cp remote/DataBase/DataBase     ../../../out/$1
    cp common/Battle/Battle         ../../../out/$1
    cp common/Controller/Controller ../../../out/$1
    cp common/LivingRoom/LivingRoom ../../../out/$1
    cp common/Monitor/Monitor       ../../../out/$1
    cp common/Uploader/Uploader     ../../../out/$1
    cd $dir
}


function BuildProjects {

# $1 - debug build
# $2 - release build

    if [ $1 -eq 1 ]
    then
        BuildProject "debug"
    fi

    if [ $2 -eq 1 ]
    then
        BuildProject "release"
    fi
}


# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

./stop.sh all

set -e              # Exit immediately if a command exits with a non-zero status.

isMake=0            # If 1, then run cmake
isBuild=0           # If 1, then run make
isBuildDebug=0      # If 1, cmake|make for debug gonfiguration
isBuildRelease=0    # If 1, cmake|make for release configuration

if [[ $# -ne 2 ]]
then
    ShowHint
    exit
fi

dir=$PWD

cd ../..

sudo git pull

cd $dir

case $1 in
    "make"  ) isMake=1  ;;

    "build" ) isBuild=1 ;;

    "full"  ) isMake=1
              isBuild=1 ;;

    *       ) ShowHint
              exit      ;;
esac

case $2 in
    "debug"   ) isBuildDebug=1    ;;

    "release" ) isBuildRelease=1; ;;

    "all"     ) isBuildDebug=1
                isBuildRelease=1  ;;

    *         ) ShowHint
                exit              ;;
esac


if [ $isMake -eq 1 ]
then
    MakeProjects $isBuildDebug $isBuildRelease
fi


if [ $isBuild -eq 1 ]
then
    BuildProjects $isBuildDebug $isBuildRelease
fi

