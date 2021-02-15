@echo off

set _CURRENT_DIR_=%CD%

cd ..

set PROJECT_DIR=%CD%

cd %_CURRENT_DIR_%

@echo on

%comspec% /k "c:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat"
