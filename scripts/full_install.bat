@echo off
rem Всё должно собираться static runtime

rem *** Create links ***
set start_dir=%CD%
cd install
call create_links.bat
cd %start_dir%

rem *** Clone and build Urho3D ***
rem cd install\Urho3D
rem call assembly.bat build all
rem cd %start_dir%

rem *** Build TacticsVictory ***
rem cd Windows
rem call make.bat build all
rem cd %start_dir%

rem call copy_dll.bat
