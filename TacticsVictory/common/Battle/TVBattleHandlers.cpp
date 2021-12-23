// 2021/12/20 20:45:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Scene/World/Landscape_.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Network/Messages/MessagesServer_.h"
#include "GameState.h"


using namespace Pi;


#define NUM_OBJECTS 300


void Battle::ApplicationTask()
{
    if(GameState::landscapeCreated && !GameState::objectsCreated)
    {
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

        if(result == PiResultNetwork::Okay)
        {
            LOG_WRITE("Connected to port %d is OK. Wait connections ...", PORT_NUMBER)
        }
        else
        {
            LOG_ERROR_TRACE("Can not begin connected to port %d", PORT_NUMBER);
        }

        GameState::objectsCreated = true;
    }

    if (GameState::objectsCreated && TheMessageMgr->GetPlayerCount() > 1)
    {
        static uint prevTime = TheTimeMgr->GetAbsoluteTime();

        if(TheTimeMgr->GetAbsoluteTime() - prevTime >= 40)
        {
            prevTime = TheTimeMgr->GetAbsoluteTime();

            uint64 start_time = TheTimeMgr->GetMicrosecondCount();

            static int counter = 0;

            MessageGameObjectNodeTransform *message = new MessageGameObjectNodeTransform();

            for (GameObject *object : GameObject::objects)
            {
                if (message->NumObjects() == message->MaxNumObjects())
                {
                    TheMessageMgr->SendMessageClients(*message);
                    delete message;
                    message = new MessageGameObjectNodeTransform(object);
                }

                message->AddObject(object);
            }

            if (message)
            {
                TheMessageMgr->SendMessageClients(*message);
                delete message;
            }

            if (counter++ >= 25)
            {
                counter = 0;

                LOG_WRITE("time send %ld us", TheTimeMgr->GetMicrosecondCount() - start_time);
            }
        }
    }

    {
        static uint prevTime = TheTimeMgr->GetAbsoluteTime();

        if (TheTimeMgr->GetAbsoluteTime() - prevTime > 1000)
        {
            prevTime = TheTimeMgr->GetAbsoluteTime();

            LOG_WRITE("FPS = %d", TheEngine->GetFPS());
        }
    }
}
