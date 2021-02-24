// 2021/02/23 11:00:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/TGrenade_.h"


class CGrenade : public Grenade
{
    URHO3D_OBJECT(CGrenade, Grenade);

public:

    static SharedPtr<CGrenade> Create();

private:

    CGrenade(Context *context);
};
