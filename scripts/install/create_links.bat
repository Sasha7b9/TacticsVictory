echo off

cd ../..

mkdir "out/release"

mkdir "out/debug/log"
mkdir "out/release/log"

mklink /j "out/release/conf"     "out/debug/conf"
mklink /j "out/release/CoreData" "out/debug/CoreData"
mklink /j "out/release/Data"     "out/debug/Data"
mklink /j "out/release/TVData"   "out/debug/TVData"

cd scripts/install
