project (Master)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/libevent/compat
                    ../../ThirdParty/libevent/include
                    ../../ThirdParty/libevent/build/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_STATIC_DEFINE -DEVENT__HAVE_SA_FAMILY_T -DHAVE_CONFIG_H -DTINYTEST_LOCAL)

if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

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

    add_compile_options(-Wclobbered)
    add_compile_options(-Wempty-body)
    add_compile_options(-Wignored-qualifiers)
    add_compile_options(-Wmissing-field-initializers)
    add_compile_options(-Wsign-compare)
    add_compile_options(-Wtype-limits)
    add_compile_options(-Wuninitialized)
    add_compile_options(-Wunused-parameter)

endif()

file(GLOB SRC                 ../../common_files/defines_.h
                                                *.cpp
                                                *.h)
file(GLOB FILE_SYSTEM         ../../common_files/FileSystem/ConfigurationFile_.*
                              ../../common_files/FileSystem/FileSystem_.*)
file(GLOB NETWORK             ../../common_files/Network/Other/NetworkTypes_.*
                              ../../common_files/Network/Other/ServerTCP_.*
                                                 Network/ServerHandlers.cpp)
file(GLOB UTILS               ../../common_files/Utils/Log_.*
                              ../../common_files/Utils/LogRAW_.*
                              ../../common_files/Utils/StringUtils_.*
                              ../../common_files/Utils/UtilsOS_.*)
file(GLOB THIRDPARTY_LIBEVENT ../../ThirdParty/libevent/libevent_bucket*.c)


source_group(src                  FILES ${SRC})
source_group(FileSystem           FILES ${FILE_SYSTEM})
source_group(Network              FILES ${NETWORK})
source_group(Utils                FILES ${UTILS})
source_group(ThirdParty\\libevent FILES ${THIRDPARTY_LIBEVENT})

add_executable(${PROJECT_NAME} ${SRC} ${FILE_SYSTEM} ${NETWORK} ${UTILS} ${THIRDPARTY_LIBEVENT})

set_target_properties(${PROJECT_NAME}                                 PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${SRC} ${FILE_SYSTEM} ${NETWORK} ${UTILS} PROPERTIES UNITY_GROUP "master")

if(WIN32)

    include(../../RuntimeLibrary.cmake)      # »сключаем зависимости от динамических библиотек VS времени
                                             # выполнени€ релизной версии
    include(../../CopyToDirEXE.cmake)
    include(../../SetWorkingDirectory.cmake)
    target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi bcrypt)

else()

endif()

include(../../Install.cmake)
