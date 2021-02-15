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

extern CameraRTS *TheCamera;
extern CursorRTS *TheCursor;
extern Editor *TheEditor;
extern Settings *TheSet;
extern Level *TheLevel;
extern TerrainRTS *TheTerrain;
extern TacticsVictory *TheTacticsVictory;
extern LogRTS *TheLog;
extern Server *TheServer;
extern Client *TheClient;

// GUI
extern GuiGame *TheGuiGame;
extern GuiEditor *TheGuiEditor;
extern GUI *TheGUI;
extern ConsoleRTS *TheConsole;
extern WindowVariables *TheWindowVars;
extern Hint *TheHint;
extern int *TheCounterHint;
extern Vector<WindowRTS *>   TheOpenedWindow;
extern WindowTarget *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит

// Меню
extern MenuRTS *TheMenu;
extern MenuGame *TheMenuMain;
extern MenuConfirmExit *TheMenuConfirmExit;

extern ModeApp              TheMode;
