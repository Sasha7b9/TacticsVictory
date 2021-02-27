project (BattleTV)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING)

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
    add_compile_options(/wd26812)
    add_compile_options(/wd28251)
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
    add_definitions(-Wno-unused-function # 'xxx' defined but not used
    )
endif()

file(GLOB SRC                                    ../../common_files/*.*
                                                                    *.h *.cpp)
file(GLOB CORE                                   ../../common_files/Core/*.*)
file(GLOB GAME_LOGIC                             ../../common_files/Game/Logic/*.*)
file(GLOB GAME_PATH                              ../../common_files/Game/Path/*.*)
file(GLOB NETWORK                                                   Network/*.*
                                                 ../../common_files/Network/Game/*.*)
file(GLOB SCENE                                  ../../common_files/Scene/*.*)
file(GLOB SCENE_OBJECTS                          ../../common_files/Scene/Objects/*.*)
file(GLOB SCENE_OBJECTS_AMMO                     ../../common_files/Scene/Objects/Ammo/*.*)
file(GLOB SCENE_OBJECTS_AMMO_ROCKET              ../../common_files/Scene/Objects/Ammo/Rocket/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS                ../../common_files/Scene/Objects/Buildings/*.*)
file(GLOB SCENE_OBJECTS_UNITS                    ../../common_files/Scene/Objects/Units/*.*
                                                                    Scene/Objects/Units/*.*)
file(GLOB SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE ../../common_files/Scene/Objects/Units/Accessories/Engine/*.*)
file(GLOB SCENE_OBJECTS_UNITS_LOGIC              ../../common_files/Scene/Objects/Units/Logic/*.*)
file(GLOB SCENE_OBJECTS_UNITS_TANK               ../../common_files/Scene/Objects/Units/Tank/*.*
                                                                    Scene/Objects/Units/Tank/*.*)
file(GLOB SCENE_OBJECTS_UNITS_UNITOBJECT         ../../common_files/Scene/Objects/Units/UnitObject/*.*
                                                                    Scene/Objects/Units/UnitObject/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS                  ../../common_files/Scene/Objects/Weapons/*.*)
file(GLOB SCENE_PRIMITIVES                       ../../common_files/Scene/Primitives/*.*)
file(GLOB SCENE_TERRAIN                          ../../common_files/Scene/Terrain/*.*
                                                                    Scene/Terrain/*.*)
file(GLOB UTILS                                                     Utils/*.*
                                                 ../../common_files/Utils/*.*)

source_group(src                                        FILES ${SRC})
source_group(Core                                       FILES ${CORE})
source_group(Game\\Logic                                FILES ${GAME_LOGIC})
source_group(Game\\Path                                 FILES ${GAME_PATH})
source_group(Network                                    FILES ${NETWORK})
source_group(Scene                                      FILES ${SCENE})
source_group(Scene\\Objects                             FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Ammo                       FILES ${SCENE_OBJECTS_AMMO})
source_group(Scene\\Objects\\Ammo\\Rocket               FILES ${SCENE_OBJECTS_AMMO_ROCKET})
source_group(Scene\\Objects\\Buildings                  FILES ${SCENE_OBJECTS_BUILDINGS})
source_group(Scene\\Objects\\Units                      FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Accessories\\Engine FILES ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE})
source_group(Scene\\Objects\\Units\\Logic               FILES ${SCENE_OBJECTS_UNITS_LOGIC})
source_group(Scene\\Objects\\Units\\Tank                FILES ${SCENE_OBJECTS_UNITS_TANK})
source_group(Scene\\Objects\\Units\\UnitObject          FILES ${SCENE_OBJECTS_UNITS_UNITOBJECT})
source_group(Scene\\Objects\\Weapons                    FILES ${SCENE_OBJECTS_WEAPONS})
source_group(Scene\\Primitives                          FILES ${SCENE_PRIMITIVES})
source_group(Scene\\Terrain                             FILES ${SCENE_TERRAIN})
source_group(Utils                                      FILES ${UTILS})

add_executable( ${PROJECT_NAME} ${SRC} ${CORE} ${GAME_LOGIC} ${GAME_PATH} ${NETWORK} ${SCENE} ${SCENE_OBJECTS}
    ${SCENE_OBJECTS_AMMO} ${SCENE_OBJECTS_AMMO_ROCKET}
    ${SCENE_OBJECTS_BUILDINGS}
    ${SCENE_OBJECTS_UNITS} ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE} ${SCENE_OBJECTS_UNITS_TANK}
    ${SCENE_OBJECTS_UNITS_UNITOBJECT}
    ${SCENE_OBJECTS_UNITS_LOGIC}
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
