// 2021/12/16 1:29:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    struct UnitTask
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

        UnitTask(Type _type, Mode _mode) : type(_type), mode(_mode) {};
    };


    struct DiveUnitTaskAbs : public UnitTask
    {
        DiveUnitTaskAbs(float depth) : UnitTask(Type::Dive, Mode::Absolute)  { destination.z = depth; }
    };


    struct RotateUnitTaskRel : public UnitTask
    {
        RotateUnitTaskRel(const Point3D _angle) : UnitTask(Type::Rotate, Mode::Relative) { destination = _angle; }
    };
}
