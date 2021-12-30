// 2021/12/15 22:18:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Weapons/Weapon.h"


namespace Pi
{
    class Laser : public WeaponObject
    {
    public:

        static GameObject *Create();

    private:

        Laser(int id = -1);

        virtual ~Laser() {};

        static const GameObjectParameters parameters;
    };
}

