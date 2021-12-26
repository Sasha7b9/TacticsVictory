// 2021/12/25 19:37:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "PeriodicTasks.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Network/Messages/MessagesServer_.h"


using namespace Pi;


void TaskAfterLoadingLandscape::Step()
{
    static const int NUM_OBJECTS = 99;

    for (int i = 0; i < NUM_OBJECTS / 3; i++)
    {
        GameWorld::self->AppendObject(Tank::Create());

        GameWorld::self->AppendObject(Airplane::Create());

        GameWorld::self->AppendObject(Submarine::Create());
    }

//    Airplane::Create()->AppendInGame(20, 20);

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


TaskMain *TaskMain::Self()
{
    static TaskMain task;
    return &task;
}


void TaskMain::Step()
{
//    PROFILER_ENTER_FUNC();

    for (GameObject *object : GameObject::objects)
    {
        object->controller->Move(40.0f);
    }

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

//    PROFILER_LEAVE();
}


TaskRotator *TaskRotator::Self()
{
    static TaskRotator task;
    return &task;
}


void TaskRotator::Step()
{
//    PROFILER_ENTER_FUNC();

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

//    PROFILER_LEAVE();
}


TaskProfilerFull *TaskProfilerFull::Self()
{
    static TaskProfilerFull task;
    return &task;
}


void TaskProfilerFull::Step()
{
    PROFILER_LOG_FULL();
}


TaskProfilerLastFrame *TaskProfilerLastFrame::Self()
{
    static TaskProfilerLastFrame task;
    return &task;
}


void TaskProfilerLastFrame::Step()
{
    PROFILER_LOG_LAST_FRAME();
}
