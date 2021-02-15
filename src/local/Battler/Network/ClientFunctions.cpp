// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "ClientFunctions.h"
#include "NetworkMessages.h"
#include "TacticsVictory.h"
#include "Core/Camera.h"
#include "Game/Level.h"
#include "Game/Scene.h"
#include "GUI/GuiGame/GuiGame.h"



void FUNC_MSG_SEND_LANDSCAPE(Connection *connection, MemoryBuffer &in, VectorBufferRTS &)
{
    uint numRows = in.ReadUInt();
    uint numCols = in.ReadUInt();

    Vector<Vector<float>> level;

    level.Resize(numRows);
    for(uint row = 0; row < numRows; row++)
    {
        level[row].Resize(numCols);
        for(uint col = 0; col < numCols; col++)
        {
            if(in.IsEof())
            {
                level[row][col] = 0.0f;
            }
            else
            {
                level[row][col] = in.ReadFloat();
            }
        }
    }

    gLevel->SetMap(level);
    gTacticsVictory->scene = new SceneRTS(gContext, SceneRTS::Mode_Client);
    gTacticsVictory->scene->Create();
    gCamera->SetEnabled(true);
    gGuiGame->SetVisible(true);

    connection->SendMessage(MSG_REQUEST_TANKS, true, true, VectorBuffer());
}


void FUNC_MSG_SEND_TANKS(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    uint numTanks = in.ReadUInt();

    for(uint i = 0; i < numTanks; i++)
    {
        uint id = in.ReadUInt();
        Vector3 position = in.ReadVector3();
        Quaternion rotation = in.ReadQuaternion();

        SharedPtr<Tank> tank = Tank::Create(Tank::Small, id);
        tank->GetNode()->SetPosition(position);
        tank->GetNode()->SetRotation(rotation);
        tank->SetEnabled(false);
    }
}


void FUNC_MSG_SEND_SCREENSHOT(Connection *, MemoryBuffer &in, VectorBufferRTS &)
{
    volatile uint numTanks = in.ReadUInt();

    for(uint i = 0; i < numTanks; i++)
    {
        uint id = in.ReadUInt();
        Vector3 position = in.ReadVector3();
        Quaternion rotation = in.ReadQuaternion();
        Tank *tank = Tank::GetByID(id);
        if(tank)
        {
            tank->GetNode()->SetPosition(position);
            tank->GetNode()->SetRotation(rotation);
        }
    }
}
