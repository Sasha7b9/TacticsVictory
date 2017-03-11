// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Server.h"
#include "LogRTS.h"
#include "VectorBufferRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Server::Server(Context *context) : Object(context)
{
    network = GetSubsystem<Network>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Server::~Server()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Server::Start(uint16 port)
{
    /*
    gLog->EnableExtendedInfo();

    LOG_INFOF("now connectiong");

    network->Connect("localhost", port, nullptr);

    LOG_INFOF("now connectiong 2");

    float time = gTime->GetElapsedTime();

    while(!network->GetServerConnection()->IsConnected() && (gTime->GetElapsedTime() - time) < 0.01f)
    {
    }

    LOG_INFOF("Is connection ? %x", network->GetServerConnection());
    */

    return network->StartServer(port);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Server::IsRunning()
{
    return network->IsServerRunning();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Vector<SharedPtr<Connection>> Server::GetConnections()
{
    return network->GetClientConnections();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Server::SendToAll(int msgID, const VectorBufferRTS &msg)
{
    network->BroadcastMessage(msgID, true, true, msg);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Server::Disconnect()
{
    network->Disconnect();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Server::SetSimulatedLatency(int timeMS)
{
    network->SetSimulatedLatency(timeMS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Server::SetSimulatedPacketLoss(float probability)
{
    network->SetSimulatedPacketLoss(probability);
}
