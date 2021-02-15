@echo off

if "%1" equ "" goto HINT
if "%2" neq "" goto HINT

set configuration=1

if %1 equ debug set configuration=Debug & goto BUILD
if %1 equ release set configuration=Release & goto BUILD

goto HINT

:BUILD
set current_dir=%CD%
cd ../../generated/%1/VictoryU3D
@echo on
MSBuild.exe VictoryU3D.sln /p:Configuration=%configuration% /t:build -clp:ErrorsOnly;WarningsOnly -nologo -m
@echo off
cd %current_dir%
goto EXIT

:HINT
echo.
echo Using build.bat:
echo                 build.bat [debug^|release]
echo.
goto EXIT

:EXIT
