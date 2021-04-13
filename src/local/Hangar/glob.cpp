// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ServerConnector_.h"


Context       *TheContext      = nullptr;
Engine        *TheEngine       = nullptr;
FileSystem    *TheFileSystem   = nullptr;
Font          *TheFont         = nullptr;
Graphics      *TheGraphics     = nullptr;
Input         *TheInput        = nullptr;
Localization  *TheLocalization = nullptr;
ResourceCache *TheCache        = nullptr;
SceneC        *TheScene        = nullptr;
Time          *TheTime         = nullptr;
UI            *TheUI           = nullptr;
UIElement     *TheUIRoot       = nullptr;

Chat          *TheChat         = nullptr;
CursorT       *TheCursor       = nullptr;
GUI           *TheGUI          = nullptr;
Hangar        *TheHangar       = nullptr;
Hint          *TheHint         = nullptr;
Menus         *TheMenu         = nullptr;
Mouse         *TheMouse        = nullptr;

ConfigurationFile TheSettings;
ServerConnector   TheMasterServer;

