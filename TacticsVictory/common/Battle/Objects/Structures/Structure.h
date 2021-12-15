// 2021/12/15 19:32:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject.h"


namespace Pi
{
    class StructureObject : public GameObject
    {
    protected:

        StructureObject(TTypeStructure::S type) : GameObject(TTypeGameObject::Structure), typeStructure(type) {};

    private:

        TTypeStructure::S typeStructure;
    };

    class StructureController : public GameObjectController
    {
    public:

        virtual ~StructureController() {};

    protected:

        StructureController(PiTypeController::S type);
    };
}