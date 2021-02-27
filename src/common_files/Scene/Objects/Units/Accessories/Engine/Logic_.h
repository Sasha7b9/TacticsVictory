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
// Алгоритм действий - результат деятельности EngineCalculator
//
class EngineAlgorithm : public Object
{
    URHO3D_OBJECT(EngineAlgorithm, Object);

public:

    EngineAlgorithm(Context *context = TheContext) : Object(context) {}
};


//----------------------------------------------------------------------------------------------------------------------
//  Рассчитывет действия, необходимые произвести, чтобы выполнить команду
//
class EngineCalculator
{
public:
    EngineAlgorithm *Calculate(const PhysicsComponent *start, CommandEngine::E command);
};


//----------------------------------------------------------------------------------------------------------------------
/*
*  Выполняет действия, ранее рассчитанные EngineCalculator
*/
class EngineExecutor
{
public:
    void Execute(SharedPtr<EngineAlgorithm> algorithm);

    SharedPtr<EngineAlgorithm> algorithm;
};
