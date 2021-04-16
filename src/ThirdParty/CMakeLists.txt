cmake_minimum_required(VERSION 2.8.12)

# Libraries linked via full path no longer produce linker search paths
cmake_policy (SET CMP0003 NEW)
# INTERFACE_LINK_LIBRARIES defines the link interface
cmake_policy (SET CMP0022 NEW)
# MACOSX_RPATH is enabled by default
cmake_policy (SET CMP0042 NEW)
# MSVC runtime library flags are selected an abstraction
cmake_policy(SET CMP0091 NEW)

project (ThirdParty)

set (TARGET_NAME ThirdParty)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(SUB_DIR debug)
    add_definitions(-DDEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(SUB_DIR release)
endif()

set(OUT_DIR $ENV{PROJECT_DIR}\\out\\${SUB_DIR})

set(CMAKE_CXX_STANDARD 17)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

else()

    add_definitions(-m64 -msse -msse2 -pthread -fno-strict-aliasing -fmax-errors=1 -Wall)

    set(LDFLAGS "${LDFLAGS} -ldl")

    if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        add_definitions(-O0)
    else()
        add_definitions(-O3)
    endif()

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

add_subdirectory_with_folder("sqlite" sqlite)
