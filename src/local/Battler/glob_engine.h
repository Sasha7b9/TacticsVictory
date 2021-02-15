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
extern Renderer             *TheRenderer;
extern DebugRenderer        *TheDebugRenderer;
extern Context              *TheContext;
extern Scene                *TheScene;
extern Console              *TheEngineConsole;
extern DebugHud             *TheDebugHud;
extern Graphics             *TheGraphics;
extern FileSystem           *TheFileSystem;
extern PhysicsWorld         *ThePhysicsWorld;
extern Font                 *TheFont;
extern Time                 *TheTime;
extern FileSelector         *TheFileSelector;
extern Profiler             *TheProfiler;
extern Script               *TheScript;

extern CameraRTS            *TheCamera;
extern CursorRTS            *TheCursor;
extern Editor               *TheEditor;
extern Settings             *TheSet;
extern Level                *TheLevel;
extern TerrainRTS           *TheTerrain;
extern TacticsVictory       *TheTacticsVictory;
extern LogRTS               *TheLog;
extern Server               *TheServer;
extern Client               *TheClient;


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