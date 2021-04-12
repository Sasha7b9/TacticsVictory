// 2021/04/02 17:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Hangar.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Cursor_.h"
#include "GUI/Chat/Chat.h"
#include "GUI/Menu/Menu.h"
#include "Network/Other/ServerConnector_.h"


extern ConfigurationFile TheSettings;
extern ServerConnector   TheMasterServer;

extern Chat              *TheChat;
extern CursorT           *TheCursor;
extern GUI               *TheGUI;
extern Hangar            *TheHangar;
extern Menus             *TheMenu;
extern Mouse             *TheMouse;
