// 2021/02/23 10:58:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/AmmoObject_.h"


class Grenade : public AmmoObject
{
    URHO3D_OBJECT(Grenade, AmmoObject);

public:

protected:

    Grenade(Context *context, MinPP &min);
};
