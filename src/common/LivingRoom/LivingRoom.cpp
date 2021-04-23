// 2021/04/08 16:17:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "Network/Other/NetworkTypes_v.h"
#include "Network/Other/ConnectorTCP_v.h"
#include <sstream>


int LivingRoom::Run(pchar ip)
{
    remoteMasterIP = ip;

    TheMaster.Init("127.0.0.1", (uint16)TheSettings.GetInt("master_server", "port"));

    TheMaster.SetCallbacks
    (
        []()
        {
            LOGWRITE("Can not connect to local master server. Connect to remote");
            TheLivingRoom.RunRemoteServer();
        },
        OnConnect,
        OnDisconnect
    );

    LOGWRITE("Wait server for connection");

    TheMaster.Connect();

    return MainCycle();
}


int LivingRoom::RunRemoteServer()
{
    if (!remoteMasterIP)
    {
        LOGERRORF("Not specified address master server");
        return -1;
    }

    TheMaster.Init(remoteMasterIP, (uint16)TheSettings.GetInt("master_server", "port"));

    TheMaster.SetCallbacks
    (
        []()
        {
            TheMaster.Connect();
        },
        OnConnect,
        OnDisconnect
    );

    LOGWRITE("Wait server for connection");

    TheMaster.Connect();

    return MainCycle();
}


void LivingRoom::OnConnect()
{
    LOGWRITE("Connection to master server established");
    TheLivingRoom.SendNameToMasterServer();
    TheMaster.SetTasks();

    static TaskMasterServer taskPort =
    {
        []()
        {
            return TheMaster.SendRequest(MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP);
        },
        [](pchar, void *data, uint)
        {
            int delta = *((int *)data);

            LOGWRITEF("Number port for connection %d", TheSettings.GetInt("master_server", "port") + delta);

//            static SocketConfig config;
//
//            TheServer.Init(config, (int)std::thread::hardware_concurrency());
        }
    };
        
    TheMaster.RunTask(&taskPort);
}


void LivingRoom::OnDisconnect()
{
    TheMaster.Connect();
    LOGWRITE("The master server is down. Attempting to connect");
}


int LivingRoom::MainCycle()
{
    while (true)
    {
        TheMaster.Update();
    }

    return 0;
}


void LivingRoom::SendNameToMasterServer()
{
    std::string name;

    std::stringstream stream(name);

    std::srand((uint)time(nullptr));

    stream << "LivingRoom " << std::rand();

    TheMaster.SendRequest(MSG_NTW_SET_NAME_LIVINGROOM, stream.str().c_str());
}
