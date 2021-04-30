// 2021/04/30 19:54:46 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Network/MapLivingRooms.h"
#include "Network/Other/ConnectorUDP_v.h"
#include "Network/Other/NetworkTypes_v.h"


void MapLivingRooms::SetTasks()
{
    static ServerTask task_ping =
    {
        []()
        {
            return (uint)0;
        },
        [](pchar, void *, uint)
        {

        }
    };

    for (auto &connector : connectors)
    {
        connector.second.SetTask(&task_ping);
    }
}
