// 2021/12/20 15:59:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


namespace Pi
{
    class GameObject;

    class GameWorld : public World
    {
    public:

        GameWorld(pchar name);

        virtual ~GameWorld();

        static GameWorld *self;

        void AppendObject(GameObject *object);

        ListPeriodicTask periodicTasks;

    private:
        virtual WorldResult::B Preprocess() override;

        int numTick = 0;                // Порядковый номер расчитывемого тика
    };
}
