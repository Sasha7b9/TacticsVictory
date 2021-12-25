// 2021/12/24 22:00:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


namespace Pi
{
    class TaskPing : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };


    class TaskTraffic : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };
}
