project (Battle)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../libs/victory
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DU3D)

if(WIN32)

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

else()

    add_compile_options(-Wclobbered)
    add_compile_options(-Wempty-body)
    add_compile_options(-Wignored-qualifiers)
    add_compile_options(-Wmissing-field-initializers)
    add_compile_options(-Wsign-compare)
    add_compile_options(-Wtype-limits)
    add_compile_options(-Wuninitialized)
    add_compile_options(-Wunused-parameter)

endif()

file(GLOB SRC                                    ../../common_files/*.*
                                                                    *.h *.cpp)
file(GLOB CORE                                   ../../common_files/Core/*.*)
file(GLOB FILE_SYSTEM                            ../../common_files/FileSystem/ConfigurationFile_.*
                                                 ../../common_files/FileSystem/FileSystem_.*)
file(GLOB GAME_LOGIC                             ../../common_files/Game/Logic/*.*)
file(GLOB GAME_PATH                              ../../common_files/Game/Path/*.*)
file(GLOB NETWORK                                ../../common_files/Network/Game/*.*
                                                                    Network/*.*)
file(GLOB NETWORK_MESSAGES                       ../../common_files/Network/Game/Messages/*.*
                                                                    Network/Messages/*.*)
file(GLOB NETWORK_OTHER                          ../../common_files/Network/Other/MasterServer_.*)
file(GLOB SCENE                                  ../../common_files/Scene/*.*
                                                                    Scene/*.*)
file(GLOB SCENE_OBJECTS                          ../../common_files/Scene/Objects/*.*
                                                                    Scene/Objects/*.*)
file(GLOB SCENE_OBJECTS_AMMO                     ../../common_files/Scene/Objects/Ammo/*.*)
file(GLOB SCENE_OBJECTS_AMMO_ROCKET              ../../common_files/Scene/Objects/Ammo/Rocket/*.*)
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
file(GLOB UTILS                                  ../../libs/victory/Utils/Log_.h
                                                 ../../common_files/Utils/LogU3D_.*
                                                 ../../common_files/Utils/StringUtils_.*
                                                 ../../common_files/Utils/UtilsOS_.*
                                                 ../../common_files/Utils/GlobalFunctions_.*)

source_group(src                                        FILES ${SRC})
source_group(Core                                       FILES ${CORE})
source_group(FileSystem                                 FILES ${FILE_SYSTEM})
source_group(Game\\Logic                                FILES ${GAME_LOGIC})
source_group(Game\\Path                                 FILES ${GAME_PATH})
source_group(Network                                    FILES ${NETWORK})
source_group(Network\\Messages                          FILES ${NETWORK_MESSAGES})
source_group(Network\\Other                             FILES ${NETWORK_OTHER})
source_group(Scene                                      FILES ${SCENE})
source_group(Scene\\Objects                             FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Ammo                       FILES ${SCENE_OBJECTS_AMMO})
source_group(Scene\\Objects\\Ammo\\Rocket               FILES ${SCENE_OBJECTS_AMMO_ROCKET})
source_group(Scene\\Objects\\Buildings                  FILES ${SCENE_OBJECTS_BUILDINGS})
source_group(Scene\\Objects\\Units                      FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Accessories         FILES ${SCENE_OBJECTS_UNITS_ACCESSORIES})
source_group(Scene\\Objects\\Units\\Accessories\\Engine FILES ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE})
source_group(Scene\\Objects\\Units\\Air                 FILES ${SCENE_OBJECTS_UNITS_AIR})
source_group(Scene\\Objects\\Units\\Air\\AirPlane       FILES ${SCENE_OBJECTS_UNITS_AIR_AIRPLANE})
source_group(Scene\\Objects\\Units\\Ground              FILES ${SCENE_OBJECTS_UNITS_GROUND})
source_group(Scene\\Objects\\Units\\Ground\\Tank        FILES ${SCENE_OBJECTS_UNITS_GROUND_TANK})
source_group(Scene\\Objects\\Weapons                    FILES ${SCENE_OBJECTS_WEAPONS})
source_group(Scene\\Primitives                          FILES ${SCENE_PRIMITIVES})
source_group(Scene\\Terrain                             FILES ${SCENE_TERRAIN})
source_group(Utils                                      FILES ${UTILS})

file(GLOB FILES_UNITY ${SRC} ${CORE} ${FILE_SYSTEM} ${GAME_LOGIC} ${GAME_PATH}
                      ${NETWORK} ${NETWORK_MESSAGES} ${NETWORK_OTHER}
                      ${SCENE} ${SCENE_OBJECTS}
                      ${SCENE_OBJECTS_AMMO} ${SCENE_OBJECTS_AMMO_ROCKET}
                      ${SCENE_OBJECTS_BUILDINGS}
                      ${SCENE_OBJECTS_UNITS}
                      ${SCENE_OBJECTS_UNITS_ACCESSORIES} ${SCENE_OBJECTS_UNITS_ACCESSORIES_ENGINE}
                      ${SCENE_OBJECTS_UNITS_AIR} ${SCENE_OBJECTS_UNITS_AIR_AIRPLANE}
                      ${SCENE_OBJECTS_UNITS_GROUND} ${SCENE_OBJECTS_UNITS_GROUND_TANK}
                      ${SCENE_OBJECTS_WEAPONS} ${SCENE_PRIMITIVES} ${SCENE_TERRAIN} ${UTILS})

add_executable(${PROJECT_NAME} ${FILES_UNITY})

set_target_properties(${PROJECT_NAME}       PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${FILES_UNITY}  PROPERTIES UNITY_GROUP "battle")

include(../../RuntimeLibrary.cmake)

if(WIN32)

    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        target_link_libraries(${PROJECT_NAME} Urho3D_d) 
    else()
        target_link_libraries(${PROJECT_NAME} Urho3D)
    endif()

    target_link_libraries(${PROJECT_NAME} ws2_32)

else()

    target_link_libraries(${PROJECT_NAME} Urho3D)

endif()

target_link_libraries(${PROJECT_NAME} victory)

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
