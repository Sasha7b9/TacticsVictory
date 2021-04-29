echo off
rem set address=82.146.54.49
set address=127.0.0.1
echo on
start Master.exe
start Client.exe %address%
start LivingRoom.exe %address%
