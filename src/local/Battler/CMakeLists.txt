project (Battler)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS  /STACK:100000000")

set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                # base class copy constructor is inaccessible or deleted
add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                # base class assignment operator is inaccessible or deleted
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'type': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified
add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
add_compile_options(/wd26812)
add_compile_options(/wd28251)

if(${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
endif()

file(GLOB SRC                                    ../../common_files/*.*
                                                                    *.h *.cpp)
file(GLOB AUDIO                                                     Audio/*.*)
file(GLOB CORE                                   ../../common_files/Core/*.*)
file(GLOB EDITOR                                                    Editor/*.*)
file(GLOB GAME                                                      Game/*.*)
file(GLOB GAME_LOGIC                             ../../common_files/Game/Logic/*.*)
file(GLOB GAME_PATH                              ../../common_files/Game/Path/*.*
                                                                    Game/Path/*.*)
file(GLOB GRAPHICS_2D                                               Graphics/2D/*.*)
file(GLOB GRAPHICS_3D                                               Graphics/3D/*.*)
file(GLOB GUI                                                       GUI/*.*)
file(GLOB GUI_CONTROLS                           ../../common_files/GUI/Controls/*.*)
file(GLOB GUI_CONTROLS_BUTTONS                   ../../common_files/GUI/Controls/Buttons/*.*)
file(GLOB GUI_CONTROLS_SLIDERS                   ../../common_files/GUI/Controls/Sliders/*.*)
file(GLOB GUI_GUIEDITOR                                             GUI/GuiEditor/*.*)
file(GLOB GUI_GAME                                                  GUI/GuiGame/*.*)
file(GLOB GUI_LOGIC                                                 GUI/Logic/*.*)
file(GLOB GUI_MENU                                                  GUI/Menu/*.*)
file(GLOB GUI_MENU_START                                            GUI/Menu/MenuStart/*.*)
file(GLOB GUI_MENU_START_PLAY                                       GUI/Menu/MenuStart/MenuPlay/*.*)
file(GLOB GUI_PANELS                                                GUI/Panels/*.*)
file(GLOB GUI_WINDOWS                                               GUI/Windows/*.*)
file(GLOB INPUT                                                     Input/*.*)
file(GLOB NETWORK                                ../../common_files/Network/Game/*.*
                                                                    Network/*.*)
file(GLOB NETWORK_MESSAGES                       ../../common_files/Network/Game/Messages/*.*
                                                                    Network/Messages/*.*)
file(GLOB SCENE                                  ../../common_files/Scene/*.*
                                                                    Scene/*.*)
file(GLOB SCENE_CAMERAS                                             Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS                          ../../common_files/Scene/Objects/*.*
                                                                    Scene/Objects/*.*)
file(GLOB SCENE_OBJECTS_AMMO                     ../../common_files/Scene/Objects/Ammo/*.*)
file(GLOB SCENE_OBJECTS_AMMO_ROCKET                                 Scene/Objects/Ammo/Rocket/*.*
                                                 ../../common_files/Scene/Objects/Ammo/Rocket/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS                ../../common_files/Scene/Objects/Buildings/*.*)
file(GLOB SCENE_OBJECTS_UNITS                    ../../common_files/Scene/Objects/Units/*.*
                                                                    Scene/Objects/Units/*.*)
file(GLOB SCENE_OBJECTS_UNITS_ACCESSORIES        ../../common_files/Scene/Objects/Units/Accessories/*.*)
file(GLOB SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE ../../common_files/Scene/Objects/Units/Accessories/Engine/*.*)
file(GLOB SCENE_OBJECTS_UNITS_AIR                ../../common_files/Scene/Objects/Units/Air/*.*)
file(GLOB SCENE_OBJECTS_UNITS_AIR_AIRPLANE       ../../common_files/Scene/Objects/Units/Air/AirPlane/*.*
                                                                    Scene/Objects/Units/Air/AirPlane/*.*)
file(GLOB SCENE_OBJECTS_UNITS_GROUND             ../../common_files/Scene/Objects/Units/Ground/*.*)
file(GLOB SCENE_OBJECTS_UNITS_GROUND_TANK        ../../common_files/Scene/Objects/Units/Ground/Tank/*.*
                                                                    Scene/Objects/Units/Ground/Tank/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS                  ../../common_files/Scene/Objects/Weapons/*.*)
file(GLOB SCENE_PRIMITIVES                       ../../common_files/Scene/Primitives/*.*)
file(GLOB SCENE_TERRAIN                          ../../common_files/Scene/Terrain/*.*
                                                                    Scene/Terrain/*.*)
file(GLOB UTILS                                  ../../common_files/Utils/Log_.*
                                                 ../../common_files/Utils/LogU3D_.*
                                                 ../../common_files/Utils/StringUtils_.*
                                                 ../../common_files/Utils/SystemFunctions_.*
                                                 ../../common_files/Utils/SystemUtils_.*
                                                                    Utils/*.*)

source_group(src                                        FILES ${SRC})
source_group(Audio                                      FILES ${AUDIO})
source_group(Core                                       FILES ${CORE})
source_group(Editor                                     FILES ${EDITOR})
source_group(Game                                       FILES ${GAME})
source_group(Game\\Logic                                FILES ${GAME_LOGIC})
source_group(Game\\Path                                 FILES ${GAME_PATH})
source_group(Graphics\\2D                               FILES ${GRAPHICS_2D})
source_group(Graphics\\3D                               FILES ${GRAPHICS_3D})
source_group(GUI                                        FILES ${GUI})
source_group(GUI\\Controls                              FILES ${GUI_CONTROLS})
source_group(GUI\\Controls\\Buttons                     FILES ${GUI_CONTROLS_BUTTONS})
source_group(GUI\\Controls\\Sliders                     FILES ${GUI_CONTROLS_SLIDERS})
source_group(GUI\\GuiEditor                             FILES ${GUI_GUIEDITOR})
source_group(GUI\\Game                                  FILES ${GUI_GAME})
source_group(GUI\\Logic                                 FILES ${GUI_LOGIC})
source_group(GUI\\Menu                                  FILES ${GUI_MENU})
source_group(GUI\\Menu\\MenuStart                       FILES ${GUI_MENU_START})
source_group(GUI\\Menu\\MenuStart\\MenuPlay             FILES ${GUI_MENU_START_PLAY})
source_group(GUI\\Panels                                FILES ${GUI_PANELS})
source_group(GUI\\Windows                               FILES ${GUI_WINDOWS})
source_group(Input                                      FILES ${INPUT})
source_group(Network                                    FILES ${NETWORK})
source_group(Network\\Messages                          FILES ${NETWORK_MESSAGES})
source_group(Scene                                      FILES ${SCENE})
source_group(Scene\\Cameras                             FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects                             FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Ammo                       FILES ${SCENE_OBJECTS_AMMO})
source_group(Scene\\Objects\\Ammo\\Rocket               FILES ${SCENE_OBJECTS_AMMO_ROCKET})
source_group(Scene\\Objects\\Buildings                  FILES ${SCENE_OBJECTS_BUILDINGS})
source_group(Scene\\Objects\\Units                      FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Accessories         FILES ${SCENE_OBJECTS_UNITS_ACCESSORIES})
source_group(Scene\\Objects\\Units\\Accessories\\Engine FILES ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE})
source_group(Scene\\Objects\\Units\\Air                 FILES ${SCENE_OBJECTS_UNITS_AIR})
source_group(Scene\\Objects\\Units\\Air\\Ariplane       FILES ${SCENE_OBJECTS_UNITS_AIR_AIRPLANE})
source_group(Scene\\Objects\\Units\\Ground              FILES ${SCENE_OBJECTS_UNITS_GROUND})
source_group(Scene\\Objects\\Units\\Ground\\Tank        FILES ${SCENE_OBJECTS_UNITS_GROUND_TANK})
source_group(Scene\\Objects\\Weapons                    FILES ${SCENE_OBJECTS_WEAPONS})
source_group(Scene\\Primitives                          FILES ${SCENE_PRIMITIVES})
source_group(Scene\\Terrain                             FILES ${SCENE_TERRAIN})
source_group(Utils                                      FILES ${UTILS})

add_executable( ${PROJECT_NAME} ${SRC} ${AUDIO} ${CORE} ${EDITOR} ${GAME} ${GAME_LOGIC} ${GAME_PATH} ${GRAPHICS_2D}
    ${GRAPHICS_3D}
    ${GRAPHICS_OBJECTS} ${GUI} ${GUI_CONTROLS} ${GUI_CONTROLS_BUTTONS} ${GUI_CONTROLS_SLIDERS} ${GUI_GUIEDITOR}
    ${GUI_GAME} ${GUI_LOGIC}
    ${GUI_MENU} ${GUI_MENU_START} ${GUI_MENU_START_PLAY} ${GUI_PANELS}
    ${GUI_WINDOWS} ${INPUT} ${NETWORK} ${NETWORK_MESSAGES} ${SCENE} ${SCENE_CAMERAS} ${SCENE_OBJECTS}
    ${SCENE_OBJECTS_AMMO} ${SCENE_OBJECTS_AMMO_ROCKET}
    ${SCENE_OBJECTS_BUILDINGS}
    ${SCENE_OBJECTS_UNITS} ${SCENE_OBJECTS_UNITS_ACCESSORIES} ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE}
    ${SCENE_OBJECTS_UNITS_AIR} ${SCENE_OBJECTS_UNITS_AIR_AIRPLANE}
    ${SCENE_OBJECTS_UNITS_GROUND} ${SCENE_OBJECTS_UNITS_GROUND_TANK}
    ${SCENE_OBJECTS_WEAPONS} ${SCENE_PRIMITIVES} ${SCENE_TERRAIN} ${UTILS})

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
