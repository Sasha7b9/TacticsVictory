// 2021/04/02 17:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Editor.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Network/Other/ServerConnector_.h"
#include "Scene/Cameras/Camera.h"
#include "Utils/Log_.h"

extern ConfigurationFile TheConfig;
extern ConfigurationFile TheSettings;
extern ServerConnector   TheMasterServer;

extern CameraT         *TheCamera;
extern Editor          *TheClient;
extern ConsoleT        *TheConsole;
extern CursorT         *TheCursor;
extern GUI             *TheGUI;
extern Hint            *TheHint;
extern LogRAW          *TheLog;
extern Menus           *TheMenu;
extern Mouse           *TheMouse;
extern WindowVariables *TheWindowVars;

extern Vector<WindowT *> TheOpenedWindow;
