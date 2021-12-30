// 2021/12/15 18:07:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class AirUnitObject : public UnitObject, public MapElement<AirUnitObject>
    {
    public:

        const TypeAirUnit typeAirUnit;

        static Map<AirUnitObject> objects;

    protected:

        AirUnitObject(TypeAirUnit, const GameObjectParameters *, int);
    };
}

