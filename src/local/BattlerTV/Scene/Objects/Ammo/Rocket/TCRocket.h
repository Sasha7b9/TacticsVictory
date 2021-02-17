#pragma once
#include "Scene/Objects/Ammo/Rocket/_TRocket.h"


class CRocket : public Rocket
{
    URHO3D_OBJECT(CRocket, Rocket);

public:

    CRocket(Context *context = TheContext) : Rocket(context) {}

    virtual void SetParameters(float timeStep) override;
};
