project (BattlerTV)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DCLIENT)

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
file(GLOB AUDIO                                                      Audio/*.*)
file(GLOB CORE                                    ../../common_files/Core/*.*)
file(GLOB EDITOR                                                     Editor/*.*)
file(GLOB GAME                                                       Game/*.*)
file(GLOB GAME_LOGIC                                                 Game/Logic/*.*)
file(GLOB GAME_PATH                                                  Game/Path/*.*)
file(GLOB GRAPHICS_2D                                                Graphics/2D/*.*)
file(GLOB GUI                                                        GUI/*.*)
file(GLOB GUI_CONTROLS                            ../../common_files/GUI/Controls/*.*)
file(GLOB GUI_GUIEDITOR                                              GUI/GuiEditor/*.*)
file(GLOB GUI_GAME                                                   GUI/GuiGame/*.*)
file(GLOB GUI_LOGIC                                                  GUI/Logic/*.*)
file(GLOB GUI_MENU                                                   GUI/Menu/*.*)
file(GLOB GUI_PANELS                                                 GUI/Panels/*.*)
file(GLOB GUI_WINDOWS                                                GUI/Windows/*.*)
file(GLOB NETWORK                                 ../../common_files/Network/Game/*.*
                                                                     Network/*.*)
file(GLOB SCENE                                   ../../common_files/Scene/*.*)
file(GLOB SCENE_CAMERAS                                              Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS                           ../../common_files/Scene/Objects/*.*)
file(GLOB SCENE_OBJECTS_AMMO                      ../../common_files/Scene/Objects/Ammo/*.*)
file(GLOB SCENE_OBJECTS_AMMO_AIRBOMB              ../../common_files/Scene/Objects/Ammo/AirBomb/*.*)
file(GLOB SCENE_OBJECTS_AMMO_GRENADE              ../../common_files/Scene/Objects/Ammo/Grenade/*.*)
file(GLOB SCENE_OBJECTS_AMMO_MINE                 ../../common_files/Scene/Objects/Ammo/Mine/*.*)
file(GLOB SCENE_OBJECTS_AMMO_ROCKET               ../../common_files/Scene/Objects/Ammo/Rocket/*.*)
file(GLOB SCENE_OBJECTS_AMMO_ROLLINGBOMB          ../../common_files/Scene/Objects/Ammo/RollingBomb/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS                 ../../common_files/Scene/Objects/Buildings/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_CIVILPLANT      ../../common_files/Scene/Objects/Buildings/CivilPlant/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_MILITARYPLANT   ../../common_files/Scene/Objects/Buildings/MilitaryPlant/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_POWERPLANT      ../../common_files/Scene/Objects/Buildings/PowerPlant/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_PROCESSINGPLANT ../../common_files/Scene/Objects/Buildings/ProcessingPlant/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_SHAFT           ../../common_files/Scene/Objects/Buildings/Shaft/*.*)
file(GLOB SCENE_OBJECTS_BUILDINGS_WAREHOUSEAMMO   ../../common_files/Scene/Objects/Buildings/WarehouseAmmo/*.*)
file(GLOB SCENE_OBJECTS_TERRAIN                   ../../common_files/Scene/Objects/Terrain/*.*)
file(GLOB SCENE_OBJECTS_UNITS                     ../../common_files/Scene/Objects/Units/*.*)
file(GLOB SCENE_OBJECTS_UNITS_AIRPLANE            ../../common_files/Scene/Objects/Units/Airplane/*.*)
file(GLOB SCENE_OBJECTS_UNITS_BOMBER              ../../common_files/Scene/Objects/Units/Bomber/*.*)
file(GLOB SCENE_OBJECTS_UNITS_BUILDER             ../../common_files/Scene/Objects/Units/Builder/*.*)
file(GLOB SCENE_OBJECTS_UNITS_HELICOPTER          ../../common_files/Scene/Objects/Units/Helicopter/*.*)
file(GLOB SCENE_OBJECTS_UNITS_ROBOT               ../../common_files/Scene/Objects/Units/Robot/*.*)
file(GLOB SCENE_OBJECTS_UNITS_SUPPLIERAMMO        ../../common_files/Scene/Objects/Units/SupplierAmmo/*.*)
file(GLOB SCENE_OBJECTS_UNITS_TANK                ../../common_files/Scene/Objects/Units/Tank/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS                   ../../common_files/Scene/Objects/Weapons/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS_GRENADERLAUNCHER  ../../common_files/Scene/Objects/Weapons/GrenaderLauncher/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS_GUN               ../../common_files/Scene/Objects/Weapons/Gun/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS_LASER             ../../common_files/Scene/Objects/Weapons/Laser/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS_MACHINEGUN        ../../common_files/Scene/Objects/Weapons/MacheneGun/*.*)
file(GLOB SCENE_OBJECTS_WEAPONS_ROCKETLAUNCHER    ../../common_files/Scene/Objects/Weapons/RocketLauncher/*.*)
file(GLOB SCENE_PRIMITIVES                        ../../common_files/Scene/Primitives/*.*)
file(GLOB UTILS                                                      Utils/*.*)

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
source_group(Network                                   FILES ${NETWORK})
source_group(Scene                                     FILES ${SCENE})
source_group(Scene\\Cameras                            FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects                            FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Ammo                      FILES ${SCENE_OBJECTS_AMMO})
source_group(Scene\\Objects\\Ammo\\AirBomb             FILES ${SCENE_OBJECTS_AMMO_AIRBOMB})
source_group(Scene\\Objects\\Ammo\\Grenade             FILES ${SCENE_OBJECTS_AMMO_GRENADE})
source_group(Scene\\Objects\\Ammo\\Mine                FILES ${SCENE_OBJECTS_AMMO_MINE})
source_group(Scene\\Objects\\Ammo\\Rocket              FILES ${SCENE_OBJECTS_AMMO_ROCKET})
source_group(Scene\\Objects\\Ammo\\RollingBomb         FILES ${SCENE_OBJECTS_AMMO_ROLLINGBOMB})
source_group(Scene\\Objects\\Buildings                 FILES ${SCENE_OBJECTS_BUILDINGS})
source_group(Scene\\Objects\\Buildings\\CivilPlant     FILES ${SCENE_OBJECTS_BUILDINGS_CIVILPLANT})
source_group(Scene\\Objects\\Buildings\\MilitaryPlant  FILES ${SCENE_OBJECTS_BUILDINGS_MILITARYPLANT})
source_group(Scene\\Objects\\Buildings\\PowerPlant     FILES ${SCENE_OBJECTS_BUILDINGS_POWERPLANT})
source_group(Scene\\Objects\\Buildings\\ProcessingPlan FILES ${SCENE_OBJECTS_BUILDINGS_PROCESSINGPLANT})
source_group(Scene\\Objects\\Buildings\\Shaft          FILES ${SCENE_OBJECTS_BUILDINGS_SHAFT})
source_group(Scene\\Objects\\Buildings\\WarehouseAmmo  FILES ${SCENE_OBJECTS_BUILDINGS_WAREHOUSEAMMO})
source_group(Scene\\Objects\\Terrain                   FILES ${SCENE_OBJECTS_TERRAIN})
source_group(Scene\\Objects\\Units                     FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Airplane           FILES ${SCENE_OBJECTS_UNITS_AIRPLANE})
source_group(Scene\\Objects\\Units\\Bomber             FILES ${SCENE_OBJECTS_UNITS_BOMBER})
source_group(Scene\\Objects\\Units\\Builder            FILES ${SCENE_OBJECTS_UNITS_BUILDER})
source_group(Scene\\Objects\\Units\\Helicopter         FILES ${SCENE_OBJECTS_UNITS_HELICOPTER})
source_group(Scene\\Objects\\Units\\Robot              FILES ${SCENE_OBJECTS_UNITS_ROBOT})
source_group(Scene\\Objects\\Units\\SupplierAmmo       FILES ${SCENE_OBJECTS_UNITS_SUPPLIERAMMO})
source_group(Scene\\Objects\\Units\\Tank               FILES ${SCENE_OBJECTS_UNITS_TANK})
source_group(Scene\\Objects\\Weapons                   FILES ${SCENE_OBJECTS_WEAPONS})
source_group(Scene\\Objects\\Weapons\\GrenadeLauncher  FILES ${SCENE_OBJECTS_WEAPONS_GRENADERLAUNCHER})
source_group(Scene\\Objects\\Weapons\\Gun              FILES ${SCENE_OBJECTS_WEAPONS_GUN})
source_group(Scene\\Objects\\Weapons\\Laser            FILES ${SCENE_OBJECTS_WEAPONS_LASER})
source_group(Scene\\Objects\\Weapons\\MachineGun       FILES ${SCENE_OBJECTS_WEAPONS_MACHINEGUN})
source_group(Scene\\Objects\\Weapons\\RocketLauncher   FILES ${SCENE_OBJECTS_WEAPONS_ROCKETLAUNCHER})
source_group(Scene\\Primitives                         FILES ${SCENE_PRIMITIVES})
source_group(Utils                                     FILES ${UTILS})

add_executable( ${PROJECT_NAME} ${SRC} ${AUDIO} ${CORE} ${EDITOR} ${GAME} ${GAME_LOGIC} ${GAME_PATH} ${GRAPHICS_2D}
    ${GRAPHICS_OBJECTS} ${GUI} ${GUI_CONTROLS} ${GUI_GUIEDITOR} ${GUI_GAME} ${GUI_LOGIC} ${GUI_MENU} ${GUI_PANELS}
    ${GUI_WINDOWS} ${NETWORK} ${SCENE} ${SCENE_CAMERAS} ${SCENE_OBJECTS} ${SCENE_OBJECTS_AMMO}
    ${SCENE_OBJECTS_AMMO_AIRBOMB} ${SCENE_OBJECTS_AMMO_GRENADE} ${SCENE_OBJECTS_AMMO_MINE} ${SCENE_OBJECTS_AMMO_ROCKET}
    ${SCENE_OBJECTS_AMMO_ROLLINGBOMB} ${SCENE_OBJECTS_BUILDINGS} ${SCENE_OBJECTS_BUILDINGS_CIVILPLANT}
    ${SCENE_OBJECTS_BUILDINGS_MILITARYPLANT} ${SCENE_OBJECTS_BUILDINGS_POWERPLANT}
    ${SCENE_OBJECTS_BUILDINGS_PROCESSINGPLANT} ${SCENE_OBJECTS_BUILDINGS_SHAFT} ${SCENE_OBJECTS_BUILDINGS_WAREHOUSEAMMO}
    ${SCENE_OBJECTS_TERRAIN} ${SCENE_OBJECTS_UNITS} ${SCENE_OBJECTS_UNITS_AIRPLANE} ${SCENE_OBJECTS_UNITS_BOMBER}
    ${SCENE_OBJECTS_UNITS_BUILDER} ${SCENE_OBJECTS_UNITS_HELICOPTER} ${SCENE_OBJECTS_UNITS_ROBOT}
    ${SCENE_OBJECTS_UNITS_SUPPLIERAMMO} ${SCENE_OBJECTS_UNITS_TANK} ${SCENE_OBJECTS_WEAPONS}
    ${SCENE_OBJECTS_WEAPONS_GRENADERLAUNCHER} ${SCENE_OBJECTS_WEAPONS_GUN} ${SCENE_OBJECTS_WEAPONS_LASER}
    ${SCENE_OBJECTS_WEAPONS_MACHINEGUN} ${SCENE_OBJECTS_WEAPONS_ROCKETLAUNCHER} ${SCENE_PRIMITIVES} ${UTILS})

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
