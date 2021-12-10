// 2021/12/1 9:47:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/GameObject.h"


namespace Pi
{
    namespace PiTypeUnitObject
    {
        typedef StringHash S;

        const S Ground = "Ground";
    }


    class UnitObject : public GameObject
    {
    protected:
        UnitObject(PiTypeUnitObject::S _type) : GameObject(PiTypeGameObject::Unit), type(_type) {}
    private:
        PiTypeUnitObject::S type;
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
    public:
        virtual ~UnitController() {};
    private:
        Type unitType = Type::None_;
    };
}
