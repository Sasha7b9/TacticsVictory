#pragma once


class CameraRTS;
class ConsoleRTS;
class CursorRTS;
class Editor;
class GUI;
class GuiEditor;
class GuiGame;
class Hint;
class Level;
class MenuMain;
class MenuOptions;
class SegmentTerrain;
class Settings;
class Tank;
class TerrainRTS;
class WindowRTS;
class WindowConfirmExit;
class WindowTarget;
class WindowVariables;



extern Audio            *gAudio;
extern Localization     *gLocalization;
extern UI               *gUI;
extern UIElement        *gUIRoot;
extern ResourceCache    *gCache;
extern Engine           *gEngine;
extern Input            *gInput;
extern Renderer         *gRenderer;
extern DebugRenderer    *gDebugRenderer;
extern Context          *gContext;
extern Scene            *gScene;
extern Console          *gEngineConsole;
extern DebugHud         *gDebugHud;
extern Graphics         *gGraphics;
extern FileSystem       *gFileSystem;
extern PhysicsWorld     *gPhysicsWorld;
extern Font             *gFont;
extern Time             *gTime;
extern FileSelector     *gFileSelector;
extern Log              *gLog;
extern Profiler         *gProfiler;
extern Script           *gScript;

extern CameraRTS        *gCamera;
extern CursorRTS        *gCursor;
extern Editor           *gEditor;
extern Settings         *gSet;
extern Level            *gLevel;
extern TerrainRTS       *gTerrain;

extern GUI                  *gGUI;
extern ConsoleRTS           *gConsole;
extern WindowVariables      *gWindowVars;
extern MenuMain             *gMenuMain;
extern GuiGame              *gGuiGame;
extern GuiEditor            *gGuiEditor;
extern MenuOptions          *gMenuOptions;
extern WindowConfirmExit    *gWindowConfirmExit;
extern Hint                 *gHint;
extern int                  *gCounterHint;
extern Vector<WindowRTS*>    gOpenedWindow;
extern PODVector<Tank*>      gTanks;
extern WindowTarget         *gWindowTarget;
