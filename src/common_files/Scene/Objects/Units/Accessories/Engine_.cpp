// 2021/02/26 21:54:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Engine_.h"


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

    }
}


void EngineGround::CreateEngine(Node *node)
{
    node->CreateComponent<EngineGround>();
}
