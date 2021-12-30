// 2021/12/15 21:15:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Air/AirUnit_.h"


namespace Pi
{
    class Helicopter : public AirUnitObject
    {
    public:

        static GameObject *Create();

    private:

        Helicopter(int id);

        virtual ~Helicopter() {};

        static const GameObjectParameters parameters;
    };
}
