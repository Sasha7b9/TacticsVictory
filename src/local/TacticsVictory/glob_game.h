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
class TerrainRTS;
class WindowRTS;
class MenuConfirmExit;
class WindowTarget;
class WindowVariables;
class Battler;
class MenuRTS;
class LogRTS;

extern CameraRTS       *TheCamera;
extern ConsoleRTS      *TheConsole;
extern CursorRTS       *TheCursor;
extern Editor          *TheEditor;
extern GUI             *TheGUI;
extern GuiEditor       *TheGuiEditor;
extern GuiGame         *TheGuiGame;
extern Hint            *TheHint;
extern Level           *TheLevel;
extern LogRTS          *TheLog;
extern MenuConfirmExit *TheMenuConfirmExit;
extern MenuGame        *TheMenuMain;
extern MenuRTS         *TheMenu;
extern Settings        *TheSet;
extern Battler         *TheTacticsVictory;
extern TerrainRTS      *TheTerrain;
extern WindowTarget    *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables *TheWindowVars;

extern int *TheCounterHint;
extern Vector<WindowRTS *> TheOpenedWindow;
extern ModeApp             TheMode;
