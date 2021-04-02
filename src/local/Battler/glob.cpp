// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Audio           *TheAudio = nullptr;
Localization    *TheLocalization = nullptr;
Network         *TheNetwork = nullptr;
UI              *TheUI = nullptr;
UIElement       *TheUIRoot = nullptr;
ResourceCache   *TheCache = nullptr;
Engine          *TheEngine = nullptr;
Input           *TheInput = nullptr;
Renderer        *TheRenderer = nullptr;
DebugRenderer   *TheDebugRenderer = nullptr;
Context         *TheContext = nullptr;
Console         *TheEngineConsole = nullptr;
DebugHud        *TheDebugHud = nullptr;
Graphics        *TheGraphics = nullptr;
FileSystem      *TheFileSystem = nullptr;
PhysicsWorld    *ThePhysicsWorld = nullptr;
Font            *TheFont = nullptr;
Time            *TheTime = nullptr;
FileSelector    *TheFileSelector = nullptr;
Profiler        *TheProfiler = nullptr;
Script          *TheScript = nullptr;

CameraT         *TheCamera = nullptr;
ConsoleT        *TheConsole = nullptr;
CursorT         *TheCursor = nullptr;
Editor          *TheEditor = nullptr;
GUI             *TheGUI = nullptr;
GuiEditor       *TheGuiEditor = nullptr;
GuiGame         *TheGuiGame = nullptr;
Hint            *TheHint = nullptr;
LogU3D          *TheLog = nullptr;
MenuConfirmExit *TheMenuConfirmExit = nullptr;
MenuGame        *TheMenuMain = nullptr;
MenuT           *TheMenu = nullptr;
Mouse           *TheMouse = nullptr;
PathIndicator   *ThePathIndicator = nullptr;
SceneC          *TheScene = nullptr;
ServerC         *TheServer = nullptr;
Settings        *TheSet = nullptr;
Battler         *TheBattler = nullptr;
TerrainT        *TheTerrain = nullptr;
WindowTarget    *TheWindowTarget = nullptr;
WindowVariables *TheWindowVars = nullptr;

int *TheCounterHint = nullptr;
Vector<WindowT *> TheOpenedWindow;
