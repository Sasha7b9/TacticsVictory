// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Unit_.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineT::EngineT(Unit *_unit) : Object(TheContext), unit(_unit)
{

};


void EngineT::GiveCommand(CommandEngine::E command, int count)
{
    calculator.Calculate(*unit, command, count, algorithm);
}


bool EngineT::IsStopped() const
{
    return (unit->physics->mov.GetSpeed() == 0.0f) &&
        (unit->physics->rot.GetSpeed() == 0.0f);
}


void EngineT::Update(float timeStep)
{
    if (algorithm.IsFinished())
    {
        return;
    }

    EngineExecutor::Result result = executor.Execute(*unit, timeStep);

    if (result.IsFinished())
    {
        algorithm.steps.PopFront();
    }
}
