#!/usr/bin/env bash

# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

function ShowHint {
    echo "    Usage :"
    echo "        assembly.sh [make|build|full] [debug|release|all]"
}


function MakeProjectDebug {
    rm -R -f ../../generated/debug/VictoryU3D
    cmake ../../src/CMakeLists.txt -G "CodeBlocks - Unix Makefiles" -B../../generated/debug/VictoryU3D -DCMAKE_BUILD_TYPE=Debug
    rm ready_make_debug
    echo "1" >> ready_make_debug
}


function MakeProjectRelease {
    rm -R -f ../../generated/release/VictoryU3D
    cmake ../../src/CMakeLists.txt -G "CodeBlocks - Unix Makefiles" -B../../generated/release/VictoryU3D -DCMAKE_BUILD_TYPE=Release
    rm ready_make_release
    echo "1" >> ready_make_release
}


function MakeProjects {

# $1 - debug make
# $2 - release make

    if [ $1 -eq 1 ]
    then
        rm ready_make_debug
        echo "0" >> ready_make_debug
        MakeProjectDebug &
    fi

    if [ $2 -eq 1 ]
    then
        rm ready_make_release
        echo "0" >> ready_make_release
        MakeProjectRelease &
    fi
}


function BuildProjectDebug {
    cd ../../generated/debug/VictoryU3D
    make -j$(nproc)
    make install
    cp remote/Master/Master         ../../../out/debug
    cp remote/DataBase/DataBase     ../../../out/debug
    cp common/Battle/Battle         ../../../out/debug
    cp common/Controller/Controller ../../../out/debug
    cp common/LivingRoom/LivingRoom ../../../out/debug
    cp common/Monitor/Monitor       ../../../out/debug
    cp common/Uploader/Uploader     ../../../out/debug
    
    rm ready_build_debug
    echo "1" >> ready_build_debug
}


function BuildProjectRelease {
    cd ../../generated/release/VictoryU3D
    make -j$(nproc)
    make install
    cp remote/Master/Master         ../../../out/release
    cp remote/DataBase/DataBase     ../../../out/release
    cp common/Battle/Battle         ../../../out/release
    cp common/Controller/Controller ../../../out/release
    cp common/LivingRoom/LivingRoom ../../../out/release
    cp common/Monitor/Monitor       ../../../out/release
    cp common/Uploader/Uploader     ../../../out/release
    
    rm ready_build_release
    echo "1" >> ready_build_release
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

echo "1" >> ready_make_debug
echo "1" >> ready_make_release

if [ $isMake -eq 1 ]
then
    MakeProjects $isBuildDebug $isBuildRelease
fi

echo "1" >> ready_build_debug
echo "1" >> ready_build_release

if [ $isBuild -eq 1 ]
then

    if [ $isBuildDebug -eq 1 ]
    then
        rm ready_build_debug
        echo "0" >> ready_build_debug
    
        rd_mk_db=$(<ready_make_debug)
        while [ $rd_mk_db -eq "0" ]
        do
            rd_mk_db=$(<ready_make_debug)
        done
        BuildProjectDebug &
    fi

    if [ $isBuildRelease -eq 1 ]
    then
        rm ready_build_release
        echo "0" >> ready_build_release

        rd_mk_rl=$(<ready_make_release)
        while [ $rd_mk_rl -eq "0" ]
        do
            rd_mk_rl=$(<ready_make_release)
        done
        BuildProjectRelease &
    fi
fi

rm ready_make_debug
rm ready_make_release

rd=$(<ready_build_debug)
while [ $rd -eq "0" ]
do
    rd=$(<ready_build_debug)
done

rd=$(<ready_build_release)
while [ $rd -eq "0" ]
do
    rd=$(<ready_build_release)
done

echo " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! point 1"

rm ready_build_debug
rm ready_build_release
