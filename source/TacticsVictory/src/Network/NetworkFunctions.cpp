#include <stdafx.h>
#include "NetworkFunctions.h"
#include "NetworkMessages.h"
#include "TacticsVictory.h"
#include "VectorBufferRTS.h"
#include "Core/Camera.h"
#include "Game/Scene.h"
#include "Game/Level.h"
#include "GUI/GuiGame/GuiGame.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            level[row][col] = in.ReadFloat();
        }
    }

    gLevel->Set(level);
    gTacticsVictory->scene = new SceneRTS(gContext, SceneRTS::Mode_Client);
    gTacticsVictory->scene->Create();
    gCamera->SetEnabled(true);
    gGuiGame->SetVisible(true);

    connection->SendMessage(MSG_REQUEST_TANKS, true, true, VectorBuffer());
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
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
