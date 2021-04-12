project (Hangar)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D -DU3D -DGRAPHICS)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS  /STACK:100000000")

add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                # base class copy constructor is inaccessible or deleted
add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                # base class assignment operator is inaccessible or deleted
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4710)    # 'function' : function not inlined
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'type': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified
add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
add_compile_options(/wd26812)   # Prefer 'enum class' over 'enum' (Enum.3)
add_compile_options(/wd28251)   # Inconsistent annotation for function: this instance has an error

file(GLOB SRC          ../../common_files/*.*
                                          *.h *.cpp)
file(GLOB FILE_SYSTEM  ../../common_files/FileSystem/ConfigurationFile_.*
                       ../../common_files/FileSystem/FileSystem_.*)
file(GLOB GUI          ../../common_files/GUI/Cursor_.*
                                          GUI/*.*)
file(GLOB GUI_CHAT                        GUI/Chat/*.*)
file(GLOB GUI_CONTROLS ../../common_files/GUI/Controls/Window_.*)
file(GLOB INPUT        ../../common_files/Input/Mouse_.*
                                          Input/Mouse.cpp)
file(GLOB NETWORK      ../../common_files/Network/Other/MasterServer_.*
                       ../../common_files/Network/Other/SocketsTCP_.*)
file(GLOB UTILS        ../../common_files/Utils/Log_.*
                       ../../common_files/Utils/LogU3D_.*
                       ../../common_files/Utils/StringUtils_.*
                       ../../common_files/Utils/UtilsOS_.*)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src           FILES ${SRC})
source_group(FileSystem    FILES ${FILE_SYSTEM})
source_group(GUI           FILES ${GUI})
source_group(GUI\\Chat     FILES ${GUI_CHAT})
source_group(GUI\\Controls FILES ${GUI_CONTROLS})
source_group(Input         FILES ${INPUT})
source_group(Network       FILES ${NETWORK})
source_group(Utils         FILES ${UTILS})

source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable( ${PROJECT_NAME} ${SRC} ${FILE_SYSTEM} ${GUI} ${GUI_CHAT} ${GUI_CONTROLS} ${INPUT} ${NETWORK} ${UTILS}
                ${SOCKPP} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

set_target_properties(${PROJECT_NAME}                                                 PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${SRC} ${FILE_SYSTEM} ${GUI} ${GUI_CHAT} ${GUI_CONTROLS} ${INPUT} ${NETWORK} ${UTILS} 
                                                                                      PROPERTIES UNITY_GROUP "bucket")

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

target_link_libraries(${PROJECT_NAME} ws2_32)

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
