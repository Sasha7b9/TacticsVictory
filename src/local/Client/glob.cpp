// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Network/Other/ConnectorUDP_v.h"


Audio           *TheAudio        = nullptr;
Context         *TheContext      = nullptr;
Engine          *TheEngine       = nullptr;
FileSelector    *TheFileSelector = nullptr;
FileSystem      *TheFileSystem   = nullptr;
Font            *TheFont         = nullptr;
Graphics        *TheGraphics     = nullptr;
Input           *TheInput        = nullptr;
ResourceCache   *TheCache        = nullptr;
Localization    *TheLocalization = nullptr;
Renderer        *TheRenderer     = nullptr;
Scene           *TheScene        = nullptr;
Time            *TheTime         = nullptr;
UI              *TheUI           = nullptr;
UIElement       *TheUIRoot       = nullptr;

CameraT         *TheCamera       = nullptr;
Client          *TheClient       = nullptr;
ConsoleT        *TheConsole      = nullptr;
CursorT         *TheCursor       = nullptr;
GUI             *TheGUI          = nullptr;
Hint            *TheHint         = nullptr;
LogRAW          *TheLog          = nullptr;
Menus           *TheMenu         = nullptr;
Mouse           *TheMouse        = nullptr;
TerrainT        *TheTerrain      = nullptr;
WindowVariables *TheWindowVars   = nullptr;

ConfigurationFile TheSettings;
ConnectorTCP      TheConnMaster;
