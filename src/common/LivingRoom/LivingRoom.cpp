// 2021/04/08 16:17:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ConnectorTCP_v.h"
#include "Utils/GlobalFunctions_.h"
#include <sstream>


int LivingRoom::Run(pchar ip)
{
    TheConnMaster.Init(ip, (uint16)TheSettings.GetInt("master_server", "port"));

    TheConnMaster.SetCallbacks
    (
        []()
        {
            LOGWRITE("Can not connect to master server");
            TheConnMaster.Connect();
        },
        OnConnect,
        OnDisconnect
    );

    TheConnMaster.Connect();

    return MainCycle();
}


int LivingRoom::MainCycle()
{
    while (1)
    {
        GF::DelayMS(50);
    }

    return 0;
}


void LivingRoom::OnConnect()
{
    LOGWRITE("Connection to master server established");

    TheLivingRoom.SendNameToMasterServer();

    TheConnMaster.SetTasks();

    static TaskMasterServer taskPort =
    {
        []()
        {
            return TheConnMaster.SendRequest(MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP);
        },
        [](pchar, void *data, uint)
        {
            int delta = *((int *)data);

            uint16 port_udp = (uint16)(TheSettings.GetInt("master_server", "port") + delta);

            LOGWRITEF("Number port for incoming broadcast connections %d", port_udp);

            TheBroadcastServerUDP.Run(port_udp);
        }
    };
        
    TheConnMaster.RunTask(&taskPort);
}


void LivingRoom::OnDisconnect()
{
    TheConnMaster.Connect();
    LOGWRITE("The master server is down. Attempting to connect");
}


void LivingRoom::SendNameToMasterServer()
{
    std::string name;

    std::stringstream stream(name);

    std::srand((uint)time(nullptr));

    stream << "LivingRoom " << std::rand();

    TheConnMaster.SendRequest(MSG_NTW_SET_NAME_LIVINGROOM, stream.str().c_str());
}
