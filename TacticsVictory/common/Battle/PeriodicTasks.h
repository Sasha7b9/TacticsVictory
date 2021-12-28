// 2021/12/25 19:37:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


namespace Pi
{
    // Эта задача будет выполнена один раз после загрузки ландшафта
    class TaskAfterLoadingLandscape : public PeriodicTask
    {
    public:
        static TaskAfterLoadingLandscape *Self() { static TaskAfterLoadingLandscape task; return &task; }
    protected:
        virtual void RunOnce() override;
    private:
        virtual void CreateUnits();
    };


    // Это основная задача - выполняется каждый кадр
    class TaskMain : public PeriodicTask
    {
    public:
        static TaskMain *Self() { static TaskMain task; return &task; }
        // Число потоков, используемых для обработки объектов
        static int NumberThreads();
        virtual void RunOnce() override;
    private:
        TaskMain();
        ~TaskMain();
        int numFrame = 0;

        class MoveGameObjectsJob : public BatchJob
        {
        public:
            MoveGameObjectsJob(int num) : BatchJob(&JobCompute), numThread(num)  {}
        private:
            static void JobCompute(Job *, void *);
            int numThread;
        };

        MoveGameObjectsJob *jobs[32];
    };


    // Заслать в сеть состояние всех объектов
    class TaskSendStateInNetwork : public PeriodicTask
    {
    public:
        static TaskSendStateInNetwork *Self() { static TaskSendStateInNetwork task; return &task; }
        virtual void RunOnce() override;
    };


    // Тестовая задача - вращение объектов на сцене
    class TaskRotator : public PeriodicTask
    {
    public:
        static TaskRotator *Self() { static TaskRotator task; return &task; }
        virtual void RunOnce() override;
    };


    // Вывод лога профилировщика
    class TaskProfilerFull : public PeriodicTask
    {
    public:
        static TaskProfilerFull *Self() { static TaskProfilerFull task; return &task; }
    protected:
        virtual void RunOnce() override;
    };


    // Вывод лога профилировщика для пследнего фрейма
    class TaskProfilerLastFrame : public PeriodicTask
    {
    public:
        static TaskProfilerLastFrame *Self() { static TaskProfilerLastFrame task; return &task; }
        virtual void RunOnce() override;
    };


    // Эта задача периодически выводит время расчёта объектов
    class TaskFPS : public PeriodicTask
    {
    public:
        static TaskFPS *Self() { static TaskFPS task; return &task; }
        virtual void RunOnce() override;
        void BeginFrame() { start = TheTimeMgr->GetMicrosecondCount(); }
        void EndFrame() { end = TheTimeMgr->GetMicrosecondCount(); }
    private:
        uint64 start;
        uint64 end;
    };


    // Трассировка состояния объекта
    class TaskTraceGameObject : public PeriodicTask
    {
    public:
        static TaskTraceGameObject *Self() { static TaskTraceGameObject task; return &task; }
        virtual void RunOnce() override;
        void SetID(int _id) { id = _id; }
    private:
        int id = 0;
    };
}
