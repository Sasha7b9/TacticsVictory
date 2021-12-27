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

    static uint timeNext40ms = time;

    if (time >= timeNext40ms)
    {
        timeNext40ms += 40;

        RunTasksAcross40ms();

        static uint timeNext1000ms = time;

        if (time >= timeNext1000ms)
        {
            timeNext1000ms += 1000;

            RunTasksAcross1000ms();
        }
    }
}


void Battle::RunTasksAcross40ms()
{
    TaskMain::Self()->Step();

    TaskSendStateInNetwork::Self()->Step();

    ListPeriodicTask::Self()->Run();
}


void Battle::RunTasksAcross1000ms()
{
    TaskProfilerLastFrame::Self()->Step();
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
