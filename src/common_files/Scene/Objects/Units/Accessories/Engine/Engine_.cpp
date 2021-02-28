// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine/Engine_.h"
#include "Scene/Objects/Units/Accessories/Engine/Logic_.h"


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


void EngineGround::Update(float /*timeStep*/)
{

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
