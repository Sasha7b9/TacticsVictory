// 2021/12/15 19:29:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/Weapon.h"


using namespace Pi;


WeaponObject::WeaponObject(TypeWeapon type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::Weapon, params, id),
    typeWeapon(type)
{
}
