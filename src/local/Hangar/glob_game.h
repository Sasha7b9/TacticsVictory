// 2021/04/02 17:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hangar.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/Chat/Chat.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Windows/Console_.h"
#include "GUI/Windows/WindowVariables_.h"
#include "Network/Other/ServerConnector_.h"
#include "Scene/Cameras/Camera.h"


extern ConfigurationFile TheSettings;
extern ServerConnector   TheMasterServer;

extern CameraT           *TheCamera;
extern Chat              *TheChat;
extern ConsoleT          *TheConsole;
extern CursorT           *TheCursor;
extern GUI               *TheGUI;
extern Hangar            *TheHangar;
extern Hint              *TheHint;
extern Menus             *TheMenu;
extern Mouse             *TheMouse;
extern WindowVariables   *TheWindowVars;
