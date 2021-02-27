#!/usr/bin/env bash


# Functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

function MakeDirectory {
    mkdir -p $1
}


function LinkDirectory {
    if [ ! -e $2 ]
    then
        echo "Not exist directory " $2 ". Create it"
        ln -rs $1 $2
    else
        echo "Directory " $2 " already exist"
    fi
}


function CopyFiles {
    cp -rfu $1 $2
}


# Start here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

dir=$PWD
cd ../..

MakeDirectory "out/release"

MakeDirectory "out/debug/log"
MakeDirectory "out/release/log"

LinkDirectory "out/debug/conf"     "out/release/conf"
LinkDirectory "out/debug/CoreData" "out/release/CoreData"
LinkDirectory "out/debug/Data"     "out/release/Data"
LinkDirectory "out/debug/TVData"   "out/release/TVData"

cd $dir
