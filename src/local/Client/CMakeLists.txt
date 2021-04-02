project (Client)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS  /STACK:100000000")

set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                # base class copy constructor is inaccessible or deleted
add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                # base class assignment operator is inaccessible or deleted
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4710)    # 'function' : function not inlined
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'type': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified
add_compile_options(/wd5219)    # implicit conversion from 'type-1' to 'type-2', possible loss of data
add_compile_options(/wd26812)   # Prefer 'enum class' over 'enum'
add_compile_options(/wd28251)   # Inconsistent annotation for function: this instance has an error


file(GLOB SRC       ../../common_files/*.*
                                       *.h *.cpp)

source_group(src    FILES ${SRC})

add_executable( ${PROJECT_NAME} ${SRC})

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
