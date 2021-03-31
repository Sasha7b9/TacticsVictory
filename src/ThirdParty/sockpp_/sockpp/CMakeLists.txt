cmake_minimum_required(VERSION 3.0)

project(sockpp VERSION "0.7.0")

include_directories(include)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

source_group(src REGULAR_EXPRESSION src/*)

file(GLOB SOURCES src/*)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

include(../../../RuntimeLibrary.cmake)

add_definitions(-DCOMPILE_LIBRARY)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

install(TARGETS ${PROJECT_NAME}
    ARCHIVE
        DESTINATION ${CMAKE_BINARY_DIR}/bin
)
