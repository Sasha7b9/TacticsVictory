project (Master)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

set(CMAKE_UNITY_BUILD ON)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

    add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
    add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                    # base class copy constructor is inaccessible or deleted
    add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                    # base class assignment operator is inaccessible or deleted
    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
    add_compile_options(/wd4820)    # bytes' bytes padding added after construct 'member_name'
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'class': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer
                                    # implies that compiler generated copy/move constructors and copy/move assignment
                                    # operators are not trivial

else()

   add_definitions(-Wno-cpp
   )

endif()

file(GLOB SRC         ../../common_files/defines_.h
                                        *.cpp
                                        *.h)
file(GLOB FILE_SYSTEM ../../common_files/FileSystem/ConfigurationFile_.*
                      ../../common_files/FileSystem/FileSystem_.*)
file(GLOB NETWORK     ../../common_files/Network/Other/SocketsTCP_.*)
file(GLOB UTILS       ../../common_files/Utils/Log_.*
                      ../../common_files/Utils/LogRAW_.*
                      ../../common_files/Utils/StringUtils_.*
                      ../../common_files/Utils/SystemFunctions_.*
                      ../../common_files/Utils/SystemUtils_.*)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src        FILES ${SRC})
source_group(FileSystem FILES ${FILE_SYSTEM})
source_group(Network    FILES ${NETWORK})
source_group(Utils      FILES ${UTILS})

source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(${PROJECT_NAME} ${SRC} ${FILE_SYSTEM} ${NETWORK} ${UTILS}
                ${SOCKPP} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

include(../../RuntimeLibrary.cmake)      # »сключаем зависимости от динамических библиотек VS времени
                                         # выполнени€ релизной версии

if(WIN32)
    include(../../CopyToDirEXE.cmake)
    include(../../SetWorkingDirectory.cmake)
endif()

target_link_libraries(${PROJECT_NAME} ws2_32)

include(../../Install.cmake)
