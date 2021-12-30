// 2021/12/15 21:29:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class Worm : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Worm(int id = -1);

        virtual ~Worm() {};

        static const GameObjectParameters parameters;
    };
}
