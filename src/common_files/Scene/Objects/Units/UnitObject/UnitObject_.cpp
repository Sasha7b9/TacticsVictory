// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObject/UnitObject_.h"


Vector<UnitObject *> UnitObject::storage;


UnitObject::UnitObject(Context *context) : GameObject(context)
{

}


void UnitObject::RegisterObject()
{
    UnitObjectSpecific::RegisterObject();

    Accessories::RegisterObject();

    Tank::RegisterObject();
}


void UnitObject::Start()
{
    GameObject::Start();

    node_->SetVar(VAR_NODE_IS_UNIT, true);
}


void UnitObject::Update(float timeStep)
{
    GameObject::Update(timeStep);
}
