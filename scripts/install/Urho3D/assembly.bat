@echo off

if "%1" equ "" goto HINT
if "%2" equ "" goto HINT
if "%3" neq "" goto HINT

set isMake=0
set isBuild=0
set isDebug=0
set isRelease=0

set current_dir=%CD%

cd ../../../..

if not exist Urho3D git clone https://github.com/Sasha7b9/Urho3D.git& set isMake=1& cd Urho3D& goto START_WITH_MAKE

cd Urho3D

git pull

set isMake=0
set isBuild=1
goto LABEL1

:START_WITH_MAKE
if %1==build set isBuild=1 & goto LABEL1
if %1==full  set isMake=1 & set isBuild=1 & goto LABEL1

goto HINT

:LABEL1
if %2==debug   set isDebug=1 & goto LABEL2
if %2==release set isRelease=1 & goto LABEL2
if %2==all     set isDebug=1 & set isRelease=1 & goto LABEL2

goto HINT

:LABEL2
if %isMake% equ 0 goto BUILD

:MAKE
if %isDebug%   equ 1 call %current_dir%\make.bat debug
if %isRelease% equ 1 call %current_dir%\make.bat release

:BUILD
if %isBuild%   equ 0 goto EXIT
if %isDebug%   equ 1 call %current_dir%\build.bat debug
if %isRelease% equ 1 call %current_dir%\build.bat release
goto EXIT

:HINT
echo.
echo Using assembly.bat:
echo                    assembly.bat [make^|build^|full] [debug^|release^|all]
echo.
goto EXIT

:EXIT
cd %current_dir%
