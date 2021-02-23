// 2021/02/23 11:00:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/_TGrenade.h"
#include "Scene/Objects/Ammo/TCAmmoObject.h"


class CGrenade : public Grenade, public CAmmoObject
{
    URHO3D_OBJECT(CGrenade, Grenade);

public:

    static SharedPtr<CGrenade> Create();

private:

    CGrenade();
};
