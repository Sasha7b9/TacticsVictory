// 2021/12/15 19:42:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Rocket_.h"


using namespace Pi;


GameObject *Rocket::Create()
{
    return nullptr;
}


Rocket::Rocket(int id) : AmmoObject(TypeAmmo::Rocket, &parameters, id)
{
}
