// 2021/02/27 10:05:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Components/PhysicsComponent.h"


struct CommandEngine { enum E {
    None,
    MoveToNorth,
    MoveToEast,
    MoveToSouth,
    MoveToWest
}; };


//----------------------------------------------------------------------------------------------------------------------
// Шаг алгоритма
//
class Step
{
public:

    struct Type { enum E {
        None,
        Move,                   // Движение из точки в точку
        Rotate                  // Поворот от угла к углу
    }; };

    Step(Type::E t = Type::None) : type(t) {}

    Vector3 start;
    Vector3 end;

    Type::E type = Type::None;
};


//----------------------------------------------------------------------------------------------------------------------
// Алгоритм действий - результат деятельности EngineCalculator
//
class EngineAlgorithm : public Object
{
    URHO3D_OBJECT(EngineAlgorithm, Object);

public:

    EngineAlgorithm(Context *context = TheContext) : Object(context) {}

    bool IsFinished() const { return steps.Empty(); }

    Vector<Step> steps;     // Здесь хранятся шаги алгоритма - от первого к последнему. Когда заканчивается
                            // выполнение шага [0], он удаляется.
    Vector3 current;        // Текущая позиция для шага [0]
};


//----------------------------------------------------------------------------------------------------------------------
//  Рассчитывет действия, необходимые произвести, чтобы выполнить команду
//
class EngineCalculator : public Component
{
    URHO3D_OBJECT(EngineCalculator, Component);

public:

    EngineCalculator(Context *context = TheContext) : Component(context) {}

    static void RegisterObject();

    EngineAlgorithm *Calculate(CommandEngine::E command);
};


//----------------------------------------------------------------------------------------------------------------------
/*
*  Выполняет действия, ранее рассчитанные EngineCalculator
*/
class EngineExecutor
{
public:

    struct Result { enum E {
        Running,            // Это значение означает, что следует продолжить выполнение шага
        Finished            // Это значение означает, что выполнение шага завершено
    };
    
        E value;

        Result(E v) : value(v) {}

        bool IsFinished() const { return value == Finished; }
    };

    Result Execute(const Step &step, Vector3 &current, float timeStep);
};
