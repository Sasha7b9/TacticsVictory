// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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
extern GuiGame              *TheGuiGame;
extern GuiEditor            *TheGuiEditor;
extern GUI                  *TheGUI;
extern ConsoleRTS           *TheConsole;
extern WindowVariables      *TheWindowVars;
extern Hint                 *TheHint;
extern int                  *TheCounterHint;
extern Vector<WindowRTS*>   TheOpenedWindow;
extern WindowTarget         *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит

// Меню
extern MenuRTS              *TheMenu;
extern MenuGame             *TheMenuMain;
extern MenuConfirmExit      *TheMenuConfirmExit;

extern ModeApp              TheMode;