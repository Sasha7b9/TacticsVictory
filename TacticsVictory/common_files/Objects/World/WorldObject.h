// 2022/1/3 15:56:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class WorldObject : public GameObject, public MapElement<WorldObject>
    {
    public:
        const TypeWorldObject typeWorldObject;

        static Map<WorldObject> objects;

        virtual void Move(float dT) override;

    protected:

        WorldObject(TypeWorldObject, const GameObjectParameters *, int);
    };
}
