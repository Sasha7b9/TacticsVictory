@echo off

if "%1" equ "" goto SHOW_HINT

if %1==edit goto EDIT
if %1==build goto BUILD

goto SHOW_HINT

:EDIT
set current_dir=%CD%
cd ../../../Urho3D/generated/debug/
@echo on
start devenv.exe Urho3D.sln
@echo off
cd %current_dir%
goto EXIT

:BUILD
set current_dir=%CD%
cd ../install/Urho3D
assembly.bat build all
cd %current_dir%
cd ..
copy_dll.bat
cd %current_dir%
goto EXIT


:SHOW_HINT
echo.
echo Using urho3d.bat:
echo                  urho3d.bat [edit^|build]

:EXIT   