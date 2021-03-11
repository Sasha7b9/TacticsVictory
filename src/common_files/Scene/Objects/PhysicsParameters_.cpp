// 2021/03/05 20:39:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/PhysicsParameters_.h"


Vector3 PositionPP::GetWorld() const
{
    return object->GetObjectNode()->GetWorldPosition();
}


void PositionPP::SetWorld(const Vector3 &position)
{
    object->GetObjectNode()->SetWorldPosition(position);
}


Vector2 PositionPP::GetCoord() const
{
    Vector3 coord = GetWorld();

    return { coord.z_, coord.x_ };
}


Vector3 DirectionPP::GetWorldDir() const
{
    Vector3 dir = object->GetObjectNode()->GetWorldDirection();

    Quaternion rotate(-object->shift->rotateY, Vector3::UP);

    return rotate * dir;
}


Vector3 DirectionPP::GetWorldUp() const
{
    return object->GetObjectNode()->GetWorldUp();
}


Vector3 DirectionPP::GetWorldRight() const
{
    Vector3 dir = object->GetObjectNode()->GetWorldRight();

    Quaternion rotate(-object->shift->rotateY, Vector3::UP);

    return rotate * dir;
}


Quaternion RotationPP::GetWorld() const
{
    Quaternion result = object->GetObjectNode()->GetRotation();

    Quaternion rotate(-object->shift->rotateY, Vector3::UP);

    return result * rotate;
}


void RotationPP::SetWorld(const Quaternion &rotation)
{
    object->GetObjectNode()->SetRotation(rotation);

    Quaternion shift(object->shift->rotateY, Vector3::UP);

    object->GetObjectNode()->Rotate(shift);
}


void RotationPP::ChangeWorld(const Quaternion &delta)
{
    object->GetObjectNode()->Rotate(delta);
}
