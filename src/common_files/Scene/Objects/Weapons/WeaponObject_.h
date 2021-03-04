// 2021/02/22 21:01:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Object_.h"


class WeaponObject : public GameObject
{
    URHO3D_OBJECT(WeaponObject, GameObject);

public:

protected:

    WeaponObject(Context *context);
};
