// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerS.h"
#include "Network/Game/Messages/GameMessages_.h"


ServerS::ServerS(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ServerS, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ServerS, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ServerS, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ServerS, HandleConnectFailed));
    SubscribeToEvent(E_CLIENTCONNECTED, URHO3D_HANDLER(ServerS, HandleClientConnected));
    SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(ServerS, HandleCliendDisconnected));
}


bool ServerS::Start(uint16 port)
{
    bool result = TheNetwork->StartServer(port);

    if (result)
    {
        LOGINFOF("Start server on port %d succsefful", port);
    }
    else
    {
        LOGINFOF("Start server on port %d failed", port);
    }

    return result;
}


void ServerS::HandleMessage(StringHash, VariantMap &eventData)
{
    LOG_FUNC_ENTER();

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
    LOG_FUNC_ENTER();

    using namespace ClientConnected;

    Connection *newConnection = (Connection *)eventData[P_CONNECTION].GetPtr();

    connections.Push(ConnectionT(newConnection));
}


void ServerS::HandleCliendDisconnected(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();

    TheEngine->Exit();
}


void ServerS::HandleConnectFailed(StringHash, VariantMap &)
{
//    LOG_FUNC_ENTER();
}


void ServerS::SendToAll(const Message::Message &message)
{
    for (ConnectionT &connection : connections)
    {
        connection.SendMessage(true, message);
    }
}
