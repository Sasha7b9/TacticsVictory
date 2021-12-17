// 2021/12/16 23:57:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class UnitController;
    class UnitObject;
    struct UnitTask;
    class Driver;


    // Класс занимается расчётом перемещений на основе поступающих заданий и окружающей остановки
    class Commander
    {
    public:

        virtual ~Commander() {};

        static Commander *New(UnitController *);

        virtual void Update(float dT);

        void AppendTask(const UnitTask *task) { tasks.AddElement(task); }

        void SetDriver(Driver *_driver) { driver = _driver; }

    protected:

        Commander(UnitController *controller);

        UnitObject *unit = nullptr;
        UnitController *controller = nullptr;
        Driver *driver = nullptr;

        Array<const UnitTask *> tasks;

        // Добавляет случайное задание
        virtual void AppendRandomTask();

        virtual void BreakIntoSteps(const UnitTask *task) const;        // Распарсить задание на шаги

        virtual void ParseMove(const UnitTask *task) const;

        virtual void ParseDive(const UnitTask *task) const;

        virtual void ParseRotate(const UnitTask *task) const;
    };
}
