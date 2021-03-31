
if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL Release)        # Для релизной версии
        message("...................................................MultiThreaded")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        message("...................................................MultiThreadedDebugDLL")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
endif()
