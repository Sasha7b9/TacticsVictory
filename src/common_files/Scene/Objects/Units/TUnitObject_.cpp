// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/TUnitObject_.h"


Vector<UnitObject *> UnitObject::storage;


UnitObject::UnitObject(Context *context) : GameObject(context)
{
}


void UnitObject::OnNodeSet(Node *node)
{
    GameObject::OnNodeSet(node);

    if (node)
    {
        node->SetVar(VAR_NODE_IS_UNIT, true);
        node->SetVar(VAR_NODE_IS_FLYING, false);
    }
}
