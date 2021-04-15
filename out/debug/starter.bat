echo off
set address=82.146.54.49
echo on
Updater.exe %address%
start Client.exe %address%
start LivingRoom.exe %address%
