// 2021/02/22 15:46:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/Accessories/Accessories_.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Objects/Units/UnitObject_.h"


Vector<UnitObject *> UnitObject::storage;


UnitObjectSpecific::UnitObjectSpecific(UnitObject *object) : GameObjectSpecific(object)
{

}


void UnitObjectSpecific::Update(float timeStep)
{
    GameObjectSpecific::Update(timeStep);
}


UnitObject::UnitObject(Context *context) : GameObject(context)
{

}


void UnitObject::Start()
{
    GameObject::Start();

    node_->SetVar(VAR_NODE_IS_UNIT, true);
}


void UnitObject::Update(float timeStep)
{
    GameObject::Update(timeStep);

    engine->Update(timeStep);

    if (engine->algorithm.IsFinished())
    {
        int direct = Rand() % 4;

        engine->GiveCommand((CommandEngine::E)(direct + 1));
    }
}
