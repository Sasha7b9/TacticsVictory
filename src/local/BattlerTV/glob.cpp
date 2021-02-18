// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Audio               *TheAudio = nullptr;
Localization        *TheLocalization = nullptr;
Network             *TheNetwork = nullptr;
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

TCamera           *TheCamera = nullptr;
TCursor           *TheCursor = nullptr;
Editor              *TheEditor = nullptr;
Settings            *TheSet = nullptr;
Level               *TheLevel = nullptr;
TTerrain          *TheTerrain = nullptr;
Battler             *TheTacticsVictory = nullptr;
CLog              *TheLog = nullptr;
Server              *TheServer = nullptr;
Client              *TheClient = nullptr;

GuiGame             *TheGuiGame = nullptr;
GuiEditor           *TheGuiEditor = nullptr;
GUI                 *TheGUI = nullptr;
TConsole          *TheConsole = nullptr;
WindowVariables     *TheWindowVars = nullptr;
Hint                *TheHint = nullptr;
int                 *TheCounterHint = 0;
Vector<TWindow*>   TheOpenedWindow;
WindowTarget        *TheWindowTarget = nullptr;
TMenu             *TheMenu = nullptr;
TScene            *TheScene = nullptr;
MenuGame            *TheMenuMain = nullptr;
MenuConfirmExit     *TheMenuConfirmExit = nullptr;
