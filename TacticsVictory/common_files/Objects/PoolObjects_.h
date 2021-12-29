// 2021/12/29 19:00:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    struct UnitParameters;

    namespace PoolObjects
    {
        extern const int MAX_NUM_OBJECTS;

        static void Consruct();

        static void Destruct();

        UnitParameters *AllocateParameters(int id);
    }
}
