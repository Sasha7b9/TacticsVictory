// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/_TTank.h"
#include "Scene/Objects/Units/TCUnitObject.h"


class CTank : public Tank, public CUnitObject
{
    URHO3D_OBJECT(CTank, Tank);

public:

private:

    CTank();
};
