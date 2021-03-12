// 2021/02/23 11:03:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/AmmoObject_.h"


class Rocket : public AmmoObject
{
    URHO3D_OBJECT(Rocket, AmmoObject);

public:

protected:

    Rocket(Context *);
};
