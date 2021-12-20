// 2021/12/20 14:19:15 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape_.h"
#include "TVBattle.h"


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

    new Landscape((Battle::self->DataPath() + "levels/level2.lvl").c_str());

    GetRootNode()->AppendNewSubnode(Landscape::self);

    return WorldResult::Okay;
}
