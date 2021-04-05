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
class MenuConfirmExit;
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

extern CameraT           *TheCamera;
extern ConsoleT          *TheConsole;
extern CursorT           *TheCursor;
extern Editor            *TheEditor;
extern GUI               *TheGUI;
extern GuiEditor         *TheGuiEditor;
extern GuiGame           *TheGuiGame;
extern Hint              *TheHint;
extern LogU3D            *TheLog;
extern MenuConfirmExit   *TheMenuConfirmExit;
extern Menus             *TheMenu;
extern PageGame          *TheMenuMain;
extern Mouse             *TheMouse;
extern PathIndicator     *ThePathIndicator;
extern SceneC            *TheScene;
extern ServerC           *TheServer;
extern Battler           *TheBattler;
extern TerrainT          *TheTerrain;
extern WindowTarget      *TheWindowTarget;             // В этом окне можно посмотреть, что видит юнит
extern WindowVariables   *TheWindowVars;

extern Vector<WindowT *> TheOpenedWindow;
