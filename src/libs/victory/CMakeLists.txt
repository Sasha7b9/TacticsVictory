project (victory)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../ThirdParty/libevent/compat
                    ../../ThirdParty/libevent/include
                    ../../ThirdParty/libevent/build/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_STATIC_DEFINE -DEVENT__HAVE_SA_FAMILY_T -DHAVE_CONFIG_H -DTINYTEST_LOCAL -DU3D -DGRAPHICS)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /FORCE:MULTIPLE")

    add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
    add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                    # base class copy constructor is inaccessible or deleted
    add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                    # base class assignment operator is inaccessible or deleted
    add_compile_options(/wd4710)    # 'function' : function not inlined
    add_compile_options(/wd4711)    # function 'function' selected for inline expansion
    add_compile_options(/wd4820)    # bytes' bytes padding added after construct 'member_name'
    add_compile_options(/wd5026)    # 'xxx': move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # 'class': move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                    # specified
    add_compile_options(/wd5220)    # 'xxx:yyy': a non-static data member with a volatile qualified type no longer
                                    # implies that compiler generated copy/move constructors and copy/move assignment
                                    # operators are not trivial

else()

endif()

file(GLOB SRC                                  *.h *.cpp)
file(GLOB CORE                                 Core/*.*)
file(GLOB FILESYSTEM                           FileSystem/*.*)
file(GLOB INPUT                                Input/*.*)
file(GLOB NETWORK                              Network/Other/*.*)
file(GLOB UTILS                                Utils/*.*)

file(GLOB LIBEVENT           ../../ThirdParty/libevent/libevent_bucket*.c)
file(GLOB SOCKPP                   ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES     ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE     ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src                         FILES ${SRC})
source_group(Core                        FILES ${CORE})
source_group(FileSystem                  FILES ${FILESYSTEM})
source_group(Input                       FILES ${INPUT})
source_group(Network                     FILES ${NETWORK})
source_group(Utils                       FILES ${UTILS})

source_group(ThirdParty\\libevent        FILES ${LIBEVENT})
source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

file(GLOB FILES_UNITY   ${SRC})
file(GLOB FILES_UNITY_2 ${CORE})
file(GLOB FILES_UNITY_3 ${FILESYSTEM})
file(GLOB FILES_UNITY_4 ${INPUT})
file(GLOB FILES_UNITY_5 ${NETWORK})
file(GLOB FILES_UNITY_6 ${UTILS})
file(GLOB FILES_UNITY_7 ${SOCKPP})

add_library(${PROJECT_NAME} ${FILES_UNITY} ${FILES_UNITY_2} ${FILES_UNITY_3} ${FILES_UNITY_4} ${FILES_UNITY_5}
            ${FILES_UNITY_6} ${FILES_UNITY_7} ${LIBEVENT})

set_target_properties(${PROJECT_NAME}        PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${FILES_UNITY}   PROPERTIES UNITY_GROUP "victory")
set_source_files_properties(${FILES_UNITY_2} PROPERTIES UNITY_GROUP "victory2")
set_source_files_properties(${FILES_UNITY_3} PROPERTIES UNITY_GROUP "victory3")
set_source_files_properties(${FILES_UNITY_4} PROPERTIES UNITY_GROUP "victory4")
set_source_files_properties(${FILES_UNITY_5} PROPERTIES UNITY_GROUP "victory5")
set_source_files_properties(${FILES_UNITY_6} PROPERTIES UNITY_GROUP "victory6")
set_source_files_properties(${FILES_UNITY_7} PROPERTIES UNITY_GROUP "victory7")

if(WIN32)

    include(../../RuntimeLibrary.cmake)      # »сключаем зависимости от динамических библиотек VS времени
                                             # выполнени€ релизной версии
    include(../../SetWorkingDirectory.cmake)
    target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi bcrypt)

else()

    target_link_libraries(${PROJECT_NAME} Urho3D pthread)

endif()

include(../../Install.cmake)
