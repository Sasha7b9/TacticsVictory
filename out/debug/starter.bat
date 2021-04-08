echo off
set address=127.0.0.1
echo on
Updater.exe %address%
start Client.exe %address%
