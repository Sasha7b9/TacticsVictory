// 2021/12/15 19:41:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Ammo.h"


using namespace Pi;


void AmmoObject::Construct()
{

}


void AmmoObject::Destruct()
{

}


AmmoController::AmmoController(PiTypeController::S type) : GameObjectController(TypeGameObject::Ammo, type)
{

}
