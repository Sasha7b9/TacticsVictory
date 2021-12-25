// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Unit_.h"


namespace Pi
{
    class Tank;
    class GroundUnitController;

    class GroundUnitObject : public UnitObject, public MapElement<GroundUnitObject>
    {
    public:

        Tank *GetTank() { return typeGroundUnit == TypeGroundUnit::Tank ? (Tank *)this : nullptr; }

        const TypeGroundUnit typeGroundUnit;

        static Map<GroundUnitObject> objects;

    protected:

        GroundUnitObject(TypeGroundUnit, int, GroundUnitController *);
    };


    class GroundUnitController : public UnitController
    {
    public:

        virtual ~GroundUnitController() {}

    protected:

        GroundUnitController(GroundUnitObject *, const UnitParameters &);
    };
}
