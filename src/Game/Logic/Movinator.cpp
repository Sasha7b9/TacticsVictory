#include <stdafx.h>


#include "Movinator.h"


vMovinator::vMovinator(Context *context) :
    LogicComponent(context)
{
    SetUpdateEventMask(Urho3D::USE_UPDATE);
}

void vMovinator::SetMoveSpeed(float speedMoving)
{
    speed = speedMoving;
}

void vMovinator::SetCenter(const Vector3 &vec)
{
    center = vec;
}

void vMovinator::Update(float time)
{
    float y = center.y_;
    angle += speed * time;
    float radius = 25.0f;
    float x = center.x_ + (sin(angle) * radius);
    float z = center.z_ + (cos(angle) * radius);
    node_->SetPosition({x, y, z});
}