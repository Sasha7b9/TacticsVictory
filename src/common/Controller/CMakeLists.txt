project (Controller)


set(CMAKE_UNITY_BUILD ON)


include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../ThirdParty/rapidjson/include)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified

else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC       *.h *.cpp)

file(GLOB RAPIDJSON                       ../../ThirdParty/rapidjson/include/rapidjson/*.*)
file(GLOB RAPIDJSON_ERROR                 ../../ThirdParty/rapidjson/include/rapidjson/error/*.*)
file(GLOB RAPIDJSON_INTERNAL              ../../ThirdParty/rapidjson/include/rapidjson/internal/*.*)
file(GLOB RAPIDJSON_MSINTTYPES            ../../ThirdParty/rapidjson/include/rapidjson/msinttypes/*.*)
file(GLOB SOCKPP                                ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES                  ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE                  ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src    FILES ${SRC})

source_group(ThirdParty\\rapidjson             FILES ${RAPIDJSON})
source_group(ThirdParty\\rapidjson\\error      FILES ${RAPIDJSON_ERROR})
source_group(ThirdParty\\rapidjson\\internal   FILES ${RAPIDJSON_INTERNAL})
source_group(ThirdParty\\rapidjson\\msinttypes FILES ${RAPIDJSON_MSINTTYPES})
source_group(ThirdParty\\sockpp                FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources       FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include       FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(${PROJECT_NAME} ${SRC}
                ${RAPIDJSON} ${RAPIDJSON_ERROR} ${RAPIDJSON_INTERNAL} ${RAPIDJSON_MSINTTYPES}
                ${SOCKPP} ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

if(WIN32)
    include(../../CopyToDirEXE.cmake)
    include(../../SetWorkingDirectory.cmake)

    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
