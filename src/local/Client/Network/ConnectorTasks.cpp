// 2021/04/11 20:20:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Menu/Menu.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Network/Other/NetworkTypes_.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/Log_v.h"


static TaskMasterServer taskPing = {
    []()
    {
        int64 now = GF::Timer::TimeMS();

        return TheMaster.SendRequest(MSG_NTW_PING, &now, 4);
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
        return TheMaster.SendRequest(MSG_NTW_INFO_LIVINGROOM);
    },
    [](pchar, void *data, uint)
    {
        TheMenu->pageFindServer->SetServersInfo((char *)data);
    }
};


void ConnectorTCP::SetTasks()
{
    TheMaster.SetTask(1000, &taskPing);
    TheMaster.SetTask(1000, &taskGetInfoLivingRooms);
}
