#include <stdafx.h>
#include "Client.h"
#include "VectorBufferRTS.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Client::Client(Context *context) : Object(context)
{
    network = GetSubsystem<Network>();

    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(Client, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(Client, HandleServerDisconnected));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Client::~Client()
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::StartConnecting(String address, uint16 port, pFuncVV _funcOnConnect)
{
    funcOnConnect = _funcOnConnect;
    network->Connect(address, port, nullptr);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Client::IsConnected()
{
    return connection != nullptr;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Connection *Client::GetServerConnection()
{
    return connection;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::Send(int msgID, const VectorBufferRTS &msg)
{
    if(connection)
    {
        connection->SendMessage(msgID, true, true, msg);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::Disconnect()
{
    network->Disconnect();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint16 Client::GetPort()
{
    if(connection)
    {
        return connection->GetPort();
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::HandleServerConnected(StringHash, VariantMap&)
{
    connection = network->GetServerConnection();

    gConsole->Write(String(L"Установлено соединение с ") + connection->GetAddress() + ToString(":%d", connection->GetPort()));

    if(funcOnConnect)
    {
        funcOnConnect();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Client::HandleServerDisconnected(StringHash, VariantMap&)
{
    connection = nullptr;
}
