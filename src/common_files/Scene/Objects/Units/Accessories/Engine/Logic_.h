// 2021/02/27 10:05:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class EngineT;
class Unit;


struct CommandEngine { enum E {
    None,
    MoveToNorth,
    MoveToNorthEast,
    MoveToEast,
    MoveToEastSouth,
    MoveToSouth,
    MoveToSouthWest,
    MoveToWest,
    MoveToWestNorth
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

    Vector3 endPos;     // Если шаг перемещения, то здесь хранится конечная позиция, если шаг поворота - координаты
                        // точки, к которой необходимо повернуться

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

    Step &GetStep() { return steps.Front(); }

    List<Step> steps;     // Здесь хранятся шаги алгоритма - от первого к последнему. Когда заканчивается
                          // выполнение шага [0], он удаляется.
};


//----------------------------------------------------------------------------------------------------------------------
//  Рассчитывет алгоритм действий, необходимых для выполнения команды
class EngineCalculator
{
public:

    void Calculate(Unit &unit, CommandEngine::E command, int count, EngineAlgorithm &algorithm);

private:

    // Возвращает false, если поворот не нужен (юнит всё равно туда не проедет)
    bool CalculateRotate(Unit &unit, CommandEngine::E command, EngineAlgorithm &algorithm);

    void CalculateMovement(Unit &unit, CommandEngine::E command, int count, EngineAlgorithm &algorithm);
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
    Result Execute(Unit &unit, float dT);

    Result ExecuteRotate(Unit &unit, float dT);

    Result ExecuteMovement(Unit &unit, float dT);
};
