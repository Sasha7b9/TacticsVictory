// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "PeriodicTasks.h"
#include "Objects/GameObject_.h"
#include "GameWorld.h"


using namespace Pi;

static String<> commandLine;

PI_ENTER_POINT(Battle)


Battle *Battle::self = nullptr;


Battle::Battle()
    : Singleton<Battle>(self)
{
    TheWorldMgr->SetWorldCreator(&ConstructWorld);

    TheWorldMgr->LoadWorld("world/Empty");

    GameObject::Construct();

//    ListPeriodicTask::Self()->Append(TaskFPS::Self(), 1000);
//    ListPeriodicTask::Self()->Append(TaskTraffic::Self(), 1000);
}


Battle::~Battle()
{
    TheWorldMgr->UnloadWorld();
    TheWorldMgr->SetWorldCreator(nullptr);
    TheMessageMgr->EndGame();

    Log::Destruct();

    GameObject::Destruct();
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
    TaskMain::Self()->RunOnce();

    TaskSendStateInNetwork::Self()->RunOnce();

    ListPeriodicTask::Self()->Run();
}


void Battle::RunTasksAcross1000ms()
{
    TaskProfilerLastFrame::Self()->RunOnce();
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
