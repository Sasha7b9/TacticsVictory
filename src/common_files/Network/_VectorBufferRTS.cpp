// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


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
