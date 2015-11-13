#pragma once


#include <Urho3D/Core/Mutex.h>


class Mutex : public Urho3D::Mutex
{
public:
    bool TryAcquire();
private:
};