// 2021/12/25 19:37:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "PeriodicTasks.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Network/Messages/MessagesServer_.h"
#include "Utils/Math_.h"


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
    for (int i = 0; i < 10; i++)
    {
        Airplane *airplane = Airplane::Create();

        airplane->AppendInGame(rand() % 50, 30);

        airplane->GetUnitController()->AppendTask(new CommanderTask(CommanderTask::Type::FreeFlight, CommanderTask::Mode::Absolute));
    }

//    static const int NUM_OBJECTS = 10;
//
//    for (int i = 0; i < NUM_OBJECTS; i++)
//    {
//        GameWorld::self->AppendObject(Airplane::Create());
//        int index = rand() % 3;
//
//        if (index == 0)         GameWorld::self->AppendObject(Tank::Create());
//        else if (index == 1)    GameWorld::self->AppendObject(Airplane::Create());
//        else                    GameWorld::self->AppendObject(Submarine::Create());
//  }
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
    LOG_WRITE("time frame %llu ms (%llu us)", time / 1000, time);
}


void TaskTraceGameObject::RunOnce()
{
    GameObject *object = GameObject::objects.Find(5);
    if (object)
    {
        LOG_WRITE("distance %f", object->GetUnitObject()->GetUnitController()->param.stat.distance);
    }
}


void TaskSendStateInNetwork::RunOnce()
{
    if (TheMessageMgr->GetPlayerCount() > 1)
    {
        MessageGameObjectState message;

        for (GameObject *object : GameObject::objects)
        {
            if (message.NumObjects() == message.MaxNumObjects())
            {
                TheMessageMgr->SendMessageClients(message);
                message.ResetCounter();
            }

            message.AddObject(object);
        }

        if (message.NumObjects() > 0)
        {
            TheMessageMgr->SendMessageClients(message);
        }
    }
}


void TaskRotator::RunOnce()
{
    for (Tank *tank : Tank::objects)
    {
        Vector3D &direction = tank->GetUnitController()->param.direction;
        Vector3D &up = tank->GetUnitController()->param.up;

        direction.RotateAboutZ(0.2f);

        tank->SetDirection(direction, up);
    }

    for (Airplane *airplane : Airplane::objects)
    {
        Vector3D &direction = airplane->GetUnitController()->param.direction;
        Vector3D &up = airplane->GetUnitController()->param.up;

        up.RotateAboutY(0.1f);

        airplane->SetDirection(direction, up);
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
