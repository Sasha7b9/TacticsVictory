/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Game/Logic/_TMovinator.h"


SunEngine::SunEngine(Context *context) :
    LogicComponent(context)
{
    SetUpdateEventMask(USE_UPDATE);
}


void SunEngine::SetMoveSpeed(float speedMoving)
{
    speed = speedMoving;
}


void SunEngine::SetCenter(const Vector3 &vec)
{
    center = vec;
}


void SunEngine::Update(float time)
{
    float y = center.y_;
    angle += speed * time;
    float radius = 25.0f;
    float x = center.x_ + (sin(angle) * radius);
    float z = center.z_ + (cos(angle) * radius);
    //node_->SetPosition({100.0f, 25.0f, -100.0f});
    node_->SetPosition(Vector3(x, y, z));
}


void SunEngine::RegisterObject(Context *context)
{
    context->RegisterFactory<SunEngine>();
}
