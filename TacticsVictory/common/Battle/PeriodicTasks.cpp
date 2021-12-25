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
    static const int NUM_OBJECTS = 333;

    for (int i = 0; i < NUM_OBJECTS / 3; i++)
    {
        GameWorld::self->AppendObject(Tank::Create());

        GameWorld::self->AppendObject(Airplane::Create());

        GameWorld::self->AppendObject(Submarine::Create());
    }

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


void TaskMain::Step()
{
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

        up.RotateAboutY(0.2f);

        airplane->SetDirection(direction, up);
    }
}


void TaskProfiler::Step()
{
    LOG_WRITE("Number cycles %d", Profiler::NumberCycles());
}
