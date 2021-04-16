project(sqlite)

file(GLOB SRC src/*.h src/*.c)

source_group(src FILES${SRC})

add_library( ${PROJECT_NAME} ${SRC} )

if(WIN32)

    include(../../RuntimeLibrary.cmake)      # Исключаем зависимости от динамических библиотек VS времени
                                             # выполнения релизной версии

else()

    set(LDFLAGS "${LDFLAGS} -ldl")
    target_link_libraries(${PROJECT_NAME} dl pthread)

endif()

# SQLite will not work correctly with the -ffast-math option, so unset it in this scope only
string (REPLACE -ffast-math "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")    # Stringify for string replacement
