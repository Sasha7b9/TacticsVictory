#include <stdafx.h>


#include "Object.h"


lObject::lObject(Context *context) : Object(context)
{
    modelNode = gScene->CreateChild(NODE_GAME_OBJECT);
}

void lObject::SetPosition(const Vector3& pos)
{
    modelNode->SetPosition(pos + deltaPos);
}

Vector3 lObject::GetPosition()
{
    return modelNode->GetPosition() - deltaPos;
}
