@echo off
rem Всё должно собираться static runtime

set start_dir=%CD%

rem *** Create links ***
cd install
call create_links.bat
cd %start_dir%

rem *** Clone and build Urho3D ***
cd install\Urho3D
call assembly.bat build all
cd %start_dir%

rem *** Build TacticsVictory ***
rem cd Windows
rem call make.bat build all
rem cd %start_dir%

rem call copy_dll.bat
