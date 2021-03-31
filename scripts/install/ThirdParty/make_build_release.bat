rmdir ..\..\..\generated\release\ThirdParty /S /Q

cmake ../../../src/ThirdParty/CMakeLists.txt -B../../../generated/release/ThirdParty -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release

MSBuild.exe ../../../generated/release/ThirdParty/ThirdParty.sln /p:Configuration=release /t:build -clp:ErrorsOnly -nologo /m
