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
    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    TheWorldMgr->LoadWorld("world/Empty");
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
    uint time = TheTimeMgr->GetMillisecondCount();

    static uint timeNext = time;

    if (time >= timeNext)
    {
        timeNext += 40;

        TaskRotator::Self()->Step();
        TaskMain::Self()->Step();

        static uint timeNextLog = time;

        if (time >= timeNextLog)
        {
            timeNextLog += 1000;
            TaskProfilerLastFrame::Self()->Step();
        }
    }

    GameWorld::self->periodicTasks.Run();
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
