// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Vector<Tank *> Tank::storage;


void Tank::FixedUpdate(float /*time*/)
{

}


void Tank::Start()
{
    UnitObject::Start();

    LoadFromJSON(JSON_MODEL_TANK);

    Normalize();

    storage.Push(this);
}


void Tank::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild(NAME_NODE_TANK);

        TankSpecificPart::Create(node_);
    }

    UnitObject::OnNodeSet(node ? node_ : node);
}


void TankSpecificPart::OnNodeSet(Node *node)
{
    Component::OnNodeSet(node);
}
