
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND copy "$(OutputPath)${PROJECT_NAME}.exe" ${OUT_DIR} /Y
    )
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND copy "$(OutputPath)${PROJECT_NAME}" ${OUT_DIR}
    )
endif()
