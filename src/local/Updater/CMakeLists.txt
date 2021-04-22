project (Updater)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../libs/victory
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                # base class copy constructor is inaccessible or deleted
add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                # base class assignment operator is inaccessible or deleted
add_compile_options(/wd4710)    # 'function' : function not inlined
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'type': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified

file(GLOB SRC                          *.h *.cpp)
file(GLOB FILESYSTEM ../../common_files/FileSystem/FileSystem_.*)
file(GLOB NETWORK    ../../common_files/Network/Other/ConnectorTCP_.*)
file(GLOB UTILS      ../../common_files/Utils/GlobalFunctions_.*
                     ../../libs/victory/Utils/Log_.h
                     ../../common_files/Utils/StringUtils_.*
                     ../../common_files/Utils/UtilsOS_.*)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src        FILES ${SRC})
source_group(FileSystem FILES ${FILESYSTEM})
source_group(Network    FILES ${NETWORK})
source_group(Utils      FILES ${UTILS})

source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

file(GLOB FILES_UNITY ${SRC} ${FILESYSTEM} ${NETWORK} ${UTILS} ${SOCKPP})

add_executable( ${PROJECT_NAME} ${FILES_UNITY} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

set_target_properties(${PROJECT_NAME}       PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${FILES_UNITY}  PROPERTIES UNITY_GROUP "updater")

include(../../RuntimeLibrary.cmake)

include(../../CopyToDirEXE.cmake)
include(../../SetWorkingDirectory.cmake)

target_link_libraries(${PROJECT_NAME} ws2_32 victory)
