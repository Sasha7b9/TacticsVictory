// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "TacticsVictory.h"
#include "LogRTS.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/ClientFunctions.h"
#include "Network/ServerFunctions.h"
#include "Network/VectorBufferRTS.h"
#include "Core/Camera.h"
#include "Game/Scene.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TacticsVictory::HandleConnecFailed(StringHash, VariantMap&)
{
    LOGINFOF("Failed connection");

    SetWindowTitleAndIcon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleClientConnected(StringHash, VariantMap& eventData)
{
    Connection *connection = dynamic_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

    std::stringstream s;
    s << connection->GetAddress().CString() << ":" << connection->GetPort() << " connected";
    LOGINFOF(s.str().c_str());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleClientDisconnected(StringHash, VariantMap& eventData)
{
    Connection *connection = dynamic_cast<Connection*>(eventData[ClientConnected::P_CONNECTION].GetPtr());

    std::stringstream s;
    s << connection->GetAddress().CString() << ":" << connection->GetPort() << " disconnected";
    LOGINFOF(s.str().c_str());

    gEngine->Exit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleNetworkMessage(StringHash, VariantMap& eventData)
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

