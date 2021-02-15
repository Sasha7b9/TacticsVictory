@echo off

if "%1" EQU "" goto SHOW_HINT
if %1==debug   goto START_DEBUG
if %1==release goto START_RELEASE

goto SHOW_HINT

:START_DEBUG
@echo on
start devenv.exe ../../generated/debug/VictoryU3D/VictoryU3D.sln /ProjectConfig Debug
@echo off
goto EXIT

:START_RELEASE
@echo on
start devenv.exe ../../generated/release/VictoryU3D/VictoryU3D.sln /ProjectConfig Release
@echo off
goto EXIT

:SHOW_HINT
echo.
echo Using edit.bat:
echo                 edit [ debug ^| release ]
echo.


:EXIT
