// 2021/02/15 16:12:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Battle.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Scene/Terrain/Terrain_.h"


extern ConfigurationFile TheConfig;
extern ConfigurationFile TheSettings;


extern Battle       *TheBattle;
extern SceneS       *TheScene;
extern ServerS      *TheServer;
extern TerrainT     *TheTerrain;
