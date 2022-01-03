// 2021/12/15 22:32:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/GameObject_.h"
#include "Objects/Weapons/RocketLauncher_.h"


using namespace Pi;


GameObject *RocketLauncher::Create()
{
    return nullptr;
}


RocketLauncher::RocketLauncher(int id) : WeaponObject(TypeWeapon::RocketLauncher, &parameters, id)
{
}
