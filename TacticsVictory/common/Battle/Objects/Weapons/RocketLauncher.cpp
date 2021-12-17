// 2021/12/15 22:32:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/RocketLauncher.h"


using namespace Pi;


GameObject *RocketLauncher::Create()
{
    return nullptr;
}


RocketLauncherController::RocketLauncherController() : WeaponController(TypeWeapon::RocketLauncher)
{

}


RocketLauncherController::RocketLauncherController(const RocketLauncherController &controller) :
    WeaponController(controller)
{

}


RocketLauncherController::~RocketLauncherController()
{

}


Controller *RocketLauncherController::Replicate() const
{
    return new RocketLauncherController(*this);
}


void RocketLauncherController::Preprocess()
{
    WeaponController::Preprocess();
}
