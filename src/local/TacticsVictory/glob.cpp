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
Scene               *TheScene = nullptr;
Console             *TheEngineConsole = nullptr;
DebugHud            *TheDebugHud = nullptr;
Graphics            *TheGraphics = nullptr;
FileSystem          *TheFileSystem = nullptr;
PhysicsWorld        *ThePhysicsWorld = nullptr;
Font                *TheFont = nullptr;
Time                *TheTime = nullptr;
FileSelector        *TheFileSelector = nullptr;
Profiler            *TheProfiler = nullptr;
Script              *TheScript = nullptr;

CameraRTS           *TheCamera = nullptr;
CursorRTS           *TheCursor = nullptr;
Editor              *TheEditor = nullptr;
Settings            *TheSet = nullptr;
Level               *TheLevel = nullptr;
TerrainRTS          *TheTerrain = nullptr;
TacticsVictory      *TheTacticsVictory = nullptr;
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
WindowTarget        *TheWindowTarget = nullptr;

// Меню
MenuRTS             *TheMenu = nullptr;
MenuGame            *TheMenuMain = nullptr;
MenuConfirmExit     *TheMenuConfirmExit = nullptr;

ModeApp             TheMode = ModeApp_Start;
