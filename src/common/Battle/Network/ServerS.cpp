// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Game/Connection_.h"
#include "Network/Game/Messages/GameMessages_.h"


ServerS::ServerS(ServerS **self) : Object(TheContext)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ServerS, HandlerMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ServerS, HandlerServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ServerS, HandlerServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ServerS, HandlerConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(ServerS, HandlerClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(ServerS, HandlerCliendDisconnected));

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


void ServerS::HandlerMessage(StringHash, VariantMap &eventData)
{
    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();

    Message::Message(id).Handle(eventData);
}


void ServerS::HandlerServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();
}


void ServerS::HandlerServerDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void ServerS::HandlerClientConnected(StringHash, VariantMap &eventData)
{
    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    LOGWRITEF("%s : client %s is connected", __FUNCTION__, newConnection->ToString().CString());

    connections.Push(ConnectionT(newConnection));
}


void ServerS::HandlerCliendDisconnected(StringHash, VariantMap &eventData)
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


void ServerS::HandlerConnectFailed(StringHash, VariantMap &)
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
