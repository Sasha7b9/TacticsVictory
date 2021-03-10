// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineT::EngineT(ObjectT *_object) : Object(TheContext), object(_object)
{

};


void EngineT::GiveCommand(CommandEngine::E command, int count)
{
    calculator.Calculate(*object->physics, command, count, algorithm);
}


bool EngineT::IsStopped() const
{
    return (object->physics->mov.GetSpeed() == 0.0f) &&
        (object->physics->rot.GetSpeed() == 0.0f);
}


void EngineT::Update(float timeStep)
{
    if (algorithm.IsFinished())
    {
        return;
    }

    EngineExecutor::Result result = executor.Execute(*object->physics, timeStep, *this);

    if (result.IsFinished())
    {
        algorithm.steps.PopFront();
    }
}
