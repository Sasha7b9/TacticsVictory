// 2021/12/15 19:43:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Ammo/Ammo_.h"


namespace Pi
{
    class Rocket : public AmmoObject
    {
    public:

        static GameObject *Create();

    private:

        Rocket(int id = -1);

        virtual ~Rocket() {};

        static const GameObjectParameters parameters;
    };
}
