// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/UnitsEvents_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"


Vector<Tank *> Tank::storage;


Tank::Tank(Context *context) : UnitObject(context)
{

}


void Tank::FixedUpdate(float /*time*/)
{

}


void Tank::Start()
{
    UnitObject::Start();

    node_->SetVar(VAR_NODE_IS_FLYING, false);

    LoadFromJSON(JSON_MODEL_TANK);

    Normalize();

    storage.Push(this);

    TankSpecificPart::Create(node_);
}


void Tank::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild(NAME_NODE_TANK);
    }

    UnitObject::OnNodeSet(node ? node_ : node);
}
