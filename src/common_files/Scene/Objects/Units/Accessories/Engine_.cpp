// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine_.h"


void EngineT::GiveCommand(Command::E /*command*/)
{

}


bool EngineT::IsStopped() const
{
    return true;
}


void EngineAir::Update(float /*timeStep*/)
{

}


void EngineGround::Update(float /*timeStep*/)
{

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
    return node->CreateComponent<EngineGround>();
}
