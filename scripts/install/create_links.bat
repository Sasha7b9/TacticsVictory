echo off

cd ../..

if not exist "out/release"     mkdir "out/release"
if not exist "out/debug/log"   mkdir "out/debug/log"
if not exist "out/release/log" mkdir "out/release/log"

if not exist "out/release/conf"     mklink /j "out/release/conf"     "out/debug/conf"
if not exist "out/release/CoreData" mklink /j "out/release/CoreData" "out/debug/CoreData"
if not exist "out/release/Data"     mklink /j "out/release/Data"     "out/debug/Data"
if not exist "out/release/TVData"   mklink /j "out/release/TVData"   "out/debug/TVData"

cd scripts/install
