// 2021/12/15 22:27:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/Laser_.h"


using namespace Pi;


GameObject *Laser::Create()
{
    return nullptr;
}


Laser::Laser(int id) : WeaponObject(TypeWeapon::Laser, &parameters, id)
{
}
