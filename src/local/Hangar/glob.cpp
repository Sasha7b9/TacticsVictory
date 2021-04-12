// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/ServerConnector_.h"


Context       *TheContext      = nullptr;
Engine        *TheEngine       = nullptr;
FileSystem    *TheFileSystem   = nullptr;
Graphics      *TheGraphics     = nullptr;
Input         *TheInput        = nullptr;
Localization  *TheLocalization = nullptr;
ResourceCache *TheCache        = nullptr;
Time          *TheTime         = nullptr;
UI            *TheUI           = nullptr;

Hangar        *TheHangar       = nullptr;

ConfigurationFile TheSettings;
ServerConnector   TheMasterServer;

