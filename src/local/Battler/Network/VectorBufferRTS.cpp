// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "VectorBufferRTS.h"
#include "Game/Objects/Units/Tank/Tank.h"



VectorBufferRTS::VectorBufferRTS() : VectorBuffer()
{

}


VectorBufferRTS::VectorBufferRTS(int value) : VectorBuffer()
{
    WriteInt(value);
}


VectorBufferRTS::VectorBufferRTS(float value) : VectorBuffer()
{
    WriteFloat(value);
}


void VectorBufferRTS::WriteTank(Tank *tank)
{
    Node *node = tank->GetNode();

    WriteUInt(tank->GetID());
    WriteVector3(node->GetPosition());
    WriteQuaternion(node->GetRotation());
}


void VectorBufferRTS::ReadTank(uint *id, Vector3 *position, Quaternion *rotation)
{
    *id = ReadUInt();
    *position = ReadVector3();
    *rotation = ReadQuaternion();
}
