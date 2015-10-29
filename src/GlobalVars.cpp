#include <stdafx.h>

Localization    *gLocalization = nullptr;
UI              *gUI = nullptr;
UIElement       *gUIRoot = nullptr;
ResourceCache   *gCache = nullptr;
Engine          *gEngine = nullptr;
Input           *gInput = nullptr;
Renderer        *gRenderer = nullptr;
DebugRenderer   *gDebugRenderer = nullptr;
Context         *gContext = nullptr;
Scene           *gScene = nullptr;
Console         *gEngineConsole = nullptr;
DebugHud        *gDebugHud = nullptr;
Graphics        *gGraphics = nullptr;
FileSystem      *gFileSystem = nullptr;
PhysicsWorld    *gPhysicsWorld = nullptr;
Font            *gFont = nullptr;
Time            *gTime = nullptr;
FileSelector    *gFileSelector = nullptr;
Log             *gLog = nullptr;

lCamera         *gCamera = nullptr;
lCursor         *gCursor = nullptr;
lGuiGame        *gGuiGame = nullptr;
lGuiEditor      *gGuiEditor = nullptr;
lEditor         *gEditor = nullptr;
lSettings       *gSet = nullptr;
lGUI            *gGUI = nullptr;
lConsole        *gConsole = nullptr;
lMenuMain       *gMenuMain = nullptr;
lMenuOptions    *gMenuOptions = nullptr;

lWindowConfirmExit    *gWindowConfirmExit = nullptr;
lWindowVariables    *gWindowVars = nullptr;
lHint               *gHint = nullptr;
int                 *gCounterHint = 0;
lLevel              *gLevel = nullptr;
lTerrain            *gTerrain = nullptr;
Vector<lWindow*>    gOpenedWindow;
