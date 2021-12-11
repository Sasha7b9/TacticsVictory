// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Unit.h"


namespace Pi
{
    // ----------------------------------------------------------------------------------------------------------------
    class GroundUnitObject : public UnitObject
    {
    public:
    protected:
        GroundUnitObject(PiTypeGroundUnitObject::S _type) : UnitObject(PiTypeUnitObject::Ground), typeGroundUnit(_type) {}
    private:
        PiTypeGroundUnitObject::S typeGroundUnit;
    };


    // ----------------------------------------------------------------------------------------------------------------
    class GroundUnitController : public UnitController
    {
    public:
    protected:
        GroundUnitController(const PiTypeController::S &contrType);
    public:
        virtual ~GroundUnitController() {};
    };
}
