// 2021/04/11 20:20:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnector_.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/Log_.h"


static TaskMasterServer taskPing = { 1000,
    []()
    {
        int64 now = GF::Timer::TimeMS();

        return TheMasterServer.SendRequest(MSG_NTW_PING, &now, 4);
    },
    [](pchar, void *data, uint)
    {
        uint prev_time = *((uint *)data);

        LOGWRITEF("ping = %d ms", GF::Timer::TimeMS() - prev_time);
    }
};


static TaskMasterServer taskGetInfoLivingRooms = { 1000,
    []()
    {
        return TheMasterServer.SendRequest(MSG_NTW_INFO_LIVINGROOM);
    },
    [](pchar, void *data, uint)
    {
        LOGWRITEF("received data for living rooms : %s", (char *)data);

//        TheMenu->pageFindServer->SetServersInfo((char *)data);
    }
};


void ServerConnector::SetTasks()
{
    TheMasterServer.SetTask(&taskPing);
    TheMasterServer.SetTask(&taskGetInfoLivingRooms);
}
