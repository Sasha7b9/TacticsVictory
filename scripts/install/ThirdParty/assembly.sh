#!/usr/bin/env bash

function ShowHint {
    echo "Usage :"
    echo "        ./assembly.sh [make|build|full] [debug|release|all]"
}


function MakeProject {
    rm -R -f generated/$1
    cmake . -Bgenerated/$1 -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=$2 -DURHO3D_64BIT=1 -DURHO3D_THREADING=1 -DURHO3D_LIB_TYPE=SHARED
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
    cd generated/$1
    make -j$(nproc)
    make
    cd ../..
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

# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

set -e

if [[ $# -ne 2 ]]
then
    ShowHint
    exit
fi

isMake=0
isBuild=0
isDebug=0
isRelease=0

echo $1

dir=$PWD

cd ../../../..

if [ -d Urho3D ]
then
    isMake=0
    isBuild=1
fi

if [ ! -d Urho3D ]
then
    git clone https://github.com/Sasha7b9/Urho3D.git
fi

case $1 in
"make"  ) isMake=1  ;;

"build" ) isBuild=1 ;;

"full"  ) isMake=1
          isBuild=1 ;;

*       ) ShowHint
          exit      ;;
esac

cd Urho3D

git pull

case $2 in
    "debug"   ) isDebug=1   ;;

    "release" ) isRelease=1 ;;

    "all"     ) isDebug=1
                isRelease=1 ;;

    *         ) ShowHint
                exit        ;;
esac

if [ $isMake -eq 1 ]
then
    MakeProjects $isDebug $isRelease
fi

if [ $isBuild -eq 1 ]
then
    BuildProjects $isDebug $isRelease
fi

cd $dir
