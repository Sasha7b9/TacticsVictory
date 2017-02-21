#include <stdafx.h>


Audio           *gAudio = nullptr;
Localization    *gLocalization = nullptr;
UI              *gUI = nullptr;
UIElement       *gUIRoot = nullptr;
ResourceCache   *gCache = nullptr;
Engine          *gEngine = nullptr;
Input           *gInput = nullptr;
Renderer        *gRenderer = nullptr;
DebugRenderer   *gDebugRenderer = nullptr;
Context         *gContext = nullptr;
Scene   *gScene = nullptr;
Console *gEngineConsole = nullptr;
DebugHud        *gDebugHud = nullptr;
Graphics        *gGraphics = nullptr;
FileSystem      *gFileSystem = nullptr;
PhysicsWorld    *gPhysicsWorld = nullptr;
Font            *gFont = nullptr;
Time            *gTime = nullptr;
FileSelector    *gFileSelector = nullptr;
Log     *gLog = nullptr;
Profiler        *gProfiler = nullptr;

CameraRTS        *gCamera = nullptr;
lCursor        *gCursor = nullptr;
GuiGame        *gGuiGame = nullptr;
GuiEditor      *gGuiEditor = nullptr;
Editor         *gEditor = nullptr;
Settings       *gSet = nullptr;
GUI            *gGUI = nullptr;
lConsole       *gConsole = nullptr;
MenuMain       *gMenuMain = nullptr;
MenuOptions    *gMenuOptions = nullptr;

WindowConfirmExit   *gWindowConfirmExit = nullptr;
WindowVariables     *gWindowVars = nullptr;
Hint                *gHint = nullptr;
int                 *gCounterHint = 0;
Level               *gLevel = nullptr;
TerrainRTS         *gTerrain = nullptr;
Vector<lWindow*>    gOpenedWindow;
PODVector<Tank*>    gTanks;
WindowTarget        *gWindowTarget = nullptr;
