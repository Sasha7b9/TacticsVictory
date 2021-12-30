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
#include "Scene/World/Landscape_.h"


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
    for (int i = 0; i < 20; i++)
    {
        Airplane *airplane = Airplane::Create();

        airplane->AppendTask(new CommanderTaskTest());

        airplane->AppendInGame(i * 5, 0);

        Tank *tank = Tank::Create();

        tank->params->direction.RotateAboutZ(-K::pi / 2.0f);

        tank->AppendInGame(0, i * 5);
    }

    for (int x = 0; x < 100; x += 2)
    {
        for (int y = 0; y < Landscape::self->GetSizeY_Rows(); y++)
        {
            if (Landscape::self->UnderWater(x, y))
            {
                Submarine *submarine = Submarine::Create();
                submarine->AppendInGame(x, y);
                break;
            }
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
        if (object->params->numberThread == job->numThread)
        {
            object->Move(0.040f);
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
    LOG_WRITE("time frame %llu ms (%llu us), %f us/unit", time / 1000, time, (float)time / (float)GameObject::objects.GetElementCount());
}


void TaskTraceGameObject::RunOnce()
{
    GameObject *object = GameObject::objects.Find(5);
    if (object)
    {
        LOG_WRITE("distance %f", object->GetUnitObject()->params->stat.distance);
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
        GameObjectParameters &param = *tank->params;

        param.direction.RotateAboutZ(0.2f);
        tank->SetDirection(param.direction, param.up);
    }

    for (Airplane *airplane : Airplane::objects)
    {
        GameObjectParameters &param = *airplane->params;

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
