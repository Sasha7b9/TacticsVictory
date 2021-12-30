// 2021/12/15 19:41:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Ammo_.h"


using namespace Pi;


void AmmoObject::Construct()
{
}


void AmmoObject::Destruct()
{
}


AmmoObject::AmmoObject(TypeAmmo type, const GameObjectParameters *params, int id) :
    GameObject(TypeGameObject::Ammo, params, id),
    typeAmmo(type)
{
}
