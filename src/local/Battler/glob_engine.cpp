// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>


Audio               *TheAudio = nullptr;
Localization        *TheLocalization = nullptr;
UI                  *TheUI = nullptr;
UIElement           *TheUIRoot = nullptr;
ResourceCache       *TheCache = nullptr;
Engine              *TheEngine = nullptr;
Input               *TheInput = nullptr;
Renderer            *gRenderer = nullptr;
DebugRenderer       *gDebugRenderer = nullptr;
Context             *gContext = nullptr;
Scene               *gScene = nullptr;
Console             *gEngineConsole = nullptr;
DebugHud            *gDebugHud = nullptr;
Graphics            *gGraphics = nullptr;
FileSystem          *gFileSystem = nullptr;
PhysicsWorld        *gPhysicsWorld = nullptr;
Font                *gFont = nullptr;
Time                *gTime = nullptr;
FileSelector        *gFileSelector = nullptr;
Profiler            *gProfiler = nullptr;
Script              *gScript = nullptr;

CameraRTS           *gCamera = nullptr;
CursorRTS           *gCursor = nullptr;
Editor              *gEditor = nullptr;
Settings            *gSet = nullptr;
Level               *gLevel = nullptr;
TerrainRTS          *gTerrain = nullptr;
TacticsVictory      *gTacticsVictory = nullptr;
LogRTS              *gLog = nullptr;
Server              *gServer = nullptr;
Client              *gClient = nullptr;

// GUI
GuiGame             *gGuiGame = nullptr;
GuiEditor           *gGuiEditor = nullptr;
GUI                 *gGUI = nullptr;
ConsoleRTS          *gConsole = nullptr;
WindowVariables     *gWindowVars = nullptr;
Hint                *gHint = nullptr;
int                 *gCounterHint = 0;
Vector<WindowRTS*>   gOpenedWindow;
WindowTarget        *gWindowTarget = nullptr;

// Меню
MenuRTS             *gMenu = nullptr;
MenuGame            *gMenuMain = nullptr;
MenuConfirmExit     *gMenuConfirmExit = nullptr;

ModeApp             gMode = ModeApp_Start;
