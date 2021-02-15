/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Movinator.h"



Movinator::Movinator(Context *context) :
    LogicComponent(context)
{
    SetUpdateEventMask(USE_UPDATE);
}


void Movinator::SetMoveSpeed(float speedMoving)
{
    speed = speedMoving;
}


void Movinator::SetCenter(const Vector3 &vec)
{
    center = vec;
}


void Movinator::Update(float time)
{
    float y = center.y_;
    angle += speed * time;
    float radius = 25.0f;
    float x = center.x_ + (sin(angle) * radius);
    float z = center.z_ + (cos(angle) * radius);
    //node_->SetPosition({100.0f, 25.0f, -100.0f});
    node_->SetPosition(Vector3(x, y, z));
}
