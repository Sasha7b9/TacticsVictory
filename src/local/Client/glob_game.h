// 2021/04/02 17:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

class CameraT;
class Client;
class ConfigurationFile;
class LogRAW;
class ServerT;
class Menus;
class PageStart;
class WindowVariables;

extern ConfigurationFile TheConfig;
extern ConfigurationFile TheSettings;
extern ServerT      TheMasterServer;

extern CameraT         *TheCamera;
extern Client          *TheClient;
extern ConsoleT        *TheConsole;
extern CursorT         *TheCursor;
extern GUI             *TheGUI;
extern Hint            *TheHint;
extern LogRAW          *TheLog;
extern Menus           *TheMenu;
extern Mouse           *TheMouse;
extern WindowVariables *TheWindowVars;
