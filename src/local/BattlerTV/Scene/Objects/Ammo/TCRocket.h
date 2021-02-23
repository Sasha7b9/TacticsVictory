// 2021/02/23 11:06:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/_TRocket.h"
#include "Scene/Objects/Ammo/TCAmmoObject.h"


class CRocket : public Rocket, public CAmmoObject
{
    URHO3D_OBJECT(CRocket, Rocket);

public:

    static SharedPtr<CRocket> Create();

private:

    CRocket();
};
