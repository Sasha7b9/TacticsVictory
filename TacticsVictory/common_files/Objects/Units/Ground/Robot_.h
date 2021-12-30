// 2021/12/15 21:22:39 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"


namespace Pi
{
    class Robot : public GroundUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Robot(int id = -1);

        virtual ~Robot() {};

        static const GameObjectParameters parameters;
    };
}
