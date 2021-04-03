echo off
set address=127.0.0.1:40000
Updater.exe %address%
start Client.exe %address%
