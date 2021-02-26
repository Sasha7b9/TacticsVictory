// 2021/02/27 0:13:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class PhysicsComponent : public Component
{
    URHO3D_OBJECT(PhysicsComponent, Component);

public:

    PhysicsComponent(Context *context) : Component(context) {}

    Vector3 speedMove = Vector3::ZERO;

    Vector3 speedRotate = Vector3::ZERO;

    Vector3 currentSpeedMove = Vector3::ZERO;
};

