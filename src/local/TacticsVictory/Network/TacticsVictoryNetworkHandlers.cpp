// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void Battler::HandleConnecFailed(StringHash, VariantMap&)
{
    LOGINFOF("Failed connection");

    SetWindowTitleAndIcon();
}


void Battler::HandleClientConnected(StringHash, VariantMap& eventData)
{
    Connection *connection = dynamic_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

    std::stringstream s;
    s << connection->GetAddress().CString() << ":" << connection->GetPort() << " connected";
    LOGINFOF(s.str().c_str());
}


void Battler::HandleClientDisconnected(StringHash, VariantMap& eventData)
{
    Connection *connection = dynamic_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

    std::stringstream s;
    s << connection->GetAddress().CString() << ":" << connection->GetPort() << " disconnected";
    LOGINFOF(s.str().c_str());

    TheEngine->Exit();
}


void Battler::HandleNetworkMessage(StringHash, VariantMap& eventData)
{
    using namespace NetworkMessage;

    int msgID = eventData[P_MESSAGEID].GetInt();
    Connection *connection = dynamic_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
    const PODVector<uint8>& data = eventData[P_DATA].GetBuffer(); //-V2002
    MemoryBuffer buffer(data);

    VectorBufferRTS msg;

    if(networkFunctions[msgID]) //-V108
    {
        networkFunctions[msgID](connection, buffer, msg); //-V108
    }
}

