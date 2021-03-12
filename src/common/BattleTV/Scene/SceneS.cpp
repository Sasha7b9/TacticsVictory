// 2021/03/04 10:35:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/SceneS.h"


SceneS::SceneS(SceneS **self) : SceneT(TheContext)
{
    *self = this;
}


SceneS::~SceneS()
{
    
}


void SceneS::Create()
{
    SceneT::Create();

    TheTerrain = new TerrainT();
    TheTerrain->level->Load("Game/Levels/level.map");
    TheTerrain->CreateFromVector(TheTerrain->level->map);
}
