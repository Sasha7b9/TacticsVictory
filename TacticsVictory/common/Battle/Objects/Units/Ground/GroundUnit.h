// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    // ----------------------------------------------------------------------------------------------------------------
    class GroundUnitObject : public UnitObject
    {
    protected:

        GroundUnitObject(TTypeGroundUnit::S _type) : UnitObject(TTypeUnit::Ground), typeGroundUnit(_type) {}

    private:

        TTypeGroundUnit::S typeGroundUnit;
    };


    // ----------------------------------------------------------------------------------------------------------------
    class GroundUnitController : public UnitController
    {
    protected:

        GroundUnitController(const PiTypeController::S &contrType);

    public:

        virtual ~GroundUnitController() {};
    };
}
