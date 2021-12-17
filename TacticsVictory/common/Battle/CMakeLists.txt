project (TVPiBattle)

message("-------------------------------------------------------------------------------------------------- ${PROJECT_NAME}")


#set(CMAKE_UNITY_BUILD OFF)


include_directories(.
                    ${_ROOT_DIR_}/src/PiEngine/Engine)

if(MSVC)
    add_definitions(
        -D__PLACEMENT_NEW_INLINE        # без этого ругается на placement operator new
        -D__PLACEMENT_VEC_NEW_INLINE    # без этого ругается на placement operator new
    )

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:1000000000")
endif()

file(GLOB SRC                                              *.h *.*c*)
file(GLOB GRAPHICS                                         Graphics/*.*)
file(GLOB GRAPHICS_GEOMETRY                                Graphics/Geometry/*.*)
file(GLOB GRAPHICS_MESHES                                  Graphics/Meshes/*.*)
file(GLOB GRAPHICS_TEXTURES                                Graphics/Textures/*.*)
file(GLOB GUI                                              GUI/*.*)
file(GLOB GUI_MUTATORS                                     GUI/Mutators/*.*)
file(GLOB GUI_PANELS                                       GUI/Panels/*.*)
file(GLOB GUI_WIDGETS                                      GUI/Widgets/*.*)
file(GLOB INPUT                                            Input/*.*)
file(GLOB OBJECTS                                          Objects/*.*)
file(GLOB OBJECTS_AMMO                                     Objects/Ammo/*.*)
file(GLOB OBJECTS_STRUCTURES                               Objects/Structures/*.*)
file(GLOB OBJECTS_UNITS                                    Objects/Units/*.*)
file(GLOB OBJECTS_UNITS_AIR                                Objects/Units/Air/*.*)
file(GLOB OBJECTS_UNITS_GROUND                             Objects/Units/Ground/*.*)
file(GLOB OBJECTS_UNITS_WATER                              Objects/Units/Water/*.*)
file(GLOB OBJECTS_UNITS_UNITLOGIC                          Objects/Units/UnitLogic/*.*)
file(GLOB OBJECTS_UNITS_PATHFINDER                         Objects/Units/PathFinder/*.*)
file(GLOB OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER       Objects/Units/PathFinder/NavmeshController/*.*)
file(GLOB OBJECTS_UNITS_SELECTOR                           Objects/Units/Selector/*.*)
file(GLOB OBJECTS_WEAPONS                                  Objects/Weapons/*.*)
file(GLOB SCENE                                            Scene/*.*)
file(GLOB SCENE_CAMERAS                                    Scene/Cameras/*.*)
file(GLOB SCENE_WORLD                                      Scene/World/*.*)
file(GLOB SHADERS                                          Shaders/*.*)
file(GLOB SOUNDS                                           Sounds/*.*)
file(GLOB SYSTEM                                           System/*.*)
file(GLOB UTILS                                            Utils/*.*)
#file(GLOB EXPERIMENTS                                      Experiments/*.*)


source_group(src                                                  FILES ${SRC})
source_group(Graphics                                             FILES ${GRAPHICS})
source_group(Graphics\\Geometry                                   FILES ${GRAPHICS_GEOMETRY})
source_group(Graphics\\Meshes                                     FILES ${GRAPHICS_MESHES})
source_group(Graphics\\Textures                                   FILES ${GRAPHICS_TEXTURES})
source_group(GUI                                                  FILES ${GUI})
source_group(GUI\\Mutators                                        FILES ${GUI_MUTATORS})
source_group(GUI\\Panels                                          FILES ${GUI_PANELS})
source_group(GUI\\Widgets                                         FILES ${GUI_WIDGETS})
source_group(Input                                                FILES ${INPUT})
source_group(Objects                                              FILES ${OBJECTS})
source_group(Objects\\Ammo                                        FILES ${OBJECTS_AMMO})
source_group(Objects\\Structures                                  FILES ${OBJECTS_STRUCTURES})
source_group(Objects\\Units                                       FILES ${OBJECTS_UNITS})
source_group(Objects\\Units\\Air                                  FILES ${OBJECTS_UNITS_AIR})
source_group(Objects\\Units\\Ground                               FILES ${OBJECTS_UNITS_GROUND})
source_group(Objects\\Units\\Water                                FILES ${OBJECTS_UNITS_WATER})
source_group(Objects\\Units\\UnitLogic                            FILES ${OBJECTS_UNITS_UNITLOGIC})
source_group(Objects\\Units\\PathFinder                           FILES ${OBJECTS_UNITS_PATHFINDER})
source_group(Objects\\Units\\PathFinder\\NavmeshController        FILES ${OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER})
source_group(Objects\\Units\\Selection                            FILES ${OBJECTS_UNITS_SELECTOR})
source_group(Objects\\Weapons                                     FILES ${OBJECTS_WEAPONS})
source_group(Scene                                                FILES ${SCENE})
source_group(Scene\\Cameras                                       FILES ${SCENE_CAMERAS})
source_group(Scene\\World                                         FILES ${SCENE_WORLD})
source_group(Shaders                                              FILES ${SHADERS})
source_group(Sounds                                               FILES ${SOUNDS})
source_group(System                                               FILES ${SYSTEM})
source_group(Utils                                                FILES ${UTILS})
#source_group(Experiments                                          FILES ${EXPERIMENTS})

set_source_files_properties(${OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER} PROPERTIES HEADER_FILE_ONLY TRUE)

#set_source_files_properties(Utils/Array2D.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)

add_executable(${PROJECT_NAME} ${SRC} ${GRAPHICS} ${GRAPHICS_GEOMETRY} ${GRAPHICS_MESHES}
                               ${GRAPHICS_TEXTURES} ${GUI} ${GUI_MUTATORS} ${GUI_PANELS} ${GUI_WIDGETS}
                               ${INPUT} ${SCENE} ${SCENE_CAMERAS} ${OBJECTS} ${OBJECTS_AMMO}
                               ${OBJECTS_STRUCTURES} ${OBJECTS_UNITS} ${OBJECTS_UNITS_AIR}
                               ${OBJECTS_UNITS_GROUND} ${OBJECTS_UNITS_WATER} ${OBJECTS_UNITS_UNITLOGIC}
                               ${OBJECTS_UNITS_PATHFINDER} ${OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER}
                               ${OBJECTS_UNITS_SELECTOR} ${OBJECTS_WEAPONS}
                               ${SCENE_WORLD} ${SHADERS} ${SOUNDS} ${SYSTEM} ${UTILS}
#                               ${EXPERIMENTS}
                               )

tune_precopiled_header()

link_runtime()

target_link_libraries(${PROJECT_NAME} PiEngine)

copy_to_dir_exe($(OutputPath)${PROJECT_NAME} ${_INSTALL_DIR_})

set_work_directory()

message("CMAKE_BINARY_DIR:         ${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_SOURCE_DIR:         ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR:       ${PROJECT_BINARY_DIR}")
message("PROJECT_SOURCE_DIR:       ${PROJECT_SOURCE_DIR}")
message("CMAKE_MODULE_PATH:        ${CMAKE_MODULE_PATH}")
message("CMAKE_COMMAND:            ${CMAKE_COMMAND}")
#message("CMAKE_ROOT:               ${CMAKE_ROOT}")
#message("CMAKE_SYSTEM:             ${CMAKE_SYSTEM}")
#message("CMAKE_SYSTEM_VERSION:     ${CMAKE_SYSTEM_VERSION}")
#message("CMAKE_SYSTEM_PROCESSOR:   ${CMAKE_SYSTEM_PROCESSOR}")
#message("CMAKE_SKIP_RPATH:         ${CMAKE_SKIP_RPATH}")
#message("CMAKE_VERBOSE_MAKEFILE:   ${CMAKE_VERBOSE_MAKEFILE}")
#message("CMAKE_CXX_FLAGS:          ${CMAKE_CXX_FLAGS}")
#message("CMAKE_BUILD_TYPE:         ${CMAKE_BUILD_TYPE}")
#message("CMAKE_C_COMPILER:         ${CMAKE_C_COMPILER} (id ${CMAKE_C_COMPILER_ID}, clang ${CLANG}, GNUC ${GNUC})")
