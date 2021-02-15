// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
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
    uint numRows = TheTacticsVictory->scene->level.Size();
    uint numCols = TheTacticsVictory->scene->level[0].Size();

    out.WriteUInt(numRows);
    out.WriteUInt(numCols);

    for(uint row = 0; row < numRows; row++)
    {
        for(uint col = 0; col < numCols; col++)
        {
            out.WriteFloat(TheTacticsVictory->scene->level[row][col]);
        }
    }

    connection->SendMessage(MSG_SEND_LANDSCAPE, true, true, out);
}


void FUNC_MSG_CAMERA_INFO(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    TheCamera->SetPosition(in.ReadVector3());
    TheCamera->GetNode()->SetRotation(in.ReadQuaternion());
}


void FUNC_MSG_REQUEST_TANKS(Connection *connection, MemoryBuffer &, VectorBufferRTS &out)
{
    uint time = TheTime->GetSystemTime();
    out.WriteUInt(Tank::GetAll().Size());

    for(Tank *tank : Tank::GetAll())
    {
        out.WriteTank(tank);
    }
    connection->SendMessage(MSG_SEND_TANKS, true, true, out);

    gConsole->Write(String(TheTime->GetSystemTime() - time));
}


void FUNC_MSG_DELETE_SERVER(Connection *, MemoryBuffer &, VectorBufferRTS &)
{
    TheEngine->Exit();
}


void FUNC_MSG_SET_NETWORK_LOSS(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    TheServer->SetSimulatedPacketLoss(in.ReadFloat());
}


void FUNC_MSG_SET_NETWORK_LATENCY(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    TheServer->SetSimulatedLatency(in.ReadInt());
}

