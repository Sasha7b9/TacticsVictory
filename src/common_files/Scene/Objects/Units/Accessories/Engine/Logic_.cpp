// 2021/02/27 10:04:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineCalculator::Calculate(Node *node, CommandEngine::E command)
{
    EngineAlgorithm &algorithm = node->GetComponent<EngineT>()->algorithm;

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


EngineExecutor::Result EngineExecutor::Execute(Node * /*_node*/, float /*timeStep*/)
{
    return EngineExecutor::Result(EngineExecutor::Result::Finished);
}
