// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Unit.h"


namespace Pi
{
    namespace PiTypeGroundUnitObject
    {
        typedef StringHash S;

        const S Tank = "Tank";
    }

    class GroundUnitObject : public UnitObject
    {
    public:
    protected:
        GroundUnitObject(PiTypeGroundUnitObject::S _type) : UnitObject(PiTypeUnitObject::Ground), type(_type) {}
    private:
        PiTypeGroundUnitObject::S type;
    };

    class GroundUnitController : public UnitController
    {
    public:
    protected:
        GroundUnitController(const PiTypeController::S &contrType);
    public:
        virtual ~GroundUnitController() {};
    };
}
