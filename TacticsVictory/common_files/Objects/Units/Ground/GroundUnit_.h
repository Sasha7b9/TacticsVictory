// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class Tank;

    class GroundUnitObject : public UnitObject
    {
    public:

        Tank *GetTank() { return typeGroundUnit == TypeGroundUnit::Tank ? (Tank *)this : nullptr; }

        const TypeGroundUnit::S typeGroundUnit;

    protected:

        GroundUnitObject(TypeGroundUnit::S _type, int id = -1) : UnitObject(TypeUnit::Ground, id), typeGroundUnit(_type) {}
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
