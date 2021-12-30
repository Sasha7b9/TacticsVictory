// 2021/12/15 21:37:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit_.h"


namespace Pi
{
    class Boat : public WaterUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Boat(int id = -1);

        virtual ~Boat() {};

        static const GameObjectParameters parameters;
    };
}
