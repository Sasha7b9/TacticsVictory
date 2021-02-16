// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
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
class TerrainTV;
class WindowTV;
class MenuConfirmExit;
class WindowTarget;
class WindowVariables;
class Battler;
class MenuRTS;
class LogTV;
class Server;
class Client;

extern CameraRTS       *TheCamera;
extern Client          *TheClient;
extern ConsoleRTS      *TheConsole;
extern CursorRTS       *TheCursor;
extern Editor          *TheEditor;
extern GUI             *TheGUI;
extern GuiEditor       *TheGuiEditor;
extern GuiGame         *TheGuiGame;
extern Hint            *TheHint;
extern Level           *TheLevel;
extern LogTV          *TheLog;
extern MenuConfirmExit *TheMenuConfirmExit;
extern MenuGame        *TheMenuMain;
extern MenuRTS         *TheMenu;
extern SceneTV        *TheScene;
extern Server          *TheServer;
extern Settings        *TheSet;
extern Battler         *TheTacticsVictory;
extern TerrainTV      *TheTerrain;
extern WindowTarget    *TheWindowTarget;             // � ���� ���� ����� ����������, ��� ����� ����
extern WindowVariables *TheWindowVars;

extern int *TheCounterHint;
extern Vector<WindowTV *> TheOpenedWindow;
extern ModeApp             TheMode;
