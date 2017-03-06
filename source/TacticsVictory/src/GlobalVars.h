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
class MenuGame;
class MenuStart;
class MenuOptions;
class SegmentTerrain;
class Settings;
class Tank;
class TerrainRTS;
class WindowRTS;
class MenuConfirmExit;
class WindowTarget;
class WindowVariables;
class TacticsVictory;
class MenuRTS;
class LogRTS;


extern Audio                *gAudio;
extern Localization         *gLocalization;
extern UI                   *gUI;
extern UIElement            *gUIRoot;
extern ResourceCache        *gCache;
extern Engine               *gEngine;
extern Input                *gInput;
extern Renderer             *gRenderer;
extern DebugRenderer        *gDebugRenderer;
extern Context              *gContext;
extern Scene                *gScene;
extern Console              *gEngineConsole;
extern DebugHud             *gDebugHud;
extern Graphics             *gGraphics;
extern FileSystem           *gFileSystem;
extern PhysicsWorld         *gPhysicsWorld;
extern Font                 *gFont;
extern Time                 *gTime;
extern FileSelector         *gFileSelector;
extern Profiler             *gProfiler;
extern Script               *gScript;
extern Network              *gNetwork;

extern CameraRTS            *gCamera;
extern CursorRTS            *gCursor;
extern Editor               *gEditor;
extern Settings             *gSet;
extern Level                *gLevel;
extern TerrainRTS           *gTerrain;
extern TacticsVictory       *gTacticsVictory;
extern PODVector<Tank*>      gTanks;
extern LogRTS               *gLog;

// GUI
extern GuiGame              *gGuiGame;
extern GuiEditor            *gGuiEditor;
extern GUI                  *gGUI;
extern ConsoleRTS           *gConsole;
extern WindowVariables      *gWindowVars;
extern Hint                 *gHint;
extern int                  *gCounterHint;
extern Vector<WindowRTS*>    gOpenedWindow;
extern WindowTarget         *gWindowTarget;             // В этом окне можно посмотреть, что видит юнит

// Меню
extern MenuRTS              *gMenu;
extern MenuGame             *gMenuMain;
extern MenuConfirmExit      *gMenuConfirmExit;
