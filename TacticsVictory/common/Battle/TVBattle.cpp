// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battle)


Battle *Battle::self = nullptr;


Battle::Battle()
    : Singleton<Battle>(self)
{
    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    TheWorldMgr->LoadWorld("world/Empty");
}


Battle::~Battle()
{
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);
    TheMessageMgr->EndGame();
}


World *Battle::ConstructWorld(pchar name, void *)
{
    new GameWorld(name);

    return GameWorld::self;
}


std::string Battle::DataPath() const
{
    return std::filesystem::current_path().string() + "/Data/TacticsVictory/";
}
