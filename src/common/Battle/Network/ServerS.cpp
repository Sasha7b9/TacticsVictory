// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerS.h"
#include "Network/Game/Messages/GameMessages_.h"


ServerS::ServerS(ServerS **self) : Object(TheContext)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ServerS, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ServerS, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ServerS, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ServerS, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(ServerS, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(ServerS, HandleCliendDisconnected));

    *self = this;
}


bool ServerS::Start(uint16 port)
{
    bool result = TheNetwork->StartServer(port);

    if (result)
    {
        LOGWRITEF("Start server on port %d succsefful", port);
    }
    else
    {
        LOGWRITEF("Start server on port %d failed", port);
    }

    return result;
}


void ServerS::HandleMessage(StringHash, VariantMap &eventData)
{
    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();

    Message::Message(id).Handle(eventData);
}


void ServerS::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void ServerS::HandleServerDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void ServerS::HandleClientConnected(StringHash, VariantMap &eventData)
{
    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    LOGWRITEF("%s : client %s is connected", __FUNCTION__, newConnection->ToString().CString());

    connections.Push(ConnectionT(newConnection));
}


void ServerS::HandleCliendDisconnected(StringHash, VariantMap &eventData)
{
    using namespace ClientDisconnected;

    Connection *closedConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    LOGWRITEF("%s : client %s is disconnected", __FUNCTION__, closedConnection->ToString().CString());

    for (ConnectionT &connection : connections)
    {
        if (connection.self == closedConnection)
        {
            connections.Remove(connection);
            break;
        }
    }

    if (connections.Size() == 0)
    {
        TheEngine->Exit();
    }
}


void ServerS::HandleConnectFailed(StringHash, VariantMap &)
{
    LOGERRORF("%s : failed connection");
}


void ServerS::SendToAll(bool reliable, const Message::Message &message)
{
    for (ConnectionT &connection : connections)
    {
        connection.SendMessage(reliable, message);
    }
}
