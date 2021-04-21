// 2021/04/11 20:20:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu.h"
#include "Network/Other/ConnectorTCP_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/Log_.h"


static TaskMasterServer taskPing = {
    []()
    {
        int64 now = GF::Timer::TimeMS();

        return TheServerConnector.SendRequest(MSG_NTW_PING, &now, 4);
    },
    [](pchar, void *data, uint)
    {
        (void)data;

//        uint prev_time = *((uint *)data);
//
//        LOGWRITEF("ping = %d ms", GF::Timer::TimeMS() - prev_time);
    }
};


static TaskMasterServer taskGetInfoLivingRooms = {
    []()
    {
        return TheServerConnector.SendRequest(MSG_NTW_INFO_LIVINGROOM);
    },
    [](pchar, void *data, uint)
    {
        TheMenu->pageFindServer->SetServersInfo((char *)data);
    }
};


void ServerConnectorTCP::SetTasks()
{
    TheServerConnector.SetTask(1000, &taskPing);
    TheServerConnector.SetTask(1000, &taskGetInfoLivingRooms);
}
