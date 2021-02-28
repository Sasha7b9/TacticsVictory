// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


EngineT::EngineT(Context *context) : Component(context)
{
    algorithm = new EngineAlgorithm();
}


void EngineT::GiveCommand(CommandEngine::E command)
{
    algorithm = calculator.Calculate(physics, command);
}


bool EngineT::IsStopped() const
{
    return physics->speedMove == Vector3::ZERO && physics->speedRotate == Vector3::ZERO;
}


void EngineAir::Update(float /*timeStep*/)
{

}


void EngineGround::Update(float timeStep)
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

    physics->position = algorithm->current;
}


void EngineT::OnNodeSet(Node *node)
{
    if (node)
    {
        Component::OnNodeSet(node);

        physics = node->GetComponent<PhysicsComponent>();
    }
}


void EngineGround::OnNodeSet(Node *node)
{
    if (node)
    {
        EngineT::OnNodeSet(node);
    }
}


EngineT *EngineGround::CreateEngine(Node *node)
{
    return node->CreateComponent<EngineGround>(LOCAL);
}
