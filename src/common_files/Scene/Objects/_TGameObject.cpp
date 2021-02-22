// 2021/02/18 22:31:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/_TGameObject.h"


Vector<GameObject *> GameObject::storage;


GameObject::GameObject() : Object(TheContext)
{
    storage.Push(this);
}
