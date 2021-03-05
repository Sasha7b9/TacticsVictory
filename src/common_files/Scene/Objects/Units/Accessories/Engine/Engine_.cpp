// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineT::EngineT(ObjectT *_object) : Object(TheContext), object(_object)
{
    params = new EngineParameters();
};


void EngineT::GiveCommand(CommandEngine::E command)
{
    calculator.Calculate(object, command, algorithm);
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

    EngineExecutor::Result result = executor.Execute(object->GetNode(), timeStep, *this);

    if (result.IsFinished())
    {
        algorithm.steps.PopFront();
    }
}
