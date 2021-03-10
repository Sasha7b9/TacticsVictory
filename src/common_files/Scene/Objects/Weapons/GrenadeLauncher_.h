// 2021/02/22 21:30:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Weapons/WeaponObject_.h"


class GrenadeLauncher : public WeaponObject
{
    URHO3D_OBJECT(GrenadeLauncher, WeaponObject);

public:

protected:

    GrenadeLauncher(Context *context, MinPP &min);
};
