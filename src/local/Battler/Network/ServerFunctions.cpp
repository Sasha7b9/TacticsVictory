// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "ServerFunctions.h"
#include "NetworkMessages.h"
#include "TacticsVictory.h"
#include "VectorBufferRTS.h"
#include "Server.h"
#include "Core/Camera.h"
#include "Game/Scene.h"
#include "GUI/Windows/Console.h"



void FUNC_MSG_REQUEST_LANDSCAPE(Connection *connection, MemoryBuffer &, VectorBufferRTS &out)
{
    uint numRows = gTacticsVictory->scene->level.Size();
    uint numCols = gTacticsVictory->scene->level[0].Size();

    out.WriteUInt(numRows);
    out.WriteUInt(numCols);

    for(uint row = 0; row < numRows; row++)
    {
        for(uint col = 0; col < numCols; col++)
        {
            out.WriteFloat(gTacticsVictory->scene->level[row][col]);
        }
    }

    connection->SendMessage(MSG_SEND_LANDSCAPE, true, true, out);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FUNC_MSG_CAMERA_INFO(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    gCamera->SetPosition(in.ReadVector3());
    gCamera->GetNode()->SetRotation(in.ReadQuaternion());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FUNC_MSG_REQUEST_TANKS(Connection *connection, MemoryBuffer &, VectorBufferRTS &out)
{
    uint time = gTime->GetSystemTime();
    out.WriteUInt(Tank::GetAll().Size());

    for(Tank *tank : Tank::GetAll())
    {
        out.WriteTank(tank);
    }
    connection->SendMessage(MSG_SEND_TANKS, true, true, out);

    gConsole->Write(String(gTime->GetSystemTime() - time));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FUNC_MSG_DELETE_SERVER(Connection *, MemoryBuffer &, VectorBufferRTS &)
{
    gEngine->Exit();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FUNC_MSG_SET_NETWORK_LOSS(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    gServer->SetSimulatedPacketLoss(in.ReadFloat());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void FUNC_MSG_SET_NETWORK_LATENCY(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    gServer->SetSimulatedLatency(in.ReadInt());
}

