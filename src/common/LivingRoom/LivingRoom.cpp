// 2021/04/08 16:17:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ConnectorTCP_.h"


int LivingRoom::Run(pchar ip)
{
    remoteMasterIP = ip;

    TheMaster.SetAddress("127.0.0.1", (uint16)TheSettings.GetInt("master_server", "port"));

    TheMaster.SetCallbacks
    (
        []()
        {
            LOGWRITE("Can not connect to local master server. Connect to remote");
            TheLivingRoom.RunRemoteServer();
        },
        []()
        {
            LOGWRITE("Connection to master server established");
            TheLivingRoom.SendNameToMasterServer();
            TheMaster.SetTasks();
        },
        []()
        {
            TheMaster.Connect();
            LOGWRITE("The master server is down. Attempting to connect");
        }
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

    TheMaster.SetAddress(remoteMasterIP, (uint16)TheSettings.GetInt("master_server", "port"));

    TheMaster.SetCallbacks
    (
        []()
        {
            TheMaster.Connect();
        },
        []()
        {
            LOGWRITE("Connection to master server established");
            TheLivingRoom.SendNameToMasterServer();
            TheMaster.SetTasks();
        },
            []()
        {
            TheMaster.Connect();
            LOGWRITE("The master server is down. Attempting to connect");
        }
        );

    LOGWRITE("Wait server for connection");

    TheMaster.Connect();

    return MainCycle();
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
