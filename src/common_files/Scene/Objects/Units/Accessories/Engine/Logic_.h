// 2021/02/27 10:05:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class EngineT;


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

    Vector3 start;      // Если шаг перемещения, то здесь хранится начальная позиция, если шаг поворота - начальный угол
    Vector3 end;        // Если шаг перемещения, то здесь хранится конечная позиция, если шаг поворота - конечный угол

    Type::E type = Type::None;

    bool IsMovement() const { return type == Type::Move; }
    bool IsRotate() const { return type == Type::Rotate; }
};


//----------------------------------------------------------------------------------------------------------------------
// Алгоритм действий - результат деятельности EngineCalculator
class EngineAlgorithm
{
public:

    bool IsFinished() const { return steps.Empty(); }

    List<Step> steps;     // Здесь хранятся шаги алгоритма - от первого к последнему. Когда заканчивается
                          // выполнение шага [0], он удаляется.
};


//----------------------------------------------------------------------------------------------------------------------
//  Рассчитывет алгоритм действий, необходимых для выполнения команды
class EngineCalculator
{
public:

    void Calculate(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);

private:

    void CalculateRotate(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);

    void CalculateMovement(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);
};


//----------------------------------------------------------------------------------------------------------------------
// Выполняет действия, ранее рассчитанные EngineCalculator
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

    // Выполняет текуцщий (т.е. нулевой) шаг алгоритма. Если выполнение шага закончено - возвращает Result::Finished
    Result Execute(ObjectT *object, float timeStep, EngineT &engine);

    Result ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine);

    Result ExecuteMovement(PhysicsParameters &physics, float timeStep, EngineT &engine);
};
