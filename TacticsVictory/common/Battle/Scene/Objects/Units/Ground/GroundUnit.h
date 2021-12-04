// 2021/12/1 9:49:51 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Units/Unit.h"


namespace Pi
{
    class GroundUnitObject : public UnitObject
    {

    };

    class GroundUnitController : public UnitController
    {
    public:
        enum class Type
        {
            Tank
        };
    protected:
        GroundUnitController(Type grounUnitType, const PiTypeController::S &contrType);
        GroundUnitController(const GameObjectController &gameObjectController);
    public:
        virtual ~GroundUnitController() {};
    };
}
