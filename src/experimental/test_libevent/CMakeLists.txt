project (test_libevent)

include_directories(.
                    ../../ThirdParty/libevent/compat
                    ../../ThirdParty/libevent/include
                    ../../ThirdParty/libevent/build/include)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

add_definitions(-DHAVE_CONFIG_H)

add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a
                                # base class copy constructor is inaccessible or deleted
add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a
                                # base class assignment operator is inaccessible or deleted
add_compile_options(/wd4710)    # 'function' : function not inlined
add_compile_options(/wd4711)    # function 'function' selected for inline expansion
add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
add_compile_options(/wd5026)    # 'type': move constructor was implicitly defined as deleted
add_compile_options(/wd5027)    # 'type': move assignment operator was implicitly defined as deleted
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch
                                # specified

add_compile_options(/wd4244)
add_compile_options(/wd4996)

file(GLOB SRC       *.h *.c
                    ../../ThirdParty/libevent/buffer.c
                    ../../ThirdParty/libevent/buffer_iocp.c
                    ../../ThirdParty/libevent/bufferevent.c
                    ../../ThirdParty/libevent/bufferevent_async.c
                    ../../ThirdParty/libevent/bufferevent_filter.c
                    ../../ThirdParty/libevent/bufferevent_pair.c
                    ../../ThirdParty/libevent/bufferevent_ratelim.c
                    ../../ThirdParty/libevent/bufferevent_sock.c
                    ../../ThirdParty/libevent/epoll.c
                    ../../ThirdParty/libevent/event.c
                    ../../ThirdParty/libevent/event_iocp.c
                    ../../ThirdParty/libevent/evmap.c
                    ../../ThirdParty/libevent/evthread.c
                    ../../ThirdParty/libevent/evutil.c
                    ../../ThirdParty/libevent/evutil_rand.c
                    ../../ThirdParty/libevent/evutil_time.c
                    ../../ThirdParty/libevent/listener.c
                    ../../ThirdParty/libevent/log.c
                    ../../ThirdParty/libevent/signal.c
                    ../../ThirdParty/libevent/strlcpy.c
                    ../../ThirdParty/libevent/wepoll.c
                    ../../ThirdParty/libevent/win32select.c)

source_group(src            FILES ${SRC})

add_executable( ${PROJECT_NAME} ${SRC} )

target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi bcrypt)
