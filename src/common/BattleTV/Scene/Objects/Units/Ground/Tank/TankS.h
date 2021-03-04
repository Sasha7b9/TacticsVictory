// 2021/02/26 16:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitS.h"


class TankSpecificS : public UnitObjectSpecificS
{
    URHO3D_OBJECT(TankSpecificS, UnitObjectSpecificS);

public:

    TankSpecificS(Tank *tank) : UnitObjectSpecificS(tank) {}

    virtual void Update(float timeStep) override;
};
