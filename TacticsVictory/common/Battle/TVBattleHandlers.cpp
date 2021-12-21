// 2021/12/20 20:45:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TVBattle.h"
#include "Scene/World/Landscape_.h"


using namespace Pi;


void Battle::ApplicationTask()
{
    static bool first = true;

    if(first)
    {
        if (Landscape::self->IsCreated())
        {
            first = false;

            TheNetworkMgr->SetProtocol(kGameProtocol);
            TheNetworkMgr->SetPortNumber(PORT_NUMBER);
            TheNetworkMgr->SetBroadcastPortNumber(PORT_NUMBER);
            TheMessageMgr->SetMaxPlayerCount(10);
            TheMessageMgr->BeginMultiplayerGame(true);

            LOG_WRITE("Connected to port %d is OK. Wait connections ...", PORT_NUMBER)
        }
    }
}
