// 2021/12/25 19:37:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


namespace Pi
{
    // Эта задача будет выполнена один раз после загрузки ландшафта
    class TaskAfterLoadingLandscape : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };


    // Это основная задача - выполняется каждый кадр
    class TaskMain : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };


    // Тестовая задача
    class TaskRotator : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };


    class TaskProfiler : public PeriodicTask
    {
    protected:
        virtual void Step() override;
    };
}
