// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class TConsole;
class TCursor;
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
class TerrainTV;
class TWindow;
class MenuConfirmExit;
class WindowTarget;
class WindowVariables;
class Battler;
class TMenu;
class Server;
class Client;

class TCamera;
class CLog;
class TScene;

extern TCamera         *TheCamera;
extern Client          *TheClient;
extern TConsole       *TheConsole;
extern TCursor        *TheCursor;
extern Editor          *TheEditor;
extern GUI             *TheGUI;
extern GuiEditor       *TheGuiEditor;
extern GuiGame         *TheGuiGame;
extern Hint            *TheHint;
extern Level           *TheLevel;
extern CLog            *TheLog;
extern MenuConfirmExit *TheMenuConfirmExit;
extern MenuGame        *TheMenuMain;
extern TMenu          *TheMenu;
extern TScene          *TheScene;
extern Server          *TheServer;
extern Settings        *TheSet;
extern Battler         *TheTacticsVictory;
extern TerrainTV       *TheTerrain;
extern WindowTarget    *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables *TheWindowVars;

extern int *TheCounterHint;
extern Vector<TWindow *> TheOpenedWindow;
