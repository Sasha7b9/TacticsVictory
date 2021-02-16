// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Context           *TheContext = nullptr;
Engine            *TheEngine = nullptr;
FileSystem        *TheFileSystem = nullptr;
Font              *TheFont = nullptr;
Localization      *TheLocalization = nullptr;
Network           *TheNetwork = nullptr;
PhysicsWorld      *ThePhysicsWorld = nullptr;
Profiler          *TheProfiler = nullptr;
ResourceCache     *TheCache = nullptr;
Script            *TheScript = nullptr;
Time              *TheTime = nullptr;


Battle             *TheBattle = nullptr;
Level              *TheLevel = nullptr;
LogRTS             *TheLog = nullptr;
SceneTV           *TheScene = nullptr;
Settings           *TheSet = nullptr;
TerrainTV         *TheTerrain = nullptr;
Vector<Connection *> connections;
