// 2021/12/15 19:29:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/Weapon.h"


using namespace Pi;


WeaponObject::WeaponObject(TypeWeapon type, int id, WeaponController *controller) :
    GameObject(TypeGameObject::Weapon, id, controller),
    typeWeapon(type)
{
}



WeaponController::WeaponController(WeaponObject *weapon) : GameObjectController(weapon)
{
}
