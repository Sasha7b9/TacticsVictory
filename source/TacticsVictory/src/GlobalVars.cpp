// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>


Audio               *gAudio = nullptr;
Localization        *gLocalization = nullptr;
UI                  *gUI = nullptr;
UIElement           *gUIRoot = nullptr;
ResourceCache       *gCache = nullptr;
Engine              *gEngine = nullptr;
Input               *gInput = nullptr;
#ifdef CLIENT
Renderer            *gRenderer = nullptr;
#endif
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

Mode gMode = Mode_Start;
