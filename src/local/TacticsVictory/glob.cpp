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
PhysicsWorld        *ThePhysicsWorld = nullptr;
Font                *TheFont = nullptr;
Time                *TheTime = nullptr;
FileSelector        *TheFileSelector = nullptr;
Profiler            *TheProfiler = nullptr;
Script              *TheScript = nullptr;

TCamera             *TheCamera = nullptr;
TCursor            *TheCursor = nullptr;
Editor              *TheEditor = nullptr;
Settings            *TheSet = nullptr;
Level               *TheLevel = nullptr;
TerrainTV           *TheTerrain = nullptr;
TacticsVictory      *TheTacticsVictory = nullptr;
CLog                *TheLog = nullptr;

// GUI
GuiGame             *TheGuiGame = nullptr;
GuiEditor           *TheGuiEditor = nullptr;
GUI                 *TheGUI = nullptr;
TConsole           *TheConsole = nullptr;
WindowVariables     *TheWindowVars = nullptr;
Hint                *TheHint = nullptr;
int                 *TheCounterHint = 0;
Vector<TWindow*>   TheOpenedWindow;
WindowTarget        *TheWindowTarget = nullptr;
CScene              *TheScene = nullptr;

// Меню
TMenu              *TheMenu = nullptr;
MenuGame            *TheMenuMain = nullptr;
MenuConfirmExit     *TheMenuConfirmExit = nullptr;
