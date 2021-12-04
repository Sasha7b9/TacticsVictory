project(TacticsVictory)

message("-------------------------------------------------------------------------------------------------- ${PROJECT_NAME}")

set(TARGET_NAME TacticsVictory)

set(_INSTALL_DIR_ ${_ROOT_DIR_}\\${TARGET_NAME}\\out\\${BUILD_TYPE})
if(WIN32)
	file(TO_NATIVE_PATH ${_INSTALL_DIR_} _INSTALL_DIR_)
else()
	get_filename_component(_INSTALL_DIR_ ${_INSTALL_DIR_} ABSOLUTE)
endif()

function(add_subdirectory_with_folder _folder_name _folder)
    add_subdirectory(${_folder} ${ARGN})
    set_property(DIRECTORY "${_folder}" PROPERTY FOLDER "${_folder_name}")
endfunction()


add_subdirectory_with_folder("TacticsVictory/common" common/Battle    )

