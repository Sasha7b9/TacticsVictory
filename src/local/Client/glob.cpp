// 2021/04/02 17:53:31 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Context       *TheContext = nullptr;
ResourceCache *TheCache   = nullptr;

Client           *TheClient = nullptr;
ConfigurationFile TheConfig;
LogRAW           *TheLog = nullptr;
MasterServer      TheMaster;
