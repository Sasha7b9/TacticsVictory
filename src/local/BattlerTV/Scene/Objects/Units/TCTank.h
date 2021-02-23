// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/_TTank.h"
#include "Scene/Objects/Units/TCUnitObject.h"


class CTankObject : public CUnitObject
{
    URHO3D_OBJECT(CTankObject, CUnitObject);

public:

    CTankObject() : CUnitObject() {}
};


class CTank : public CTankObject
{
    URHO3D_OBJECT(CTank, CTankObject);

public:

    static SharedPtr<CTank> Create(uint row, uint col);

    CTank();
};
