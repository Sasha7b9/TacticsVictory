// 2021/02/17 15:45:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/Units/Tank/_TTank.h"


class CTank : public Tank
{
    URHO3D_OBJECT(CTank, Tank);

public:

    CTank(Context *context) : Tank(context) { }

    static void RegisterObject(Context *context = TheContext);

    virtual void Existor() override {}
};
