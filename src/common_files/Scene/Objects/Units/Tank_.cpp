// 2021/02/22 15:40:32 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"
#include "Scene/Objects/Units/Tank_.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


Vector<Tank *> Tank::storage;


void Tank::RegisterObject()
{
    TheContext->RegisterFactory<Tank>();
}


void Tank::FixedUpdate(float /*time*/)
{

}


void Tank::Start()
{
    UnitObject::Start();

    LoadFromJSON(JSON_MODEL_TANK);

    Normalize();

    specific->Start(node_);

    storage.Push(this);

    SubscribeToEvent(EU_MOUSE_CLICK, URHO3D_HANDLER(Tank, HandleMouseClick));
}


void Tank::OnNodeSet(Node *node)
{
    if (node)
    {
        node_ = node->CreateChild(NAME_NODE_TANK);
    }

    UnitObject::OnNodeSet(node ? node_ : node);
}
