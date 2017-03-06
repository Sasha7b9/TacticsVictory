#include <stdafx.h>
#include "TacticsVictory.h"
#include "LogRTS.h"
#include "Network/Messages.h"
#include "Core/Camera.h"
#include "Game/Scene.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TacticsVictory::HandleServerConnected(StringHash, VariantMap&)
{
    Connection *connection = gNetwork->GetServerConnection();

    LOG_INFOF("Connect established to %s:%d", connection->GetAddress().CString(), connection->GetPort());

    // Теперь запросим вектор, по которому будем строить карту.

    connection->SendMessage(MSG_REQUEST_LEVEL, true, true, VectorBuffer());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleServerDisconnected(StringHash, VariantMap&)
{
    LOG_INFOF("Connection close");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleConnecFailed(StringHash, VariantMap&)
{
    LOG_INFOF("Failed connection");
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
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleNetworkMessage(StringHash, VariantMap& eventData)
{
    using namespace NetworkMessage;

    int msgID = eventData[P_MESSAGEID].GetInt();
    Connection *connection = (Connection*)eventData[P_CONNECTION].GetPtr();
    const PODVector<uint8>& data = eventData[P_DATA].GetBuffer();
    MemoryBuffer buffer(data);

    VectorBuffer msg;

    if(msgID == MSG_REQUEST_LEVEL)
    {
        uint numRows = gTacticsVictory->scene->level.Size();
        uint numCols = gTacticsVictory->scene->level[0].Size();

        msg.WriteUInt(numRows);
        msg.WriteUInt(numCols);

        for(uint row = 0; row < numRows; row++)
        {
            for(uint col = 0; col < numCols; col++)
            {
                msg.WriteFloat(gTacticsVictory->scene->level[row][col]);
            }
        }

        connection->SendMessage(MSG_SEND_LEVEL, true, true, msg);
    }
    else if(msgID == MSG_SEND_LEVEL)
    {
        scene = new SceneRTS(gContext, SceneRTS::Mode_Client);

        uint numRows = buffer.ReadUInt();
        uint numCols = buffer.ReadUInt();

        gTacticsVictory->scene->level.Resize(numRows);
        for(uint row = 0; row < numRows; row++)
        {
            gTacticsVictory->scene->level[row].Resize(numCols);
            for(uint col = 0; col < numCols; col++)
            {
                gTacticsVictory->scene->level[row][col] = buffer.ReadFloat();
            }
        }

        scene = new SceneRTS(gContext, SceneRTS::Mode_Client);
        scene->Create();
        gCamera->SetEnabled(true);
        gGuiGame->SetVisible(true);
    }
}
