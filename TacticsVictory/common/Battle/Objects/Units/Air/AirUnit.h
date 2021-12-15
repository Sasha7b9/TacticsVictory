// 2021/12/15 18:07:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    class AirUnitObject : public UnitObject
    {
    protected:

        AirUnitObject(TTypeAirUnit::S _type) : UnitObject(TTypeUnit::Air), typeAirUnit(_type) {}

    private:

        TTypeAirUnit::S typeAirUnit;
    };


    class AirUnitController : public UnitController
    {
    protected:

        AirUnitController(const PiTypeController::S &contrType);
    };
}

