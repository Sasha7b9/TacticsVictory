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


void Battle::ApplicationTask()
{
    if(GameState::landscapeCreated && !GameState::objectsCreated)
    {
        for (int i = 0; i < 33; i++)
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

            for (GameObject *object : GameObject::objects)
            {
                TheMessageMgr->SendMessage(PlayerType::Clients, MessageGameObjectNodeTransform(object));
            }
        }
    }

    {
        static uint prevTime = TheTimeMgr->GetAbsoluteTime();

        if (TheTimeMgr->GetAbsoluteTime() - prevTime > 1000)
        {
            prevTime = TheTimeMgr->GetAbsoluteTime();

            LOG_WRITE("%d", prevTime);
        }
    }
}
