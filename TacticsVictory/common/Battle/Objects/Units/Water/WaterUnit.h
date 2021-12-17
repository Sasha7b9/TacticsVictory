// 2021/12/15 19:08:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    class WaterUnitObject : public UnitObject
    {
    public:

        const TypeWaterUnit::S typeWaterUnit;

    protected:

        WaterUnitObject(TypeWaterUnit::S _type) : UnitObject(TypeUnit::Water), typeWaterUnit(_type) {}
    };


    class WaterUnitController : public UnitController
    {
    public:

        virtual ~WaterUnitController() {};

        WaterUnitObject *GetWaterUnitObject() const { return (WaterUnitObject *)GetTargetNode(); }

    protected:

        WaterUnitController(const PiTypeController::S &, const UnitParameters *);
    };
}
