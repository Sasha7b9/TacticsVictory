// 2021/04/11 20:20:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "GUI/Menu/Menu.h"
#include "Network/MapLivingRooms.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Utils/GlobalFunctions_.h"
#include "Utils/Log_v.h"


static ServerTask taskPing
(
    []()
    {
        int64 now = GF::Timer::TimeMS();

        return TheConnMaster.SendRequest(MSG_NTW_PING, &now, 4);
    },
    [](pchar, void *data, uint)
    {
        (void)data;

        uint prev_time = *((uint *)data);

        LOGWRITEF("ping master = %d ms", GF::Timer::TimeMS() - prev_time);
    }
);


static ServerTask taskGetInfoLivingRooms
(
    []()
    {
        return TheConnMaster.SendRequest(MSG_NTW_INFO_LIVINGROOM);
    },
    [](pchar, void *data, uint)
    {
        MapLivingRooms::ParseInfo(data);
    }
);


void Client::SetTasksMasterServer()
{
    TheConnMaster.SetTask(&taskPing);
    TheConnMaster.SetTask(&taskGetInfoLivingRooms);

    static ServerTask taskPortLivingRoom
    (
        []()
        {
            return TheConnMaster.SendRequest(MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP);
        },
        [](pchar, void *data, uint)
        {
            int delta = *((int *)data);

            uint16 port_udp = (uint16)(TheSettings.GetInt("master_server", "port") + delta);

            LOGWRITEF("Number port for connecting to Living Room %d", port_udp);

            MapLivingRooms::SetPort(port_udp);
        }
    );

    TheConnMaster.RunTask(&taskPortLivingRoom);
}
