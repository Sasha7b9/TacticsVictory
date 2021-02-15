
if(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL Release)        # Для релизной версии
        message("............................... Release mode")
        set_property(TARGET ${PROJECT_NAME} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded")   # Устанавливаем статическую линковку рантайм-библиотек
    elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug)
        message("............................... Debug mode")
        set_property(TARGET ${PROJECT_NAME} PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif()
endif()
