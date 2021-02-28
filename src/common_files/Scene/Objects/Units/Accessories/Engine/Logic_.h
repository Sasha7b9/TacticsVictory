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

    Vector3 start;
    Vector3 end;

    Type::E type = Type::None;
};


//----------------------------------------------------------------------------------------------------------------------
// �������� �������� - ��������� ������������ EngineCalculator
//
class EngineAlgorithm : public Object
{
    URHO3D_OBJECT(EngineAlgorithm, Object);

public:

    EngineAlgorithm(Context *context = TheContext) : Object(context) {}

    bool IsFinished() const { return steps.Empty(); }

    Vector<Step> steps;     // ����� �������� ���� ��������� - �� ������� � ����������. ����� �������������
                            // ���������� ���� [0], �� ���������.
    Vector3 current;        // ������� ������� ��� ���� [0]
};


//----------------------------------------------------------------------------------------------------------------------
//  ����������� ��������, ����������� ����������, ����� ��������� �������
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
*  ��������� ��������, ����� ������������ EngineCalculator
*/
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

    Result Execute(const Step &step, Vector3 &current, float timeStep);
};
