// 2021/02/22 20:46:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/_TAirPlane.h"
#include "Scene/Objects/Units/TCUnitObject.h"


class CAirPlane : public AirPlane, public CUnitObject
{
    URHO3D_OBJECT(CAirPlane, AirPlane);

public:

    static SharedPtr<CAirPlane> Create(uint row, uint col);

private:

    CAirPlane();
};
