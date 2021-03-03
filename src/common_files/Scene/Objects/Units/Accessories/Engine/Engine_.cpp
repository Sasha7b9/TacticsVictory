// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineT::GiveCommand(CommandEngine::E command)
{
    calculator.Calculate(node, command, algorithm);
}


bool EngineT::IsStopped() const
{
    return (params->speedMove == 0.0f) && (params->speedRotate == 0.0f);
}


void EngineT::Update(float timeStep)
{
    if (algorithm.IsFinished())
    {
        return;
    }

    EngineExecutor::Result result = executor.Execute(node, timeStep, *this);

    if (result.IsFinished())
    {
        algorithm.steps.PopFront();
    }
}
