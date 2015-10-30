#include <stdafx.h>


#include "Object.h"


lObject::lObject() : Object(gContext)
{

}

void lObject::SetPosition(const Vector3& pos)
{
    modelNode->SetPosition(pos + deltaPos);
}

Vector3 lObject::GetPosition()
{
    return modelNode->GetPosition() - deltaPos;
}
