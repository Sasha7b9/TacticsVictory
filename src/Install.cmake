if(WIN32)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_BINARY_DIR}/../out/${SUB_DIR}")
endif()
