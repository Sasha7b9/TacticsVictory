// 2021/04/08 16:17:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "LivingRoom.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/ServerConnector_.h"


int LivingRoom::Run(pchar address)
{
    TheServerConnector.SetAddress(address, (uint16)TheSettings.GetInt("master_server", "port"));

    TheServerConnector.SetCallbacks
    (
        []()
        {
            LOGERROR("Can't connect to master server");
            TheServerConnector.Connect();
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
            TheServerConnector.Connect();
            LOGWRITE("The master server is down. Attempting to connect");
        }
    );

    TheServerConnector.Connect();

    while (true)
    {
        TheServerConnector.Update();
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

    TheServerConnector.SendRequest(MSG_NTW_SET_NAME_LIVINGROOM, stream.str().c_str());
}
