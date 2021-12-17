// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit.h"


namespace Pi
{
    class GroundUnitObject : public UnitObject
    {
    public:

        const TypeGroundUnit::S typeGroundUnit;

    protected:

        GroundUnitObject(TypeGroundUnit::S _type) : UnitObject(TypeUnit::Ground), typeGroundUnit(_type) {}
    };


    class GroundUnitController : public UnitController
    {
    public:

        virtual ~GroundUnitController() {};

        GroundUnitObject *GetGroundUnitObject() const { return (GroundUnitObject *)GetTargetNode(); }

    protected:

        GroundUnitController(const PiTypeController::S &, UnitParameters *);
    };
}
