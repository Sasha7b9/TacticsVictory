// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Scene/World/GameWorld.h"
#include "PeriodicTasks.h"


using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battle)


Battle *Battle::self = nullptr;


Battle::Battle()
    : Singleton<Battle>(self)
{
    Log::Construct();

    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    TheWorldMgr->LoadWorld("world/Empty");

    SetTasks();
}


Battle::~Battle()
{
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);
    TheMessageMgr->EndGame();

    Log::Destruct();
}


void Battle::ApplicationTask()
{
    periodicTasks.Run();
    GameWorld::self->periodicTasks.Run();
}


void Battle::SetTasks()
{
    static TaskMain     mainTask;
    static TaskRotator  rotatorTask;
    static TaskProfiler profilerTask;

    periodicTasks.Append(&mainTask, 40);
    periodicTasks.Append(&rotatorTask, 40);
    periodicTasks.Append(&profilerTask, 1000);
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
