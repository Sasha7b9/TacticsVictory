// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Context           *TheContext = nullptr;
Engine            *TheEngine = nullptr;
FileSystem        *TheFileSystem = nullptr;
Localization      *TheLocalization = nullptr;
Network           *TheNetwork = nullptr;
PhysicsWorld      *ThePhysicsWorld = nullptr;
Profiler          *TheProfiler = nullptr;
ResourceCache     *TheCache = nullptr;
Script            *TheScript = nullptr;
Time              *TheTime = nullptr;


Battle            *TheBattle = nullptr;
Level             *TheLevel = nullptr;
LogT              *TheLog = nullptr;
SceneT            *TheScene = nullptr;
Settings          *TheSet = nullptr;
TerrainT          *TheTerrain = nullptr;
Vector<Connection *> connections;
