#include <stdafx.h>


tvMovinator::tvMovinator(Context *context) :
    LogicComponent(context)
{
    SetUpdateEventMask(Urho3D::USE_UPDATE);
}

void tvMovinator::SetMoveSpeed(float speedMoving)
{
    speed = speedMoving;
}

void tvMovinator::SetCenter(const Vector3 &vec)
{
    center = vec;
}

void tvMovinator::Update(float time)
{
    float y = center.y_;
    angle += speed * time;
    float radius = 25.0f;
    float x = center.x_ + (sin(angle) * radius);
    float z = center.z_ + (cos(angle) * radius);
    node_->SetPosition({x, y, z});
}