#include <stdafx.h>


Audio               *gAudio = nullptr;
Localization        *gLocalization = nullptr;
UI                  *gUI = nullptr;
UIElement           *gUIRoot = nullptr;
ResourceCache       *gCache = nullptr;
Engine              *gEngine = nullptr;
Input               *gInput = nullptr;
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
Log                 *gLog = nullptr;
Profiler            *gProfiler = nullptr;
Script              *gScript = nullptr;

CameraRTS           *gCamera = nullptr;
CursorRTS           *gCursor = nullptr;
Editor              *gEditor = nullptr;
Settings            *gSet = nullptr;
Level               *gLevel = nullptr;
TerrainRTS          *gTerrain = nullptr;
TacticsVictory      *gTacticsVictory = nullptr;
PODVector<Tank*>    gTanks;

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
MenuMain            *gMenuMain = nullptr;
MenuStart           *gMenuStart = nullptr;
MenuOptions         *gMenuOptions = nullptr;
MenuConfirmExit     *gMenuConfirmExit = nullptr;
