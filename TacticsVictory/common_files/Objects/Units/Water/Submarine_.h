// 2021/12/15 22:05:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/GameObjectParameters_.h"
#include "Objects/Staff/Commander_.h"


namespace Pi
{
    class Submarine : public WaterUnitObject, public MapElement<Submarine>
    {
    public:

        static Submarine *Create(int id = -1);

        static Map<Submarine> objects;

    private:

        Submarine(int id = -1);

        virtual ~Submarine() {};

        static const GameObjectParameters parameters;
    };


    class CommanderSubmarine : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderSubmarine() {}

    protected:

        CommanderSubmarine(GameObject *object) : Commander(object) {}
    };
}
