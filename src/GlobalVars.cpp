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
Urho3D::Scene   *gScene = nullptr;
Urho3D::Console *gEngineConsole = nullptr;
DebugHud        *gDebugHud = nullptr;
Graphics        *gGraphics = nullptr;
FileSystem      *gFileSystem = nullptr;
PhysicsWorld    *gPhysicsWorld = nullptr;
Font            *gFont = nullptr;
Time            *gTime = nullptr;
FileSelector    *gFileSelector = nullptr;
Urho3D::Log     *gLog = nullptr;

Camera         *gCamera = nullptr;
Cursor         *gCursor = nullptr;
GuiGame        *gGuiGame = nullptr;
GuiEditor      *gGuiEditor = nullptr;
Editor         *gEditor = nullptr;
Settings       *gSet = nullptr;
GUI            *gGUI = nullptr;
Console        *gConsole = nullptr;
MenuMain       *gMenuMain = nullptr;
MenuOptions    *gMenuOptions = nullptr;

WindowConfirmExit    *gWindowConfirmExit = nullptr;
WindowVariables    *gWindowVars = nullptr;
Hint               *gHint = nullptr;
int                 *gCounterHint = 0;
Level              *gLevel = nullptr;
Terrain            *gTerrain = nullptr;
Vector<lWindow*>    gOpenedWindow;
