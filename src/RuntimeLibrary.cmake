
if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL Release)        # Для релизной версии
        message("...................................................MultiThreaded")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
#        set_property(TARGET ${PROJECT_NAME} PROPERTY
#            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")   # Устанавливаем статическую линковку рантайм-библиотек
    elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        message("...................................................MultiThreadedDebugDLL")
        set_property(TARGET ${PROJECT_NAME} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
endif()
