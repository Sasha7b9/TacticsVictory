#include <stdafx.h>


#include "Rotator.h"


Rotator::Rotator(Context* context) :
    LogicComponent(context),
    rotationSpeed(Vector3::ZERO)
{
    // Only the scene update event is needed: unsubscribe from the rest for optimization
    SetUpdateEventMask(Urho3D::USE_UPDATE);
}

void Rotator::SetRotationSpeed(const Vector3& speed)
{
    rotationSpeed = speed;
}

void Rotator::Update(float timeStep)
{
    // Components have their scene node as a member variable for convenient access. Rotate the scene node now: construct a
    // rotation quaternion from Euler angles, scale rotation speed with the scene update time step
    node_->Rotate(Quaternion(rotationSpeed.x_ * timeStep, rotationSpeed.y_ * timeStep, rotationSpeed.z_ * timeStep));
}
