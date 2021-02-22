// 2021/02/22 21:01:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/_TGameObject.h"


class WeaponObject : public GameObject
{
    URHO3D_OBJECT(WeaponObject, GameObject);

public:

    static Vector<WeaponObject *> storage;

protected:

    WeaponObject();
};
