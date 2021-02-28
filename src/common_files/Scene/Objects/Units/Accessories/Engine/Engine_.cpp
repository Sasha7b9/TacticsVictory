// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


void EngineParameters::RegisterObject()
{
    TheContext->RegisterFactory<EngineParameters>();
}


EngineT::EngineT(Context *context) : Component(context)
{

}


void EngineT::RegisterObject()
{
    TheContext->RegisterFactory<EngineT>();

    EngineParameters::RegisterObject();
}


void EngineT::GiveCommand(CommandEngine::E command)
{
    calculator.Calculate(node_, command);
}


bool EngineT::IsStopped() const
{
    EngineParameters *params = GetComponent<EngineParameters>();

    return (params->speedMove == 0.0f) && (params->speedRotate == 0.0f);
}


void EngineT::Update(float timeStep)
{
    if (algorithm.IsFinished())
    {
        return;
    }

    EngineExecutor::Result result = executor.Execute(node_, timeStep);

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
