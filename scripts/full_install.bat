@echo off
rem Всё должно собираться static runtime

set start_dir=%CD%

rem *** Create links ***
rem cd install
rem call create_links.bat
rem cd %start_dir%

rem *** Clone and build Urho3D ***
rem cd install\Urho3D
rem call assembly.bat build all
rem cd %start_dir%

rem *** Build TacticsVictory ***
cd Windows
call assembly.bat full all
cd %start_dir%

rem call copy_dll.bat
