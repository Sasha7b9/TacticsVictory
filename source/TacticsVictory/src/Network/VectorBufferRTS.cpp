#include <stdafx.h>
#include "VectorBufferRTS.h"
#include "Game/Objects/Units/Tank/Tank.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VectorBufferRTS::WriteTank(Tank *tank)
{
    Node *node = tank->GetNode();

    WriteUInt(node->GetID());
    WriteVector3(node->GetPosition());
    WriteQuaternion(node->GetRotation());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void VectorBufferRTS::ReadTank(uint *id, Vector3 *position, Quaternion *rotation)
{
    *id = ReadUInt();
    *position = ReadVector3();
    *rotation = ReadQuaternion();
}
