// 2021/12/30 13:50:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class Commander;
    class GameObject;


    // Цельное задание для юнита, которое должно быть разбито на более мелкие конкретные задания StepUnitTask
    struct CommanderTask
    {
        enum class Type
        {
            Test,
            Move,           // Двигаться в точку
            Dive,           // Погружение на глубину
            Rotate,         // Вращение
            FreeFlight,     // Режим "свободного полёта"
            Count
        };

        enum class Mode
        {
            Absolute,
            Relative
        };

        Type  type;
        Mode  mode;

        Point3D destination = Point3D::ZERO;    // Точка целевого назначения - для перемещения координаты, для вращения - угол

        virtual ~CommanderTask() { }

        void SetGameObject(GameObject *_object) { object = _object; }

        virtual void RunStep(float dT) = 0;

        bool Complete() const { return complete; }

    protected:

        CommanderTask(Type _type, Mode _mode) : type(_type), mode(_mode) { }

        bool complete = false;

        GameObject *object = nullptr;
    };


    struct CommanderTaskTest : public CommanderTask
    {
        /* Задание заключается в следующем:
        *  1. Юнит едет/плывёт/летит вперёд.
        *  2. При появлении препятствия поворачивает направо
        *  3. При появлении в радиусе действия оружия противника стреляет
        *  4. Преследование цели не ведётся
        */ 
        CommanderTaskTest() : CommanderTask(Type::Test, Mode::Absolute) { }

        virtual void RunStep(float dT) override;
    };


    struct CommanderTaskDive : public CommanderTask
    {
        CommanderTaskDive(float depth) : CommanderTask(Type::Dive, Mode::Absolute)
        {
            destination.z = depth;
        }

        virtual void RunStep(float dT) override { }
    };


    struct CommanderTaskRotate : public CommanderTask
    {
        CommanderTaskRotate(const Point3D &_angle) : CommanderTask(Type::Rotate, Mode::Relative)
        {
            destination = _angle;
        }

        virtual void RunStep(float dT) override { }
    };


    struct CommanderTaskMove : public CommanderTask
    {
        CommanderTaskMove(float x, float y) : CommanderTask(Type::Move, Mode::Absolute)
        {
            destination.x = x;
            destination.y = y;
        }

        virtual void RunStep(float dT) override { }
    };
}
