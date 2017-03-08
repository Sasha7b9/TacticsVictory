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
    LOG_INFOF("Failed connection");

    SetWindowTitleAndIcon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleClientConnected(StringHash, VariantMap& eventData)
{
    Connection *connection = (Connection*)eventData[ClientConnected::P_CONNECTION].GetPtr();

    LOG_INFOF("%s:%d connected", connection->GetAddress().CString(), connection->GetPort());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleClientDisconnected(StringHash, VariantMap& eventData)
{
    Connection *connection = (Connection*)eventData[ClientConnected::P_CONNECTION].GetPtr();

    LOG_INFOF("%s:%d disconnected", connection->GetAddress().CString(), connection->GetPort());

    gEngine->Exit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleNetworkMessage(StringHash, VariantMap& eventData)
{
    using namespace NetworkMessage;

    int msgID = eventData[P_MESSAGEID].GetInt();
    Connection *connection = (Connection*)eventData[P_CONNECTION].GetPtr();
    const PODVector<uint8>& data = eventData[P_DATA].GetBuffer();
    MemoryBuffer buffer(data);

    VectorBufferRTS msg;

    if(networkFunctions[msgID])
    {
        networkFunctions[msgID](connection, buffer, msg);
    }
}

