cmake_minimum_required(VERSION 2.4)


# Libraries linked via full path no longer produce linker search paths
cmake_policy (SET CMP0003 NEW)

# INTERFACE_LINK_LIBRARIES defines the link interface
cmake_policy (SET CMP0022 NEW)

# MACOSX_RPATH is enabled by default
cmake_policy (SET CMP0042 NEW)

cmake_policy(SET CMP0091 NEW)

# Set project name
project (ThirdParty)

set(CMAKE_CXX_STANDARD 17)
set (TARGET_NAME ThirdParty)
set (PROGECT_TANKIST_DIR /home/sasha/TankistU3D)

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

add_subdirectory_with_folder("sockpp_" sockpp_/sockpp)
