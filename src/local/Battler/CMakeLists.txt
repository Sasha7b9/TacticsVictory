project (Battler)

include_directories(.
                    ../../common_files
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DCLIENT)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
else()
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -lGL -lGLX -lX11 -lGLdispatch")
    SET(LDFLAGS "${LDFLAGS} -ldl")
endif()

file(GLOB SRC                    *.h *.cpp)
file(GLOB CORE                   Core/*.*)
file(GLOB EDITOR                 Editor/*.*)
file(GLOB GAME                   Game/*.*)
file(GLOB GAME_LOGIC             Game/Logic/*.*)
file(GLOB GAME_OBJECTS           Game/Objects/*.*)
file(GLOB GAME_OBJECTS_AMMO      Game/Objects/Ammo/*.*)
file(GLOB GAME_OBJECTS_BUILDINGS Game/Objects/Buildings/*.*)
file(GLOB GAME_OBJECTS_TERRAIN   Game/Objects/Terrain/*.*)
file(GLOB GAME_OBJECTS_UNITS     Game/Objects/Units/*.*)
file(GLOB GAME_OBJECTS_WEAPONS   Game/Objects/Weapons/*.*)
file(GLOB GAME_PATH              Game/Path/*.*)
file(GLOB GRAPHICS_2D            Graphics/2D/*.*)
file(GLOB GRAPHICS_OBJECTS       Graphics/Objects/*.*)
file(GLOB GUI                    GUI/*.*)
file(GLOB GUI_CONTROLS           GUI/Controls/*.*)
file(GLOB GUI_GUIEDITOR          GUI/GuiEditor/*.*)
file(GLOB GUI_GAME               GUI/GuiGame/*.*)
file(GLOB GUI_LOGIC              GUI/Logic/*.*)
file(GLOB GUI_MENU               GUI/Menu/*.*)
file(GLOB GUI_PANELS             GUI/Panels/*.*)
file(GLOB GUI_WINDOWS            GUI/Windows/*.*)
file(GLOB NETWORK                Network/*.*)

source_group(src                      FILES ${SRC})
source_group(Core                     FILES ${CORE})
source_group(Editor                   FILES ${EDITOR})
source_group(Game                     FILES ${GAME})
source_group(Game\\Logic              FILES ${GAME_LOGIC})
source_group(Game\\Objects            FILES ${GAME_OBJECTS})
source_group(Game\\Objects\\Ammo      FILES ${GAME_OBJECTS_AMMO})
source_group(Game\\Objects\\Buildings FILES ${GAME_OBJECTS_BUILDINGS})
source_group(Game\\Objects\\Terrain   FILES ${GAME_OBJECTS_TERRAIN})
source_group(Game\\Objects\\Units     FILES ${GAME_OBJECTS_UNITS})
source_group(Game\\Objects\\Weapons   FILES ${GAME_OBJECTS_WEAPONS})
source_group(Game\\Path               FILES ${GAME_PATH})
source_group(Graphics\\2D             FILES ${GRAPHICS_2D})
source_group(Graphics\\Objects        FILES ${GRAPHICS_OBJECTS})
source_group(GUI                      FILES ${GUI})
source_group(GUI\\Controls            FILES ${GUI_CONTROLS})
source_group(GUI\\GuiEditor           FILES ${GUI_GUIEDITOR})
source_group(GUI\\Game                FILES ${GUI_GAME})
source_group(GUI\\Logic               FILES ${GUI_LOGIC})
source_group(GUI\\Menu                FILES ${GUI_MENU})
source_group(GUI\\Panels              FILES ${GUI_PANELS})
source_group(GUI\\Windows             FILES ${GUI_WINDOWS})
source_group(Network                  FILES ${NETWORK})


add_executable( ${PROJECT_NAME} ${SRC} ${CORE} ${EDITOR} ${GAME} ${GAME_LOGIC} ${GAME_OBJECTS} ${GAME_OBJECTS_AMMO}
                ${GAME_OBJECTS_BUILDINGS} ${GAME_OBJECTS_TERRAIN} ${GAME_OBJECTS_UNITS} ${GAME_OBJECTS_WEAPONS}
                ${GAME_PATH} ${GRAPHICS_2D} ${GRAPHICS_OBJECTS} ${GUI} ${GUI_CONTROLS} ${GUI_GUIEDITOR} ${GUI_GAME}
                ${GUI_LOGIC} ${GUI_MENU} ${GUI_PANELS} ${GUI_WINDOWS} ${NETWORK})

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

