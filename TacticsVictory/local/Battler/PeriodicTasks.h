// 2021/12/24 22:00:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


namespace Pi
{
    class TaskConnecting : public PeriodicTask
    {
    public:
        static TaskConnecting *Self() { static TaskConnecting task; return &task; }
    protected:
        virtual void Step() override;
    };


    class TaskPing : public PeriodicTask
    {
    public:
        static TaskPing *Self() { static TaskPing task; return &task; }
        void ToggleLogging() { enabledLogging = !enabledLogging; }
        bool EnabledLogging() const { return enabledLogging; }
    protected:
        virtual void Step() override;
        bool enabledLogging = false;
    };


    class TaskTraffic : public PeriodicTask
    {
    public:
        static TaskTraffic *Self() { static TaskTraffic task; return &task; }
    protected:
        virtual void Step() override;
    };


    class TaskProfiler : public PeriodicTask
    {
    public:
        static TaskProfiler *Self() { static TaskProfiler task; return &task; }
    protected:
        virtual void Step() override;
    };


    class TaskProfilerLastFrame : public PeriodicTask
    {
    public:
        static TaskProfilerLastFrame *Self() { static TaskProfilerLastFrame task; return &task; }
    protected:
        virtual void Step() override;
    };
}
