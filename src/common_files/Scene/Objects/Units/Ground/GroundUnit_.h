// 2021/03/10 17:41:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Unit_.h"


class GroundUnit : public Unit
{
    URHO3D_OBJECT(GroundUnit, Unit);

public:

    GroundUnit(Context *context, const MinPP &min) : Unit(context, min) {}
};
