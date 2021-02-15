// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
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
class Server;
class Client;


extern Audio                *TheAudio;
extern Localization         *TheLocalization;
extern UI                   *TheUI;
extern UIElement            *TheUIRoot;
extern ResourceCache        *TheCache;
extern Engine               *TheEngine;
extern Input                *TheInput;
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

extern CameraRTS            *gCamera;
extern CursorRTS            *gCursor;
extern Editor               *gEditor;
extern Settings             *gSet;
extern Level                *gLevel;
extern TerrainRTS           *gTerrain;
extern TacticsVictory       *gTacticsVictory;
extern LogRTS               *gLog;
extern Server               *gServer;
extern Client               *gClient;


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

extern ModeApp gMode;