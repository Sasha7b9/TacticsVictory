// 2021/12/15 19:08:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    class WaterUnitObject : public UnitObject
    {
    protected:

        WaterUnitObject(TTypeWaterUnit::S _type) : UnitObject(TTypeUnit::Water), typeWaterUnit(_type) {}

    private:

        TTypeWaterUnit::S typeWaterUnit;
    };


    class WaterUnitController : public UnitController
    {
    protected:

        WaterUnitController(const PiTypeController::S &contrType);

    public:

        virtual ~WaterUnitController() {};
    };
}
