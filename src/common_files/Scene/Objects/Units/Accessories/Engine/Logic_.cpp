// 2021/02/27 10:04:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineCalculator::Calculate(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    CalculateRotate(node, command, algorithm);

    CalculateMovement(node, command, algorithm);
}


void EngineCalculator::CalculateRotate(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm)
{

}


void EngineCalculator::CalculateMovement(Node *node, CommandEngine::E command, EngineAlgorithm &algorithm)
{
    Step step(Step::Type::Move);

    step.start = node->GetPosition();
    step.end = step.start;

    if (command == CommandEngine::MoveToNorth)
    {
        step.end.x_ -= 1.0f;
    }
    else if (command == CommandEngine::MoveToEast)
    {
        step.end.z_ += 1.0f;
    }
    else if (command == CommandEngine::MoveToSouth)
    {
        step.end.x_ += 1.0f;
    }
    else if (command == CommandEngine::MoveToWest)
    {
        step.end.z_ -= 1.0f;
    }

    algorithm.steps.Push(step);
}


EngineExecutor::Result EngineExecutor::Execute(Node *node, float timeStep, EngineT &engine)
{
    if (engine.algorithm.IsFinished())
    {
        return EngineExecutor::Result::Finished;
    }

    Step &step = engine.algorithm.steps.Front();

    Vector3 currentPos = node->GetPosition();

    float dist = engine.params->maxSpeedMove * timeStep;            // Нужно проехать

    float delta = (step.end - currentPos).Length();         // Осталось до конечной точки

    if (dist >= delta)                                      // Если проедем больше, чем нужно
    {
        node->SetPosition(step.end);

        return EngineExecutor::Result::Finished;            // То завершаем выполение шага
    }

    Vector3 direction = (step.end - currentPos);
    direction.Normalize();

    node->SetPosition(currentPos + direction * dist);

    return EngineExecutor::Result(EngineExecutor::Result::Running);
}
