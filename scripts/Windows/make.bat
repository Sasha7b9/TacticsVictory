@echo off

if "%1" equ "" goto HINT
if "%2" neq "" goto HINT

set BUILD_TYPE=1
set RUNTIME_TYPE=0

if %1==debug set BUILD_TYPE=Debug& goto MAKE
if %1==release set BUILD_TYPE=Release& set RUNTIME_TYPE=1 & goto MAKE

goto HINT

:STATIC_RUNTIME
if %2==0 goto MAKE
if %2==1 goto MAKE

goto HINT

:MAKE
set current_dir=%CD%
cd ../..
rmdir generated\%1\VictoryU3D /S /Q

cd src
@echo on
cmake . -B..\generated\%1\VictoryU3D -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cd %current_dir%
@echo off

goto EXIT

:HINT

echo.
echo Using make.bat:
echo                make.bat [debug^|release]
echo.
goto EXIT

:EXIT
