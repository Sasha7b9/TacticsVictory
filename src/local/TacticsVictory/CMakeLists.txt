project (TacticsVictory)

include_directories(.
                    ../BattlerTV
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DCLIENT -DSERVER)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    add_compile_options(/wd4625)
    add_compile_options(/wd4626)
    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
    add_compile_options(/wd5026)
    add_compile_options(/wd5027)
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
    add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC                                                        *.h *.cpp)
file(GLOB AUDIO                                         ../BattlerTV/Audio/*.*)
file(GLOB CORE                                    ../../common_files/Core/*.*)
file(GLOB EDITOR                                        ../BattlerTV/Editor/*.*)
file(GLOB GAME                                          ../BattlerTV/Game/*.*)
file(GLOB GAME_LOGIC                              ../../common_files/Game/Logic/*.*)
file(GLOB GAME_PATH                                     ../BattlerTV/Game/Path/*.*)
file(GLOB GRAPHICS_2D                                   ../BattlerTV/Graphics/2D/*.*)
file(GLOB GUI                                           ../BattlerTV/GUI/*.*)
file(GLOB GUI_CONTROLS                            ../../common_files/GUI/Controls/*.*)
file(GLOB GUI_GUIEDITOR                                 ../BattlerTV/GUI/GuiEditor/*.*)
file(GLOB GUI_GAME                                      ../BattlerTV/GUI/GuiGame/*.*)
file(GLOB GUI_LOGIC                                     ../BattlerTV/GUI/Logic/*.*)
file(GLOB GUI_MENU                                      ../BattlerTV/GUI/Menu/*.*)
file(GLOB GUI_PANELS                                    ../BattlerTV/GUI/Panels/*.*)
file(GLOB GUI_WINDOWS                                   ../BattlerTV/GUI/Windows/*.*)
file(GLOB SCENE                                   ../../common_files/Scene/*.*)
file(GLOB SCENE_CAMERAS                                 ../BattlerTV/Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS                           ../../common_files/Scene/Objects/_TGameObject.*
                                                  ../../common_files/Scene/Objects/_TGameObjectEvents.*)
file(GLOB SCENE_OBJECTS_AMMO                      ../../common_files/Scene/Objects/Ammo/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS                 ../../common_files/Scene/Objects/Buildings/*.*)
file(GLOB SCENE_OBJECTS_TERRAIN                   ../../common_files/Scene/Objects/Terrain/*.*)
file(GLOB SCENE_OBJECTS_UNITS                     ../../common_files/Scene/Objects/Units/*.*)
file(GLOB SCENE_OBJECTS_UNITS_LOGIC               ../../common_files/Scene/Objects/Units/Logic/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS                   ../../common_files/Scene/Objects/Weapons/*.*)
file(GLOB SCENE_PRIMITIVES                        ../../common_files/Scene/Primitives/*.*)
file(GLOB UTILS                                         ../BattlerTV/Utils/*.*
                                                  ../../common_files/Utils/*.*)

source_group(src                                       FILES ${SRC})
source_group(Audio                                     FILES ${AUDIO})
source_group(Core                                      FILES ${CORE})
source_group(Editor                                    FILES ${EDITOR})
source_group(Game                                      FILES ${GAME})
source_group(Game\\Logic                               FILES ${GAME_LOGIC})
source_group(Game\\Path                                FILES ${GAME_PATH})
source_group(Graphics\\2D                              FILES ${GRAPHICS_2D})
source_group(GUI                                       FILES ${GUI})
source_group(GUI\\Controls                             FILES ${GUI_CONTROLS})
source_group(GUI\\GuiEditor                            FILES ${GUI_GUIEDITOR})
source_group(GUI\\Game                                 FILES ${GUI_GAME})
source_group(GUI\\Logic                                FILES ${GUI_LOGIC})
source_group(GUI\\Menu                                 FILES ${GUI_MENU})
source_group(GUI\\Panels                               FILES ${GUI_PANELS})
source_group(GUI\\Windows                              FILES ${GUI_WINDOWS})
source_group(Scene                                     FILES ${SCENE})
source_group(Scene\\Cameras                            FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects                            FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Ammo                      FILES ${SCENE_OBJECTS_AMMO})
source_group(Scene\\Objects\\Buildings                 FILES ${SCENE_OBJECTS_BUILDINGS})
source_group(Scene\\Objects\\Terrain                   FILES ${SCENE_OBJECTS_TERRAIN})
source_group(Scene\\Objects\\Units                     FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Logic              FILES ${SCENE_OBJECTS_UNITS_LOGIC})
source_group(Scene\\Objects\\Weapons                   FILES ${SCENE_OBJECTS_WEAPONS})
source_group(Scene\\Primitives                         FILES ${SCENE_PRIMITIVES})
source_group(Utils                                     FILES ${UTILS})

add_executable( ${PROJECT_NAME} ${SRC} ${AUDIO} ${CORE} ${EDITOR} ${GAME} ${GAME_LOGIC} ${GAME_PATH} ${GRAPHICS_2D}
    ${GUI} ${GUI_CONTROLS} ${GUI_GUIEDITOR} ${GUI_GAME} ${GUI_LOGIC} ${GUI_MENU} ${GUI_PANELS}
    ${GUI_WINDOWS} ${SCENE} ${SCENE_CAMERAS} ${SCENE_OBJECTS} ${SCENE_OBJECTS_AMMO} ${SCENE_OBJECTS_BUILDINGS}
    ${SCENE_OBJECTS_TERRAIN} ${SCENE_OBJECTS_UNITS} ${SCENE_OBJECTS_UNITS_LOGIC} ${SCENE_OBJECTS_WEAPONS}
    ${SCENE_PRIMITIVES} ${UTILS})

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
