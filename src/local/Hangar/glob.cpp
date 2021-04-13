// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ServerConnector_.h"


Audio           *TheAudio         = nullptr;
Console         *TheEngineConsole = nullptr;
Context         *TheContext       = nullptr;
DebugHud        *TheDebugHud      = nullptr;
DebugRenderer   *TheDebugRenderer = nullptr;
Engine          *TheEngine        = nullptr;
FileSelector    *TheFileSelector  = nullptr;
FileSystem      *TheFileSystem    = nullptr;
Font            *TheFont          = nullptr;
Graphics        *TheGraphics      = nullptr;
Input           *TheInput         = nullptr;
Localization    *TheLocalization  = nullptr;
Renderer        *TheRenderer      = nullptr;
ResourceCache   *TheCache         = nullptr;
Time            *TheTime          = nullptr;
UI              *TheUI            = nullptr;
UIElement       *TheUIRoot        = nullptr;

CameraT         *TheCamera        = nullptr;
Chat            *TheChat          = nullptr;
ConsoleT        *TheConsole       = nullptr;
CursorT         *TheCursor        = nullptr;
GUI             *TheGUI           = nullptr;
Hangar          *TheHangar        = nullptr;
Hint            *TheHint          = nullptr;
Menus           *TheMenu          = nullptr;
Mouse           *TheMouse         = nullptr;
SceneC          *TheScene         = nullptr;
WindowVariables *TheWindowVars    = nullptr;

ConfigurationFile TheSettings;
ServerConnector   TheMasterServer;

