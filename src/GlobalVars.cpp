#include <stdafx.h>

Localization    *gLocalization = nullptr;
UI              *gUI = nullptr;
UIElement       *gUIRoot = nullptr;
ResourceCache   *gCache = nullptr;
UEngine         *gEngine = nullptr;
Input           *gInput = nullptr;
Renderer        *gRenderer = nullptr;
UDebugRenderer  *gDebugRenderer = nullptr;
UContext        *gContext = nullptr;
UScene          *gScene = nullptr;
UConsole        *gEngineConsole = nullptr;
UDebugHud       *gDebugHud = nullptr;
Graphics        *gGraphics = nullptr;
UFileSystem     *gFileSystem = nullptr;
PhysicsWorld    *gPhysicsWorld = nullptr;
UFont           *gFont = nullptr;
Time            *gTime = nullptr;
UFileSelector   *gFileSelector = nullptr;
ULog            *gLog = nullptr;

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
