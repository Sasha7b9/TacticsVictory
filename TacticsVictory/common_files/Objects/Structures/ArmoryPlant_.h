// 2021/12/15 19:36:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Structures/Structure_.h"


namespace Pi
{
    class ArmoryPlant : public StructureObject
    {
    public:

        static ArmoryPlant *Create();

    private:

        ArmoryPlant(int id = -1);

        virtual ~ArmoryPlant() {}

        static const GameObjectParameters parameters;
    };
}
