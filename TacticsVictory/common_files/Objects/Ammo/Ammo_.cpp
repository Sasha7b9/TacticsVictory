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


AmmoObject::AmmoObject(TypeAmmo type, int id, AmmoController *controller) :
    GameObject(TypeGameObject::Ammo, id, controller),
    typeAmmo(type)
{
}



AmmoController::AmmoController(AmmoObject *object) : GameObjectController(object)
{
}
