// 2021/12/20 14:19:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Objects/GameObject_.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "PeriodicTasks.h"
#include "GameWorld.h"
#include "Objects/World/Landscape_.h"


using namespace Pi;


GameWorld *GameWorld::self = nullptr;


GameWorld::GameWorld(pchar name) : World(name)
{
    self = this;
}


GameWorld::~GameWorld()
{
}


WorldResult::B GameWorld::Preprocess()
{
    WorldResult::B result = World::Preprocess();

    if (result != WorldResult::Okay)
    {
        return result;
    }

    new Landscape((Battle::self->DataPath() + "levels/level2.lvl").c_str(), TaskAfterLoadingLandscape::Self());

    GetRootNode()->AppendNewSubnode(Landscape::self);

    return WorldResult::Okay;
}
