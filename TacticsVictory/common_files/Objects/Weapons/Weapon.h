// 2021/12/15 19:16:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class WeaponObject : public GameObject
    {
    protected:

        WeaponObject(TypeWeapon, const GameObjectParameters *, int);

    private:

        TypeWeapon typeWeapon;
    };
}
