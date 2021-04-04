// 2021/04/02 17:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

class CameraT;
class Editor;
class ConfigurationFile;
class LogRAW;
class MasterServer;
class MenuMain;
class Settings;
class WindowVariables;

extern ConfigurationFile TheConfig;
extern MasterServer      TheMaster;

extern CameraT         *TheCamera;
extern Editor          *TheClient;
extern ConsoleT        *TheConsole;
extern CursorT         *TheCursor;
extern GUI             *TheGUI;
extern Hint            *TheHint;
extern LogRAW          *TheLog;
extern MenuT           *TheMenu;
extern MenuMain        *TheMenuMain;
extern Mouse           *TheMouse;
extern Settings        *TheSet;
extern WindowVariables *TheWindowVars;

extern Vector<WindowT *> TheOpenedWindow;
