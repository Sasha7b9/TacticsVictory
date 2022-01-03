// 2022/1/3 15:59:59 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/World/WorldObject.h"
#include "Objects/Staff/Commander_.h"
#include "Objects/Staff/Driver_.h"


using namespace Pi;


Map<WorldObject> WorldObject::objects;


WorldObject::WorldObject(TypeWorldObject type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::World, params, id),
    typeWorldObject(type)
{
    objects.Insert(this);
}


void WorldObject::Move(float dT)
{
    GameObject::Move(dT);

    commander->Update(dT);

    driver->Update(dT);
}
