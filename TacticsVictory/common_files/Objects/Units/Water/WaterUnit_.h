// 2021/12/15 19:08:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class WaterUnitController;


    class WaterUnitObject : public UnitObject
    {
    public:

        const TypeWaterUnit typeWaterUnit;

    protected:

        WaterUnitObject(TypeWaterUnit, int, WaterUnitController *);
    };


    class WaterUnitController : public UnitController
    {
    public:

        virtual ~WaterUnitController() {};

//        WaterUnitObject *GetWaterUnitObject() const { return (WaterUnitObject *)gameObject; }

    protected:

        WaterUnitController(WaterUnitObject *, const UnitParameters &);
    };
}
