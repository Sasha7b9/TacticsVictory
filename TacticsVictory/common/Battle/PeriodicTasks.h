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
    private:
        virtual void CreateUnits();
    };


    // Это основная задача - выполняется каждый кадр
    class TaskMain : public PeriodicTask
    {
    public:
        static TaskMain *Self() { static TaskMain task; return &task; }
        virtual void Step() override;
    };


    class TaskSendStateInNetwork : public PeriodicTask
    {
    public:
        static TaskSendStateInNetwork *Self() { static TaskSendStateInNetwork task; return &task; }
        virtual void Step() override;
    };


    // Тестовая задача
    class TaskRotator : public PeriodicTask
    {
    public:
        static TaskRotator *Self() { static TaskRotator task; return &task; }
        virtual void Step() override;
    };


    class TaskProfilerFull : public PeriodicTask
    {
    public:
        static TaskProfilerFull *Self() { static TaskProfilerFull task; return &task; }
    protected:
        virtual void Step() override;
    };


    class TaskProfilerLastFrame : public PeriodicTask
    {
    public:
        static TaskProfilerLastFrame *Self() { static TaskProfilerLastFrame task; return &task; }
        virtual void Step() override;
    };
}
