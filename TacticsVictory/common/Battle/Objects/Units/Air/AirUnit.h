// 2021/12/15 18:07:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    class AirUnitObject : public UnitObject
    {
    public:

        const TypeAirUnit::S typeAirUnit;

    protected:

        AirUnitObject(TypeAirUnit::S _type) : UnitObject(TypeUnit::Air), typeAirUnit(_type) {}
    };


    class AirUnitController : public UnitController
    {
    public:

        virtual ~AirUnitController() {};

        AirUnitObject *GetAirUnitObject()  { return (AirUnitObject *)GetTargetNode(); }

    protected:

        AirUnitController(const PiTypeController::S &, UnitParameters *);
    };
}

