// 2021/12/15 22:30:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Weapons/Weapon.h"


namespace Pi
{
    class RocketLauncher : public WeaponObject
    {
    public:

        static GameObject *Create();

    private:

        RocketLauncher(int id = -1);

        virtual ~RocketLauncher() {}

        static const GameObjectParameters parameters;
    };
}
