// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/GameObject.h"


namespace Pi
{
    // ----------------------------------------------------------------------------------------------------------------
    class UnitObject : public GameObject
    {
    protected:
        UnitObject(PiTypeUnitObject::S _type) : GameObject(PiTypeGameObject::Unit), typeUnit(_type) {}
    private:
        PiTypeUnitObject::S typeUnit;
    };


    // ----------------------------------------------------------------------------------------------------------------
    class UnitController : public GameObjectController
    {
    public:
        virtual ~UnitController() {};
    protected:
        UnitController(PiTypeController::S contrType);
    };
}
