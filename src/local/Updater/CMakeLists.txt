project (Updater)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

add_compile_options(/wd4710)    # 'function' : function not inlined
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified

file(GLOB SRC                             *.h *.cpp)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src    FILES ${SRC})

source_group(ThirdParty\\sockpp                FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources       FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include       FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable( ${PROJECT_NAME} ${SRC}
                ${SOCKPP} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

target_link_libraries(${PROJECT_NAME} ws2_32)
