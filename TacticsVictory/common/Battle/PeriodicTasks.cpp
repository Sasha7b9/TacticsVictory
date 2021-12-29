// 2021/12/25 19:37:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "PeriodicTasks.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Network/Messages/MessagesServer_.h"
#include "Utils/Math_.h"
#include "Objects/PoolObjects_.h"


using namespace Pi;


void TaskAfterLoadingLandscape::RunOnce()
{
    CreateUnits();

    TheNetworkMgr->SetProtocol(kGameProtocol);
    TheNetworkMgr->SetPortNumber(PORT_NUMBER);
    TheNetworkMgr->SetBroadcastPortNumber(PORT_NUMBER);
    TheMessageMgr->SetMaxPlayerCount(10);
    PiResultNetwork::B result = TheMessageMgr->BeginMultiplayerGame(true);

    if (result == PiResultNetwork::Okay)
    {
        LOG_WRITE("Connected to port %d is OK. Wait connections ...", PORT_NUMBER)
    }
    else
    {
        LOG_ERROR_TRACE("Can not begin connected to port %d", PORT_NUMBER);
    }
}


void TaskAfterLoadingLandscape::CreateUnits()
{
    for (int i = 0; i < PoolObjects::MAX_NUM_OBJECTS; i++)
    {
        Airplane *airplane = Airplane::Create();

        airplane->AppendInGame(rand() % 100, 30);

        airplane->GetUnitController()->AppendTask(new CommanderTask(CommanderTask::Type::FreeFlight, CommanderTask::Mode::Absolute));

        if (i % 50000 == 0)
        {
            LOG_WRITE("Created %d game objects", i);
        }
    }
}


TaskMain::TaskMain() : PeriodicTask()
{
    for (int i = 0; i < NumberThreads(); i++)
    {
        jobs[i] = new MoveGameObjectsJob(i);
    }
}


TaskMain::~TaskMain()
{
    for (int i = 0; i < NumberThreads(); i++)
    {
        delete jobs[i];
    }
}


void TaskMain::MoveGameObjectsJob::JobCompute(Job *_job, void *)
{
    MoveGameObjectsJob *job = (MoveGameObjectsJob *)_job;

    for (GameObject *object : GameObject::objects)
    {
        if (object->numberThread == job->numThread)
        {
            object->controller->Move(0.040f);
        }
    }
}


int TaskMain::NumberThreads()
{
    static int number = M::LimitationAbove(TheEngine->GetProcessorCount() - 1, 32);

    return number;
}


void TaskMain::RunOnce()
{
/*
    TaskFPS::Self()->BeginFrame();

    for (GameObject *object : GameObject::objects)
    {
        object->controller->Move(0.040f);
    }

    TaskFPS::Self()->EndFrame();
*/


    TaskFPS::Self()->BeginFrame();

    numFrame++;

    Batch batch;

    for (int i = 0; i < NumberThreads(); i++)
    {
        TheJobMgr->SubmitJob(jobs[i], &batch);
    }

    TheJobMgr->FinishBatch(&batch);

    TaskFPS::Self()->EndFrame();
}


void TaskFPS::RunOnce()
{
    uint64 time = end - start;
    LOG_WRITE("time frame %llu ms (%llu us), %f us/unit", time / 1000, time, (float)time / (float)PoolObjects::MAX_NUM_OBJECTS);
}


void TaskTraceGameObject::RunOnce()
{
    GameObject *object = GameObject::objects.Find(5);
    if (object)
    {
        LOG_WRITE("distance %f", object->GetUnitObject()->GetUnitController()->param->stat.distance);
    }
}


void TaskSendStateInNetwork::RunOnce()
{
    if (TheMessageMgr->GetPlayerCount() > 1)
    {
        MessageGameObjectState message;

        for (GameObject *object : GameObject::objects)
        {
            if (message.Full())
            {
                TheMessageMgr->SendMessageClients(message);
                message.Clear();
            }

            message.AddObject(object);
        }

        if (!message.Empty())
        {
            TheMessageMgr->SendMessageClients(message);
        }
    }
}


void TaskRotator::RunOnce()
{
    for (Tank *tank : Tank::objects)
    {
        UnitParameters &param = *tank->GetUnitController()->param;

        param.direction.RotateAboutZ(0.2f);
        tank->SetDirection(param.direction, param.up);
    }

    for (Airplane *airplane : Airplane::objects)
    {
        UnitParameters &param = *airplane->GetUnitController()->param;

        param.up.RotateAboutY(0.1f);

        airplane->SetDirection(param.direction, param.up);
    }
}


void TaskProfilerFull::RunOnce()
{
    PROFILER_LOG_FULL();
}


void TaskProfilerLastFrame::RunOnce()
{
    PROFILER_LOG_LAST_FRAME();
}
