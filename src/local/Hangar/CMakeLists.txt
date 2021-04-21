project (Hangar)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../common_files
                    ../../ThirdParty/sockpp/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include
                    ../../../../Urho3D/generated/${SUB_DIR}/include/Urho3D/ThirdParty)

add_definitions(-DURHO3D_LOGGING -DLOG_U3D -DU3D -DGRAPHICS)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS  /STACK:100000000")

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
add_compile_options(/wd26812)   # Prefer 'enum class' over 'enum' (Enum.3)
add_compile_options(/wd28251)   # Inconsistent annotation for function: this instance has an error

file(GLOB SRC              ../../common_files/*.*
                                              *.h *.cpp)
file(GLOB CORE             ../../common_files/Core/Math_.*)
file(GLOB FILE_SYSTEM      ../../common_files/FileSystem/ConfigurationFile_.*
                           ../../common_files/FileSystem/FileSystem_.*)
file(GLOB GRAPHICS         ../../common_files/Graphics/Renderer_.*)
file(GLOB GRAPHICS_2D      ../../common_files/Graphics/2D/Image_.*)
file(GLOB GUI              ../../common_files/GUI/Cursor_.*
                           ../../common_files/GUI/GUI_.*
                                              GUI/*.*)
file(GLOB GUI_CHAT                            GUI/Chat/*.*)
file(GLOB GUI_CONTROLS     ../../common_files/GUI/Controls/Control_.*
                           ../../common_files/GUI/Controls/DropDownListWithTextAndButton_.*
                           ../../common_files/GUI/Controls/GovernorFloat_.*
                           ../../common_files/GUI/Controls/Label_.*
                           ../../common_files/GUI/Controls/Hint_.*
                           ../../common_files/GUI/Controls/Buttons/Button_.*
                           ../../common_files/GUI/Controls/Buttons/ButtonSwitch_.*
                           ../../common_files/GUI/Controls/Buttons/ButtonToggled_.*
                           ../../common_files/GUI/Controls/Sliders/Slider_.*
                           ../../common_files/GUI/Controls/Sliders/SliderInt_.*
                           ../../common_files/GUI/Controls/Sliders/SliderWithTextAndButtons_.*)
file(GLOB GUI_LOGIC        ../../common_files/GUI/Logic/LineTranslator1D_.*
                           ../../common_files/GUI/Logic/LineTranslator2D_.*
                           ../../common_files/GUI/Logic/Mutator_.*)
file(GLOB GUI_MENU         ../../common_files/GUI/Menu/Menu_.*
                           ../../common_files/GUI/Menu/MenuEvents_.*
                           ../../common_files/GUI/Menu/MenuPage_.*
                                              GUI/Menu/*.*)
file(GLOB GUI_WINDOWS      ../../common_files/GUI/Windows/Console_.*
                           ../../common_files/GUI/Windows/ConsoleParserFunctions_.*
                           ../../common_files/GUI/Windows/Window_.*
                                              GUI/Windows/Chat.*)
file(GLOB INPUT            ../../common_files/Input/Mouse_.*
                                              Input/Mouse.cpp)
file(GLOB NETWORK          ../../common_files/Network/Other/ConnectorTCP_.*)
file(GLOB SCENE                               Scene/*.*)
file(GLOB SCENE_CAMERAS    ../../common_files/Scene/Cameras/*.*)
file(GLOB SCENE_OBJECTS    ../../common_files/Scene/Objects/PhysicsParameters_.*)
file(GLOB SCENE_PRIMITIVES ../../common_files/Scene/Primitives/Line_.*
                           ../../common_files/Scene/Primitives/Plane_.*)
file(GLOB SCENE_TERRAIN    ../../common_files/Scene/Terrain/*.*
                              ../common_files/Scene/Terrain/*.*)
file(GLOB UTILS            ../../common_files/Utils/GlobalFunctions_.*
                           ../../common_files/Utils/Log_.*
                           ../../common_files/Utils/StringUtils_.*
                           ../../common_files/Utils/UtilsOS_.*)

file(GLOB SOCKPP               ThirdParty/sockpp.cpp)
file(GLOB SOCKPP_SOURCES ../../ThirdParty/sockpp/src/*.cpp)
file(GLOB SOCKPP_INCLUDE ../../ThirdParty/sockpp/include/sockpp/*.h)

source_group(src               FILES ${SRC})
source_group(Core              FILES ${CORE})
source_group(FileSystem        FILES ${FILE_SYSTEM})
source_group(Graphics          FILES ${GRAPHICS})
source_group(Graphics\\2D      FILES ${GRAPHICS_2D})
source_group(GUI               FILES ${GUI})
source_group(GUI\\Chat         FILES ${GUI_CHAT})
source_group(GUI\\Controls     FILES ${GUI_CONTROLS})
source_group(GUI\\Logic        FILES ${GUI_LOGIC})
source_group(GUI\\Menu         FILES ${GUI_MENU})
source_group(GUI\\Windows      FILES ${GUI_WINDOWS})
source_group(Input             FILES ${INPUT})
source_group(Network           FILES ${NETWORK})
source_group(Scene             FILES ${SCENE})
source_group(Scene\\Cameras    FILES ${SCENE_CAMERAS})
source_group(Scene\\Objects    FILES ${SCENE_OBJECTS})
source_group(Scene\\Primitives FILES ${SCENE_PRIMITIVES})
source_group(Scene\\Terrain    FILES ${SCENE_TERRAIN})
source_group(Utils             FILES ${UTILS})

source_group(ThirdParty\\sockpp          FILES ${SOCKPP})
source_group(ThirdParty\\sockpp\\sources FILES ${SOCKPP_SOURCES})
source_group(ThirdParty\\sockpp\\include FILES ${SOCKPP_INCLUDE})

set_source_files_properties(${SOCKPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

file(GLOB FILES_UNITY ${SRC} ${CORE} ${FILE_SYSTEM} ${GRAPHICS} ${GRAPHICS_2D}
    ${GUI} ${GUI_CHAT} ${GUI_CONTROLS} ${GUI_LOGIC} ${GUI_MENU} ${GUI_WINDOWS}
    ${INPUT} ${NETWORK}
    ${SCENE} ${SCENE_CAMERAS} ${SCENE_OBJECTS} ${SCENE_PRIMITIVES} ${SCENE_TERRAIN}
    ${UTILS} ${SOCKPP})

add_executable( ${PROJECT_NAME} 
                ${FILES_UNITY}
                ${SOCKPP_INCLUDE} ${SOCKPP_SOURCES})

set_target_properties(${PROJECT_NAME}       PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(${FILES_UNITY}  PROPERTIES UNITY_GROUP "hangar")

include(../../RuntimeLibrary.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_link_libraries(${PROJECT_NAME} Urho3D_d)
else()
    target_link_libraries(${PROJECT_NAME} Urho3D)
endif()

target_link_libraries(${PROJECT_NAME} ws2_32)

include(../../SetWorkingDirectory.cmake)
include(../../Install.cmake)
include(../../CopyToDirEXE.cmake)
