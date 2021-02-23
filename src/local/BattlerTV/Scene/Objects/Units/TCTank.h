// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/_TTank.h"


class CTank : public Tank
{
    URHO3D_OBJECT(CTank, Tank);

public:

    static SharedPtr<CTank> Create(uint row, uint col);

    static Vector<CTank *> storage;

private:

    CTank();
};
