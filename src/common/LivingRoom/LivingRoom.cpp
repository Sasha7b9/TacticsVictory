// 2021/04/08 16:17:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnector_.h"


int LivingRoom::Run(pchar address)
{
    TheMasterServer.SetAddress(address, (uint16)TheSettings.GetInt("master_server", "port"));

    TheMasterServer.SetCallbacks
    (
        []()
        {
            LOGERROR("Can't connect to master server");
            TheMasterServer.Connect();
            LOGWRITE("Attempt connection to master-server");
        },
        []()
        {
            LOGWRITE("Connection to master server established");

            TheLivingRoom.SendNameToMasterServer();

            TheLivingRoom.SetTasks();
        },
        []()
        {
            TheMasterServer.Connect();
            LOGWRITE("The master server is down. Attempting to connect");
        }
    );

    TheMasterServer.Connect();

    while (true)
    {
        TheMasterServer.Update();
    }

    return 0;
}


void LivingRoom::SetTasks()
{

}


void LivingRoom::SendNameToMasterServer()
{
    std::string name;

    std::stringstream stream(name);

    stream << "LivingRoom " << std::rand();

    TheMasterServer.SendRequest(MSG_NTW_SET_NAME_LIVINGROOM, stream.str().c_str());
}
