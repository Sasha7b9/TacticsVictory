#include <stdafx.h>
#include "Client.h"
#include "VectorBufferRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Client::Client(Context *context) : Object(context)
{
    network = GetSubsystem<Network>();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Client::~Client()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::StartConnecting(String address, uint16 port, pFuncVV *_funcOnConnect)
{
    funcOnConnect = _funcOnConnect;
    network->Connect(address, port, nullptr);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Client::IsConnected()
{
    return network->GetServerConnection() != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Connection *Client::GetServerConnection()
{
    return network->GetServerConnection();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::Send(int msgID, const VectorBufferRTS &msg)
{
    network->GetServerConnection()->SendMessage(msgID, true, true, msg);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::Disconnect()
{
    network->Disconnect();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint16 Client::GetPort()
{
    if(IsConnected())
    {
        return network->GetServerConnection()->GetPort();
    }
    return 0;
}
