// 2021/02/22 21:04:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Weapons/_TWeaponObject.h"


Vector<WeaponObject *> WeaponObject::storage;


WeaponObject::WeaponObject() : GameObject()
{
    storage.Push(this);
}
