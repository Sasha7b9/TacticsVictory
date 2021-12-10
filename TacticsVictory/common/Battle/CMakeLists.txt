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

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:100000000")
endif()

file(GLOB SRC                                              *.h *.*c*)
file(GLOB GUI                                              GUI/*.*)
file(GLOB GUI_MUTATORS                                     GUI/Mutators/*.*)
file(GLOB GUI_PANELS                                       GUI/Panels/*.*)
file(GLOB GUI_WIDGETS                                      GUI/Widgets/*.*)
file(GLOB INPUT                                            Input/*.*)
file(GLOB SCENE                                            Scene/*.*)
file(GLOB SCENE_CAMERAS                                    Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS                                    Scene/Objects/*.*)
file(GLOB SCENE_OBJECTS_UNITS                              Scene/Objects/Units/*.*)
file(GLOB SCENE_OBJECTS_UNITS_GROUND                       Scene/Objects/Units/Ground/*.*)
file(GLOB SCENE_OBJECTS_UNITS_PATHFINDER                   Scene/Objects/Units/PathFinder/*.*)
file(GLOB SCENE_OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER Scene/Objects/Units/PathFinder/NavmeshController/*.*)
file(GLOB SCENE_WORLD                                      Scene/World/*.*)
file(GLOB SHADERS                                          Shaders/*.*)
file(GLOB SOUNDS                                           Sounds/*.*)
file(GLOB SYSTEM                                           System/*.*)
file(GLOB UTILS                                            Utils/*.*)
file(GLOB _RESOURCES                                       _resources/*.*)
#file(GLOB EXPERIMENTS                                      Experiments/*.*)


source_group(src                                                  FILES ${SRC})
source_group(GUI                                                  FILES ${GUI})
source_group(GUI\\Mutators                                        FILES ${GUI_MUTATORS})
source_group(GUI\\Panels                                          FILES ${GUI_PANELS})
source_group(GUI\\Widgets                                         FILES ${GUI_WIDGETS})
source_group(Input                                                FILES ${INPUT})
source_group(Scene                                                FILES ${SCENE})
source_group(Scene\\Cameras                                       FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects                                       FILES ${SCENE_OBJECTS})
source_group(Scene\\Objects\\Units                                FILES ${SCENE_OBJECTS_UNITS})
source_group(Scene\\Objects\\Units\\Ground                        FILES ${SCENE_OBJECTS_UNITS_GROUND})
source_group(Scene\\Objects\\Units\\PathFinder                    FILES ${SCENE_OBJECTS_UNITS_PATHFINDER})
source_group(Scene\\Objects\\Units\\PathFinder\\NavmeshController FILES ${SCENE_OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER})
source_group(Scene\\World                                         FILES ${SCENE_WORLD})
source_group(Shaders                                              FILES ${SHADERS})
source_group(Sounds                                               FILES ${SOUNDS})
source_group(System                                               FILES ${SYSTEM})
source_group(Utils                                                FILES ${UTILS})
source_group(_resources                                           FILES ${_RESOURCES})
#source_group(Experiments                                          FILES ${EXPERIMENTS})

set_source_files_properties(${SCENE_OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER} PROPERTIES HEADER_FILE_ONLY TRUE)

#set_source_files_properties(Utils/Array2D.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)

add_executable(${PROJECT_NAME} ${SRC} ${GUI} ${GUI_MUTATORS} ${GUI_PANELS} ${GUI_WIDGETS} ${INPUT}
                               ${SCENE} ${SCENE_CAMERAS} ${SCENE_OBJECTS} ${SCENE_OBJECTS_UNITS}
                               ${SCENE_OBJECTS_UNITS_GROUND} ${SCENE_OBJECTS_UNITS_PATHFINDER}
                               ${SCENE_OBJECTS_UNITS_PATHFINDER_NAVMESHCONTROLLER}
                               ${SCENE_WORLD} ${SHADERS} ${SOUNDS} ${SYSTEM} ${UTILS}
                               ${_RESOURCES}
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
message("CMAKE_ROOT:               ${CMAKE_ROOT}")
message("CMAKE_SYSTEM:             ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_VERSION:     ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_SYSTEM_PROCESSOR:   ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_SKIP_RPATH:         ${CMAKE_SKIP_RPATH}")
#message("CMAKE_VERBOSE_MAKEFILE:   ${CMAKE_VERBOSE_MAKEFILE}")
#message("CMAKE_CXX_FLAGS:          ${CMAKE_CXX_FLAGS}")
#message("CMAKE_BUILD_TYPE:         ${CMAKE_BUILD_TYPE}")
#message("CMAKE_C_COMPILER:         ${CMAKE_C_COMPILER} (id ${CMAKE_C_COMPILER_ID}, clang ${CLANG}, GNUC ${GNUC})")
