// 2021/12/17 0:02:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/UnitLogic/UnitTask.h"


namespace Pi
{
    class UnitController;


    // Класс для управления передвижением юнита по маршрутам, проложенным штурманом (Navigator)
    class Driver
    {
    public:

        virtual ~Driver();

        static Driver *New(UnitController *);

        virtual void Update(float dT);

        void AppendTask(const UnitTask *);

        bool EmptyTaskList() const { return tasks.GetElementCount() == 0; };

    protected:

        Driver(UnitController *controller);

        UnitObject *unit = nullptr;
        UnitController *controller = nullptr;

        Array<const UnitTask *> tasks;
    };
}