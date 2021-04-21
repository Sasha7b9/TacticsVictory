// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/ConnectorTCP_.h"


Audio         *TheAudio        = nullptr;
Context       *TheContext      = nullptr;
Engine        *TheEngine       = nullptr;
FileSelector  *TheFileSelector = nullptr;
FileSystem    *TheFileSystem   = nullptr;
Font          *TheFont         = nullptr;
Graphics      *TheGraphics     = nullptr;
Input         *TheInput        = nullptr;
ResourceCache *TheCache        = nullptr;
Renderer      *TheRenderer     = nullptr;
Localization  *TheLocalization = nullptr;
Scene         *TheScene        = nullptr;
Time          *TheTime         = nullptr;
UI            *TheUI           = nullptr;
UIElement     *TheUIRoot       = nullptr;

ConfigurationFile  TheConfig;
ConfigurationFile  TheSettings;
ConnectorTCP TheMasterServer;

CameraT         *TheCamera     = nullptr;
Editor          *TheClient     = nullptr;
ConsoleT        *TheConsole    = nullptr;
CursorT         *TheCursor     = nullptr;
GUI             *TheGUI        = nullptr;
Hint            *TheHint       = nullptr;
LogRAW          *TheLog        = nullptr;
Menus           *TheMenu       = nullptr;
Mouse           *TheMouse      = nullptr;
TerrainT        *TheTerrain    = nullptr;
WindowVariables *TheWindowVars = nullptr;

Vector<Control *> TheOpenedWindow;
