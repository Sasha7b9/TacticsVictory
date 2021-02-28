// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerC.h"
#include "Network/Game/Messages/GameMessages_.h"


ServerC::ServerC(Context *context) : Object(context)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ServerC, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ServerC, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ServerC, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ServerC, HandleConnectFailed));
}


void ServerC::Connect(const String &address, uint16 port)
{
    LOGINFOF("Trying to join the server %s:%d", address.CString(), port);

    TheNetwork->Connect(address, port, nullptr);
}


void ServerC::HandleMessage(StringHash, VariantMap & /*eventData*/)
{
//    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();
//
//    Message::Message(id).Handle(eventData);
}


void ServerC::HandleServerConnected(StringHash, VariantMap &)
{
    LOG_FUNC_ENTER();

    Message::RequestForLevel().Send(true);
}


void ServerC::HandleServerDisconnected(StringHash, VariantMap &)
{
}


void ServerC::HandleConnectFailed(StringHash, VariantMap &)
{
}
