// 2021/04/12 20:50:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Utils/GlobalFunctions_.h"


static TaskMasterServer taskPing =
{
    []()
    {
        LOGWRITE("Task ping");

        int64 now = GF::Timer::TimeMS();

        return TheConnMaster.SendRequest(MSG_NTW_PING, &now, 4);
    },
    [](pchar, void *data, uint)
    {
        (void)data;
        uint prev_time = *((uint *)data);

        LOGWRITEF("ping = %d ms", GF::Timer::TimeMS() - prev_time);
    }
};


void ConnectorTCP::SetTasks()
{
    TheConnMaster.SetTask(1000, &taskPing);
}
