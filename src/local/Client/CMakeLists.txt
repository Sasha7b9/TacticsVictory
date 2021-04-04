project (Client)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

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
add_compile_options(/wd26812)   # Prefer 'enum class' over 'enum'
add_compile_options(/wd28251)   # Inconsistent annotation for function: this instance has an error


file(GLOB SRC                         ../../common_files/*.*
                                                         *.h *.cpp)
file(GLOB FILE_SYSTEM                 ../../common_files/FileSystem/ConfigurationFile_.*
                                      ../../common_files/FileSystem/FileSystem_.*)
file(GLOB GUI                         ../../common_files/GUI/*.*
                                                         GUI/*.*)
file(GLOB GUI_CONTROLS                ../../common_files/GUI/Controls/Window_.*
                                      ../../common_files/GUI/Controls/GovernorFloat_.*)
file(GLOB GUI_CONTROLS_BUTTONS        ../../common_files/GUI/Controls/Buttons/ButtonToggled_.*)
file(GLOB GUI_MENU                                       GUI/Menu/*.*)
file(GLOB GUI_MENU_MENUSTART                             GUI/Menu/MenuStart/*.*)
file(GLOB GUI_MENU_MENUSTART_MENUPLAY                    GUI/Menu/MenuStart/MenuPlay/*.*)
file(GLOB NETWORK                     ../../common_files/Network/Other/MasterServer_.*
                                      ../../common_files/Network/Other/SocketsTCP_.*)
file(GLOB SCENE                                          Scene/*.*)
file(GLOB SCENE_CAMERAS                                  Scene/Cameras/*.*)
file(GLOB UTILS                       ../../common_files/Utils/Log_.*
                                      ../../common_files/Utils/LogRAW_.*
                                      ../../common_files/Utils/StringUtils_.*
                                      ../../common_files/Utils/SystemFunctions_.*
                                      ../../common_files/Utils/SystemUtils_.*)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src                            FILES ${SRC})
source_group(FileSystem                     FILES ${FILE_SYSTEM})
source_group(GUI                            FILES ${GUI})
source_group(GUI\\Controls                  FILES ${GUI_CONTROLS})
source_group(GUI\\Controls\\Butttons        FILES ${GUI_CONTROLS_BUTTONS})
source_group(GUI\\Menu                      FILES ${GUI_MENU})
source_group(GUI\\Menu\\MenuStart           FILES ${GUI_MENU_MENUSTART})
source_group(GUI\\Menu\\MenuStart\\MenuPlay FILES ${GUI_MENU_MENUSTART_MENUPLAY})
source_group(Network                        FILES ${NETWORK})
source_group(Scene                          FILES ${SCENE})
source_group(Scene\\Cameras                 FILES ${SCENE_CAMERAS})
source_group(Utils                          FILES ${UTILS})

source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable( ${PROJECT_NAME} ${SRC}
                ${GUI} ${GUI_CONTROLS} ${GUI_CONTROLS_BUTTONS}
                ${GUI_MENU} ${GUI_MENU_MENUSTART} ${GUI_MENU_MENUSTART_MENUPLAY}
                ${FILE_SYSTEM} ${NETWORK} ${UTILS}
                ${SCENE} ${SCENE_CAMERAS}
                ${SOCKPP} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

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
