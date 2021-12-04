// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/GameObject.h"


namespace Pi
{
    class UnitObject : public GameObject
    {

    };

    class UnitController : public GameObjectController
    {
    public:
        enum class Type
        {
            None_,
            Ground
        };
    protected:
        UnitController(Type unitType, PiTypeController::S contrType);
        UnitController(const GameObjectController &gameObjectController);
    public:
        virtual ~UnitController() {};
    private:
        Type unitType = Type::None_;
    };
}
