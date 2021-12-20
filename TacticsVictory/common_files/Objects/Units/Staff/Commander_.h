// 2021/12/16 23:57:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class UnitController;
    class UnitObject;
    class Driver;


    // Цельное задание для юнита, которое должно быть разбито на более мелкие конкретные задания StepUnitTask
    struct CommanderTask
    {
        enum class Mode
        {
            Absolute,
            Relative
        };

        enum class Type
        {
            Move,       // Двигаться в точку
            Dive,       // Погружение на глубину
            Rotate,     // Вращение
            Count
        };

        Type  type;
        Mode  mode;

        Point3D destination;    // Точка целевого назначения - для перемещения координаты, для вращения - угол

    protected:

        CommanderTask(Type _type, Mode _mode) : type(_type), mode(_mode) { };
    };


    struct CommanderTaskDive : public CommanderTask
    {
        CommanderTaskDive(float depth) : CommanderTask(Type::Dive, Mode::Absolute)
        {
            destination.z = depth;
        }
    };


    struct CommanderTaskRotate : public CommanderTask
    {
        CommanderTaskRotate(const Point3D &_angle) : CommanderTask(Type::Rotate, Mode::Relative)
        {
            destination = _angle;
        }
    };


    struct CommanderTaskMove : public CommanderTask
    {
        CommanderTaskMove(float x, float y) : CommanderTask(Type::Move, Mode::Absolute)
        {
            destination.x = x;
            destination.y = y;
        }
    };


    // Класс занимается расчётом перемещений на основе поступающих заданий и окружающей остановки
    class Commander
    {
    public:

        virtual ~Commander() {};

        static Commander *New(UnitController *);

        void Update(float dT);

        void AppendTask(const CommanderTask *task) { tasks.AddElement(task); }

        void SetDriver(Driver *_driver) { driver = _driver; }

    protected:

        Commander(UnitController *controller);

        UnitObject *unit = nullptr;
        UnitController *controller = nullptr;
        Driver *driver = nullptr;

        Array<const CommanderTask *> tasks;

        // Добавляет случайное задание
        virtual void AppendRandomTask();

        virtual void BreakIntoSteps(const CommanderTask *task) const;        // Распарсить задание на шаги

        virtual void ParseMove(const CommanderTask *task) const;

        virtual void ParseDive(const CommanderTask *task) const;

        virtual void ParseRotate(const CommanderTask *task) const;
    };
}
