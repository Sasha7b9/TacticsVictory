@echo off

rem Всё должно собираться static runtime

set start_dir=%CD%

rem *** Create links ***
cd install
call create_links.bat
cd %start_dir%

rem *** Clone and build Urho3D ***
cd install\Urho3D
rem call assembly.bat build all
call assembly.bat full all
cd %start_dir%

rem *** Build TacticsVictory ***
cd Windows
call assembly.bat full all
cd %start_dir%
