// 2021/02/25 22:14:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitC.h"


class TankSpecificC : public UnitObjectSpecificC
{
    URHO3D_OBJECT(TankSpecificC, UnitObjectSpecificC);

public:

    TankSpecificC(Tank *tank) : UnitObjectSpecificC(tank) {}

    virtual void Update(float timeStep) override;
};
