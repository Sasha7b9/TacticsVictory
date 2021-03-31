cmake_minimum_required(VERSION 3.20)


# Libraries linked via full path no longer produce linker search paths
cmake_policy (SET CMP0003 NEW)

# link_directories() treats paths relative to the source dir.
cmake_policy (SET CMP0015 NEW)

# MSVC runtime library flags are selected an abstraction
cmake_policy(SET CMP0091 NEW)

project (VictoryU3D)

set (TARGET_NAME VictoryU3D)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(SUB_DIR debug)
    add_definitions(-DDEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(SUB_DIR release)
endif()

set(OUT_DIR $ENV{PROJECT_DIR}\\out\\${SUB_DIR})

link_directories(../../Urho3D/generated/${SUB_DIR}/lib
                 ../generated/${SUB_DIR}/ThirdParty/sockpp_/sockpp/${CMAKE_BUILD_TYPE})

# set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall /std:c++17")
else()
    add_definitions(-m64 -msse -msse2 -pthread -ffast-math -fno-strict-aliasing -fmax-errors=1 -Wall)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
define_property(
    TARGET
    PROPERTY FOLDER
    INHERITED
    BRIEF_DOCS "Set the folder name."
    FULL_DOCS "Use to organize targets in an IDE."
)

function(add_subdirectory_with_folder _folder_name _folder)
    add_subdirectory(${_folder} ${ARGN})
    set_property(DIRECTORY "${_folder}" PROPERTY FOLDER "${_folder_name}")
endfunction()


if(WIN32)
    add_subdirectory_with_folder("local" local/BattlerTV)
endif()

add_subdirectory_with_folder("common" common/BattleTV)
add_subdirectory_with_folder("remote" remote/Master)
