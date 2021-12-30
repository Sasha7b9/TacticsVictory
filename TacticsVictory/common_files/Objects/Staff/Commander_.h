// 2021/12/16 23:57:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class UnitController;
    struct CommanderTask;
    class Driver;
    class UnitObject;
    class GameObject;


    // Класс занимается расчётом перемещений на основе поступающих заданий и окружающей остановки
    class Commander
    {
    public:

        virtual ~Commander() {};

        void Update(float dT);

        void AppendTask(CommanderTask *task) { tasks.AddElement(task); }

        void SetDriver(Driver *_driver) { driver = _driver; }

        Commander(GameObject *);

        GameObject *object = nullptr;

        Driver *driver = nullptr;

    private:

        Array<CommanderTask *> tasks;

        // Добавляет случайное задание
        virtual void AppendRandomTask();
    };
}
