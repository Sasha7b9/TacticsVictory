#include <stdafx.h>
#include "TacticsVictory.h"
#include "LogRTS.h"
#include "Network/Messages.h"
#include "Network/VectorBufferRTS.h"
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

    SetWindowTitleAndIcon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleServerDisconnected(StringHash, VariantMap&)
{
    LOG_INFOF("Connection close");

    SetWindowTitleAndIcon();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
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

        connection->SendMessage(MSG_REQUEST_TANKS, true, true, VectorBuffer());
    }
    else if(msgID == MSG_CAMERA_INFO)
    {
        gCamera->SetPosition(buffer.ReadVector3());
        gCamera->GetNode()->SetRotation(buffer.ReadQuaternion());
    }
    else if (msgID == MSG_REQUEST_TANKS)
    {
        uint time = gTime->GetSystemTime();
        msg.WriteUInt(gTanks.Size());

        for (Tank *tank : gTanks)
        {
            msg.WriteTank(tank);
        }
        connection->SendMessage(MSG_SEND_TANKS, true, true, msg);

        gConsole->Write(String(gTime->GetSystemTime() - time));
    }
    else if (msgID == MSG_SEND_TANKS)
    {
        uint numTanks = buffer.ReadUInt();

        for (uint i = 0; i < numTanks; i++)
        {
            uint id = buffer.ReadUInt();
            Vector3 position = buffer.ReadVector3();
            Quaternion rotation = buffer.ReadQuaternion();

            SharedPtr<Tank> tank = Tank::Create(Tank::Small, id);
            gTanks.Push(tank);
            tank->GetNode()->SetPosition(position);
            tank->GetNode()->SetRotation(rotation);
            tank->SetEnabled(false);
        }
    }
    else if (msgID == MSG_SEND_SCREENSHOT)
    {
        uint numTanks = buffer.ReadUInt();

        PODVector<Tank*> tanks;
        
        gScene->GetComponents<Tank>(tanks, true);

        for (uint i = 0; i < tanks.Size(); i++)
        {
            if (!buffer.IsEof())
            {
                uint id = buffer.ReadUInt();
                Vector3 position = buffer.ReadVector3();
                Quaternion rotation = buffer.ReadQuaternion();
                tanks[i]->GetNode()->SetPosition(position);
                tanks[i]->GetNode()->SetRotation(rotation);
            }
        }
    }
}

