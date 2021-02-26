// 2021/02/26 15:53:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/UnitObject_.h"


class UnitObjectSpecificPartC : public UnitObjectSpecificPart
{
    URHO3D_OBJECT(UnitObjectSpecificPartC, UnitObjectSpecificPart);

public:

    UnitObjectSpecificPartC(Context *context) : UnitObjectSpecificPart(context) {}
};
