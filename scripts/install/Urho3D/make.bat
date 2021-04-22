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
rmdir generated\%1 /S /Q
cmake . -Bgenerated\%1 -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DURHO3D_64BIT=1 -DURHO3D_THREADING=1 -DURHO3D_LUA=0 -DURHO3D_ANGELSCRIPT=0 -DURHO3D_LIB_TYPE=SHARED -DURHO3D_STATIC_RUNTIME=%RUNTIME_TYPE%

goto EXIT

:HINT

echo.
echo Using make.bat:
echo                make.bat [debug^|release]
echo.
goto EXIT

:EXIT