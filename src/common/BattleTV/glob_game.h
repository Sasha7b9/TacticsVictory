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

extern Level           *TheLevel;
extern LogRTS          *TheLog;
extern SceneRTS        *TheScene;
extern Settings        *TheSet;
extern Battle          *TheBattle;
extern TerrainRTS      *TheTerrain;

extern Vector<WindowRTS *> TheOpenedWindow;

extern Vector<Connection *> connections;
