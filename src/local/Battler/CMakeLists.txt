project (Battler)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DCLIENT)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    add_compile_options(/wd4514)    # 'xxx': unreferenced inline function has been removed
    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
    add_compile_options(/wd4820)    # 'xxx': 'n' bytes padding added after base class 'yyy'
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
    add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC                                                       *.h *.cpp)
file(GLOB CORE                                                      Core/*.*)
file(GLOB EDITOR                                                    Editor/*.*)
file(GLOB GAME                                                      Game/*.*)
file(GLOB GAME_LOGIC                                                Game/Logic/*.*)
file(GLOB GAME_OBJECTS                                              Game/Objects/*.*)
file(GLOB GAME_OBJECTS_AMMO                                         Game/Objects/Ammo/*.*)
file(GLOB GAME_OBJECTS_AMMO_AIRBOMB                                 Game/Objects/Ammo/AirBomb/*.*)
file(GLOB GAME_OBJECTS_AMMO_GRENADE                                 Game/Objects/Ammo/Grenade/*.*)
file(GLOB GAME_OBJECTS_AMMO_MINE                                    Game/Objects/Ammo/Mine/*.*)
file(GLOB GAME_OBJECTS_AMMO_ROCKET                                  Game/Objects/Ammo/Rocket/*.*)
file(GLOB GAME_OBJECTS_AMMO_ROLLINGBOMB                             Game/Objects/Ammo/RollingBomb/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS                                    Game/Objects/Buildings/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_CIVILPLANT                         Game/Objects/Buildings/CivilPlant/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_MILITARYPLANT                      Game/Objects/Buildings/MilitaryPlant/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_POWERPLANT                         Game/Objects/Buildings/PowerPlant/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_PROCESSINGPLANT                    Game/Objects/Buildings/ProcessingPlant/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_SHAFT                              Game/Objects/Buildings/Shaft/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS_WAREHOUSEAMMO                      Game/Objects/Buildings/WarehouseAmmo/*.*)
file(GLOB GAME_OBJECTS_TERRAIN                                      Game/Objects/Terrain/*.*)
file(GLOB GAME_OBJECTS_UNITS                                        Game/Objects/Units/*.*)
file(GLOB GAME_OBJECTS_UNITS_AIRPLANE                               Game/Objects/Units/Airplane/*.*)
file(GLOB GAME_OBJECTS_UNITS_BOMBER                                 Game/Objects/Units/Bomber/*.*)
file(GLOB GAME_OBJECTS_UNITS_BUILDER                                Game/Objects/Units/Builder/*.*)
file(GLOB GAME_OBJECTS_UNITS_HELICOPTER                             Game/Objects/Units/Helicopter/*.*)
file(GLOB GAME_OBJECTS_UNITS_ROBOT                                  Game/Objects/Units/Robot/*.*)
file(GLOB GAME_OBJECTS_UNITS_SUPPLIERAMMO                           Game/Objects/Units/SupplierAmmo/*.*)
file(GLOB GAME_OBJECTS_UNITS_TANK                                   Game/Objects/Units/Tank/*.*)
file(GLOB GAME_OBJECTS_WEAPONS                                      Game/Objects/Weapons/*.*)
file(GLOB GAME_OBJECTS_WEAPONS_GRENADERLAUNCHER                     Game/Objects/Weapons/GrenaderLauncher/*.*)
file(GLOB GAME_OBJECTS_WEAPONS_GUN                                  Game/Objects/Weapons/Gun/*.*)
file(GLOB GAME_OBJECTS_WEAPONS_LASER                                Game/Objects/Weapons/Laser/*.*)
file(GLOB GAME_OBJECTS_WEAPONS_MACHINEGUN                           Game/Objects/Weapons/MacheneGun/*.*)
file(GLOB GAME_OBJECTS_WEAPONS_ROCKETLAUNCHER                       Game/Objects/Weapons/RocketLauncher/*.*)
file(GLOB GAME_PATH                                                 Game/Path/*.*)
file(GLOB GRAPHICS_2D                                               Graphics/2D/*.*)
file(GLOB GRAPHICS_OBJECTS                                          Graphics/Objects/*.*)
file(GLOB GUI                                                       GUI/*.*)
file(GLOB GUI_CONTROLS                           ../../common_files/GUI/Controls/*.*)
file(GLOB GUI_GUIEDITOR                                             GUI/GuiEditor/*.*)
file(GLOB GUI_GAME                                                  GUI/GuiGame/*.*)
file(GLOB GUI_LOGIC                                                 GUI/Logic/*.*)
file(GLOB GUI_MENU                                                  GUI/Menu/*.*)
file(GLOB GUI_PANELS                                                GUI/Panels/*.*)
file(GLOB GUI_WINDOWS                                               GUI/Windows/*.*)
file(GLOB SCENE_CAMERAS                                             Scene/Cameras/*.*)
file(GLOB NETWORK                                                   Network/*.*)

source_group(src                                      FILES ${SRC})
source_group(Core                                     FILES ${CORE})
source_group(Editor                                   FILES ${EDITOR})
source_group(Game                                     FILES ${GAME})
source_group(Game\\Logic                              FILES ${GAME_LOGIC})
source_group(Game\\Objects                            FILES ${GAME_OBJECTS})
source_group(Game\\Objects\\Ammo                      FILES ${GAME_OBJECTS_AMMO})
source_group(Game\\Objects\\Ammo\\AirBomb             FILES ${GAME_OBJECTS_AMMO_AIRBOMB})
source_group(Game\\Objects\\Ammo\\Grenade             FILES ${GAME_OBJECTS_AMMO_GRENADE})
source_group(Game\\Objects\\Ammo\\Mine                FILES ${GAME_OBJECTS_AMMO_MINE})
source_group(Game\\Objects\\Ammo\\Rocket              FILES ${GAME_OBJECTS_AMMO_ROCKET})
source_group(Game\\Objects\\Ammo\\RollingBomb         FILES ${GAME_OBJECTS_AMMO_ROLLINGBOMB})
source_group(Game\\Objects\\Buildings                 FILES ${GAME_OBJECTS_BUILDINGS})
source_group(Game\\Objects\\Buildings\\CivilPlant     FILES ${GAME_OBJECTS_BUILDINGS_CIVILPLANT})
source_group(Game\\Objects\\Buildings\\MilitaryPlant  FILES ${GAME_OBJECTS_BUILDINGS_MILITARYPLANT})
source_group(Game\\Objects\\Buildings\\PowerPlant     FILES ${GAME_OBJECTS_BUILDINGS_POWERPLANT})
source_group(Game\\Objects\\Buildings\\ProcessingPlan FILES ${GAME_OBJECTS_BUILDINGS_PROCESSINGPLANT})
source_group(Game\\Objects\\Buildings\\Shaft          FILES ${GAME_OBJECTS_BUILDINGS_SHAFT})
source_group(Game\\Objects\\Buildings\\WarehouseAmmo  FILES ${GAME_OBJECTS_BUILDINGS_WAREHOUSEAMMO})
source_group(Game\\Objects\\Terrain                   FILES ${GAME_OBJECTS_TERRAIN})
source_group(Game\\Objects\\Units                     FILES ${GAME_OBJECTS_UNITS})
source_group(Game\\Objects\\Units\\Airplane           FILES ${GAME_OBJECTS_UNITS_AIRPLANE})
source_group(Game\\Objects\\Units\\Bomber             FILES ${GAME_OBJECTS_UNITS_BOMBER})
source_group(Game\\Objects\\Units\\Builder            FILES ${GAME_OBJECTS_UNITS_BUILDER})
source_group(Game\\Objects\\Units\\Helicopter         FILES ${GAME_OBJECTS_UNITS_HELICOPTER})
source_group(Game\\Objects\\Units\\Robot              FILES ${GAME_OBJECTS_UNITS_ROBOT})
source_group(Game\\Objects\\Units\\SupplierAmmo       FILES ${GAME_OBJECTS_UNITS_SUPPLIERAMMO})
source_group(Game\\Objects\\Units\\Tank               FILES ${GAME_OBJECTS_UNITS_TANK})
source_group(Game\\Objects\\Weapons                   FILES ${GAME_OBJECTS_WEAPONS})
source_group(Game\\Objects\\Weapons\\GrenadeLauncher  FILES ${GAME_OBJECTS_WEAPONS_GRENADERLAUNCHER})
source_group(Game\\Objects\\Weapons\\Gun              FILES ${GAME_OBJECTS_WEAPONS_GUN})
source_group(Game\\Objects\\Weapons\\Laser            FILES ${GAME_OBJECTS_WEAPONS_LASER})
source_group(Game\\Objects\\Weapons\\MachineGun       FILES ${GAME_OBJECTS_WEAPONS_MACHINEGUN})
source_group(Game\\Objects\\Weapons\\RocketLauncher   FILES ${GAME_OBJECTS_WEAPONS_ROCKETLAUNCHER})
source_group(Game\\Path                               FILES ${GAME_PATH})
source_group(Graphics\\2D                             FILES ${GRAPHICS_2D})
source_group(Graphics\\Objects                        FILES ${GRAPHICS_OBJECTS})
source_group(GUI                                      FILES ${GUI})
source_group(GUI\\Controls                            FILES ${GUI_CONTROLS})
source_group(GUI\\GuiEditor                           FILES ${GUI_GUIEDITOR})
source_group(GUI\\Game                                FILES ${GUI_GAME})
source_group(GUI\\Logic                               FILES ${GUI_LOGIC})
source_group(GUI\\Menu                                FILES ${GUI_MENU})
source_group(GUI\\Panels                              FILES ${GUI_PANELS})
source_group(GUI\\Windows                             FILES ${GUI_WINDOWS})
source_group(Scene\\Cameras                           FILES ${SCENE_CAMERAS})
source_group(Network                                  FILES ${NETWORK})

add_executable( ${PROJECT_NAME} ${SRC} ${CORE} ${EDITOR} ${GAME} ${GAME_LOGIC} ${GAME_OBJECTS} ${GAME_OBJECTS_AMMO}
                ${GAME_OBJECTS_AMMO_AIRBOMB} ${GAME_OBJECTS_AMMO_GRENADE} ${GAME_OBJECTS_AMMO_MINE}
                ${GAME_OBJECTS_AMMO_ROCKET} ${GAME_OBJECTS_AMMO_ROLLINGBOMB} ${GAME_OBJECTS_BUILDINGS}
                ${GAME_OBJECTS_BUILDINGS_CIVILPLANT} ${GAME_OBJECTS_BUILDINGS_MILITARYPLANT}
                ${GAME_OBJECTS_BUILDINGS_POWERPLANT} ${GAME_OBJECTS_BUILDINGS_PROCESSINGPLANT}
                ${GAME_OBJECTS_BUILDINGS_SHAFT} ${GAME_OBJECTS_BUILDINGS_WAREHOUSEAMMO}
                ${GAME_OBJECTS_TERRAIN} ${GAME_OBJECTS_UNITS} ${GAME_OBJECTS_UNITS_AIRPLANE}
                ${GAME_OBJECTS_UNITS_BOMBER} ${GAME_OBJECTS_UNITS_BUILDER} ${GAME_OBJECTS_UNITS_HELICOPTER}
                ${GAME_OBJECTS_UNITS_ROBOT} ${GAME_OBJECTS_UNITS_SUPPLIERAMMO} ${GAME_OBJECTS_UNITS_TANK}
                ${GAME_OBJECTS_WEAPONS} ${GAME_OBJECTS_WEAPONS_GRENADERLAUNCHER} ${GAME_OBJECTS_WEAPONS_GUN}
                ${GAME_OBJECTS_WEAPONS_LASER} ${GAME_OBJECTS_WEAPONS_MACHINEGUN} ${GAME_OBJECTS_WEAPONS_ROCKETLAUNCHER}
                ${GAME_PATH} ${GRAPHICS_2D} ${GRAPHICS_OBJECTS} ${GUI} ${GUI_CONTROLS} ${GUI_GUIEDITOR} ${GUI_GAME}
                ${GUI_LOGIC} ${GUI_MENU} ${GUI_PANELS} ${GUI_WINDOWS} ${SCENE_CAMERAS} ${NETWORK})

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
