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

    void Calculate(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm);

private:

    void CalculateRotate(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm);

    void CalculateMovement(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm);
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
    Result Execute(Node *_node, float timeStep, EngineT &engine);
};
