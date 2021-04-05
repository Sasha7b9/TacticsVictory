// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once

class CameraT;
class ConfigurationFile;
class ConsoleT;
class CursorT;
class Editor;
class GUI;
class GuiEditor;
class GuiGame;
class Hint;
class LogU3D;
class PageGame;
class Menus;
class Mouse;
class PathIndicator;
class SceneC;
class ServerC;
class Battler;
class TerrainT;
class WindowTarget;
class WindowVariables;
class WindowT;

extern ConfigurationFile  TheSettings;

extern Battler *TheBattler;
extern CameraT           *TheCamera;
extern ConsoleT          *TheConsole;
extern CursorT           *TheCursor;
extern Editor            *TheEditor;
extern GUI               *TheGUI;
extern GuiEditor         *TheGuiEditor;
extern GuiGame           *TheGuiGame;
extern Hint              *TheHint;
extern LogU3D            *TheLog;
extern Menus             *TheMenu;
extern Mouse *TheMouse;
extern PageGame          *ThePageGame;
extern PathIndicator     *ThePathIndicator;
extern SceneC            *TheScene;
extern ServerC           *TheServer;
extern TerrainT          *TheTerrain;
extern WindowTarget      *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables   *TheWindowVars;

extern Vector<WindowT *> TheOpenedWindow;
