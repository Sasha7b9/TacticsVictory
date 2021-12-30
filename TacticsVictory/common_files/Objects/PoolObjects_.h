// 2021/12/29 19:00:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    struct GameObjectParameters;

    namespace PoolObjects
    {
        extern const int MAX_NUM_OBJECTS;

        void Consruct();

        void Destruct();

        GameObjectParameters *AllocateParameters(int id);
    }
}
