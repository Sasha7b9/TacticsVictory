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
// ��� ���������
//
class Step
{
public:

    struct Type { enum E {
        None,
        Move,                   // �������� �� ����� � �����
        Rotate                  // ������� �� ���� � ����
    }; };

    Step(Type::E t = Type::None) : type(t) {}

    Vector3 start;      // ���� ��� �����������, �� ����� �������� ��������� �������, ���� ��� �������� - ��������� ����
    Vector3 end;        // ���� ��� �����������, �� ����� �������� �������� �������, ���� ��� �������� - �������� ����

    Type::E type = Type::None;

    bool IsMovement() const { return type == Type::Move; }
    bool IsRotate() const { return type == Type::Rotate; }
};


//----------------------------------------------------------------------------------------------------------------------
// �������� �������� - ��������� ������������ EngineCalculator
class EngineAlgorithm
{
public:

    bool IsFinished() const { return steps.Empty(); }

    List<Step> steps;     // ����� �������� ���� ��������� - �� ������� � ����������. ����� �������������
                          // ���������� ���� [0], �� ���������.
};


//----------------------------------------------------------------------------------------------------------------------
//  ����������� �������� ��������, ����������� ��� ���������� �������
class EngineCalculator
{
public:

    void Calculate(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);

private:

    void CalculateRotate(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);

    void CalculateMovement(ObjectT *object, CommandEngine::E command, EngineAlgorithm &algorithm);
};


//----------------------------------------------------------------------------------------------------------------------
// ��������� ��������, ����� ������������ EngineCalculator
class EngineExecutor
{
public:

    struct Result { enum E {
        Running,            // ��� �������� ��������, ��� ������� ���������� ���������� ����
        Finished            // ��� �������� ��������, ��� ���������� ���� ���������
    };
    
        E value;

        Result(E v) : value(v) {}

        bool IsFinished() const { return value == Finished; }
    };

    // ��������� �������� (�.�. �������) ��� ���������. ���� ���������� ���� ��������� - ���������� Result::Finished
    Result Execute(ObjectT *object, float timeStep, EngineT &engine);

    Result ExecuteRotate(PhysicsParameters &physics, float timeStep, EngineT &engine);

    Result ExecuteMovement(PhysicsParameters &physics, float timeStep, EngineT &engine);
};
