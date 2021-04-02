project (Updater)

set(CMAKE_UNITY_BUILD ON)

include_directories(.)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

file(GLOB SRC       *.h *.cpp)

source_group(src    FILES ${SRC})

add_executable( ${PROJECT_NAME} ${SRC})

include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)
