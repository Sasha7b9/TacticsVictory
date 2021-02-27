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
// �������� �������� - ��������� ������������ EngineCalculator
//
class EngineAlgorithm : public Object
{
    URHO3D_OBJECT(EngineAlgorithm, Object);

public:

    EngineAlgorithm(Context *context = TheContext) : Object(context) {}
};


//----------------------------------------------------------------------------------------------------------------------
//  ����������� ��������, ����������� ����������, ����� ��������� �������
//
class EngineCalculator
{
public:
    EngineAlgorithm *Calculate(const PhysicsComponent *start, CommandEngine::E command);
};


//----------------------------------------------------------------------------------------------------------------------
/*
*  ��������� ��������, ����� ������������ EngineCalculator
*/
class EngineExecutor
{
public:
    void Execute(SharedPtr<EngineAlgorithm> algorithm);

    SharedPtr<EngineAlgorithm> algorithm;
};
