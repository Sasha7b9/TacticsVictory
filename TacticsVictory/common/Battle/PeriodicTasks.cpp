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
//    for (int i = 0; i < 10; i++)
//    {
//        Airplane::Create()->AppendInGame(10 + i * 5, 30);
//    }

    static const int NUM_OBJECTS = 100;

    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        GameWorld::self->AppendObject(Airplane::Create());
//        int index = rand() % 3;
//
//        if (index == 0)         GameWorld::self->AppendObject(Tank::Create());
//        else if (index == 1)    GameWorld::self->AppendObject(Airplane::Create());
//        else                    GameWorld::self->AppendObject(Submarine::Create());
    }
}


void TaskMain::Step()
{
    for (GameObject *object : GameObject::objects)
    {
        object->controller->Move(0.040f);
    }
}


void TaskSendStateInNetwork::Step()
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


void TaskRotator::Step()
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


void TaskProfilerFull::Step()
{
    PROFILER_LOG_FULL();
}


void TaskProfilerLastFrame::Step()
{
    PROFILER_LOG_LAST_FRAME();
}
