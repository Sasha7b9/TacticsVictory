// 2021/12/25 19:32:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class PeriodicTask : public ListElement<PeriodicTask>
    {
    public:

        void Setup(uint periodMS, int times = -1);
        void Update();
        bool Complete() const { return complete; };

    protected:

        bool complete = false;

        uint nextTime = 0;          // Следующее время передачи
        uint period = 1000;
        int times = -1;             // Сколько раз выполнить. Если -1 - бесконечно

        virtual void RunOnce() = 0;
    };


    class ListPeriodicTask
    {
    public:
        static ListPeriodicTask *Self()
        {
            static ListPeriodicTask tasks;
            return &tasks;
        }
        void Append(PeriodicTask *task, uint period, int times = -1);
        void Remove(PeriodicTask *task);
        bool Consist(PeriodicTask *task);
        void Run();
        void Purge();
    private:
        List<PeriodicTask> tasks;
    };


    class TaskTraffic : public PeriodicTask
    {
    public:
        static TaskTraffic *Self() { static TaskTraffic task; return &task; }
    protected:
        virtual void RunOnce() override;
    };
}
