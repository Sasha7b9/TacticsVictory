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
class WindowRTS;
class MenuConfirmExit;
class WindowTarget;
class WindowVariables;
class Battler;
class MenuRTS;
class LogTV;

extern CameraRTS       *TheCamera;
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
extern Settings        *TheSet;
extern TacticsVictory *TheTacticsVictory;
extern TerrainTV      *TheTerrain;
extern WindowTarget    *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables *TheWindowVars;

extern int *TheCounterHint;
extern Vector<WindowRTS *> TheOpenedWindow;
