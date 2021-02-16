// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Audio               *TheAudio = nullptr;
Localization        *TheLocalization = nullptr;
UI                  *TheUI = nullptr;
UIElement           *TheUIRoot = nullptr;
ResourceCache       *TheCache = nullptr;
Engine              *TheEngine = nullptr;
Input               *TheInput = nullptr;
Renderer            *TheRenderer = nullptr;
DebugRenderer       *TheDebugRenderer = nullptr;
Context             *TheContext = nullptr;
Console             *TheEngineConsole = nullptr;
DebugHud            *TheDebugHud = nullptr;
Graphics            *TheGraphics = nullptr;
FileSystem          *TheFileSystem = nullptr;
Network             *TheNetwork = nullptr;
PhysicsWorld        *ThePhysicsWorld = nullptr;
Font                *TheFont = nullptr;
Time                *TheTime = nullptr;
FileSelector        *TheFileSelector = nullptr;
Profiler            *TheProfiler = nullptr;
Script              *TheScript = nullptr;

CursorRTS           *TheCursor = nullptr;
Settings            *TheSet = nullptr;
Level               *TheLevel = nullptr;
TerrainRTS          *TheTerrain = nullptr;
Battle              *TheBattle = nullptr;
LogRTS              *TheLog = nullptr;

// GUI
GuiGame             *TheGuiGame = nullptr;
GuiEditor           *TheGuiEditor = nullptr;
GUI                 *TheGUI = nullptr;
ConsoleRTS          *TheConsole = nullptr;
WindowVariables     *TheWindowVars = nullptr;
Hint                *TheHint = nullptr;
int                 *TheCounterHint = 0;
Vector<WindowRTS*>   TheOpenedWindow;

// Меню
MenuRTS             *TheMenu = nullptr;
MenuGame            *TheMenuMain = nullptr;
MenuConfirmExit     *TheMenuConfirmExit = nullptr;
SceneRTS            *TheScene = nullptr;

Vector<Connection *> connections;
