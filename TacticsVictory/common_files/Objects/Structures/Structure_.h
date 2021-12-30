// 2021/12/15 19:32:49 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    class StructureObject : public GameObject
    {
    protected:

        StructureObject(TypeStructure, const GameObjectParameters *, int);

    private:

        TypeStructure typeStructure;
    };
}