// 2021/12/15 22:32:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/RocketLauncher.h"


using namespace Pi;


GameObject *RocketLauncher::Create()
{
    return nullptr;
}


RocketLauncher::RocketLauncher(int id) : WeaponObject(TypeWeapon::RocketLauncher, id, new RocketLauncherController(this))
{
}


RocketLauncherController::RocketLauncherController(RocketLauncher *rocketLauncher) :
    WeaponController(rocketLauncher)
{
}


RocketLauncherController::~RocketLauncherController()
{
}


void RocketLauncherController::Preprocess()
{
    WeaponController::Preprocess();
}
