// 2021/02/26 16:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitS.h"


class TankSpecificS : public UnitSpecificS
{
    URHO3D_OBJECT(TankSpecificS, UnitSpecificS);

public:

    TankSpecificS(Tank *tank) : UnitSpecificS(tank) {}

    virtual void Update(float timeStep) override;
};
