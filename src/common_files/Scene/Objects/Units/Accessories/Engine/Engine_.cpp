// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineT::EngineT(Context *context) : Component(context)
{
    algorithm = new EngineAlgorithm();
}


void EngineT::RegisterObject()
{
    TheContext->RegisterFactory<EngineT>();
}


void EngineT::GiveCommand(CommandEngine::E command)
{
    algorithm = calculator.Calculate(command);
}


bool EngineT::IsStopped() const
{
    return physics->speedMove == Vector3::ZERO && physics->speedRotate == Vector3::ZERO;
}


void EngineT::Update(float timeStep)
{
    if (algorithm->IsFinished())
    {
        return;
    }

    EngineExecutor::Result result = executor.Execute(algorithm->steps[0], algorithm->current, timeStep);

    if (result.IsFinished())
    {
        algorithm->steps.Erase(0);
    }

    node_->SetPosition(algorithm->current);
}


void EngineT::OnNodeSet(Node *node)
{
    Component::OnNodeSet(node);
}


void EngineT::OnNodeSet(Node *node)
{
    if (node)
    {
        EngineT::OnNodeSet(node);
    }
}
