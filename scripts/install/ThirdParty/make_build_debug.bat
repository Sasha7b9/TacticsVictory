rmdir ..\..\..\generated\debug\ThirdParty /S /Q

cmake ../../../src/ThirdParty/CMakeLists.txt -B../../../generated/debug/ThirdParty -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_GENERATOR="Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug

MSBuild.exe ../../../generated/debug/ThirdParty/ThirdParty.sln /p:Configuration=debug /t:build -clp:ErrorsOnly -nologo /m
