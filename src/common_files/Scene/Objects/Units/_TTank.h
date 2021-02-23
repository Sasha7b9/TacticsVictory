// 2021/02/22 15:41:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/_TUnitObject.h"


class Tank : public Object
{
    URHO3D_OBJECT(Tank, Object);

public:

    Tank();

    static SharedPtr<Tank> Create();
};
