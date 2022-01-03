// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"
#include "Objects/World/WorldObject.h"


namespace Pi
{
    class SunController;

    class Sun : public WorldObject
    {
    public:
        Sun(int id = -1);
        virtual ~Sun() {};

        static const GameObjectParameters parameters;

    private:

        float radius = 1.0f;
    };
}
