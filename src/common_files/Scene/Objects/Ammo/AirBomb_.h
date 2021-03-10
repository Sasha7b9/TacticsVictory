// 2021/02/23 11:35:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Ammo/AmmoObject_.h"


class AirBomb : public AmmoObject
{
    URHO3D_OBJECT(AirBomb, AmmoObject);

public:

protected:

    AirBomb(Context *context, MinPP &min);
};
