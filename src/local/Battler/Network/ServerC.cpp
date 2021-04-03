// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/ServerC.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"


ServerC::ServerC(ServerC **self) : Object(TheContext)
{
    SubscribeToEvent(E_NETWORKMESSAGE, URHO3D_HANDLER(ServerC, HandleMessage));
    SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(ServerC, HandleServerConnected));
    SubscribeToEvent(E_SERVERDISCONNECTED, URHO3D_HANDLER(ServerC, HandleServerDisconnected));
    SubscribeToEvent(E_CONNECTFAILED, URHO3D_HANDLER(ServerC, HandleConnectFailed));

    *self = this;
}


void ServerC::Connect(const String &_address, uint16 _port)
{
    address = _address;
    port = _port;

    Connect();
}


void ServerC::Connect()
{
    LOGWRITEF("Trying to join the server %s:%d", address.CString(), port);

    TheNetwork->Connect(address, port, nullptr);
}


void ServerC::HandleMessage(StringHash, VariantMap & eventData)
{
    int id = eventData[NetworkMessage::P_MESSAGEID].GetInt();
 
    Message::Message(id).Handle(eventData);
}


void ServerC::HandleServerConnected(StringHash, VariantMap &)
{
    LOGWRITEF("%s : Connect to server is ok", __FUNCTION__);

    Message::RequestForLevel().Send(true);
}


void ServerC::HandleServerDisconnected(StringHash, VariantMap &)
{
    LOGWRITEF("%s : Disconnect from server", __FUNCTION__);
}


void ServerC::HandleConnectFailed(StringHash, VariantMap &)
{
    LOGERRORF("%s : failed connection", __FUNCTION__);

    Connect();
}
