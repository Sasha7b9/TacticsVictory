// 2021/03/10 15:35:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitS.h"


class AirPlaneSpecificS : public UnitSpecificS
{
    URHO3D_OBJECT(AirPlaneSpecificS, UnitSpecificS);

public:

    AirPlaneSpecificS(AirPlane *airPlane) : UnitSpecificS(airPlane) {}

    virtual void Update(float dT) override;
};
