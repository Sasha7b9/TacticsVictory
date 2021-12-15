// 2021/12/15 22:27:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/Laser.h"


using namespace Pi;


GameObject *Laser::Create()
{
    return nullptr;
}


LaserController::LaserController() : WeaponController(TTypeWeapon::Laser)
{

}


LaserController::LaserController(const LaserController &controller) : WeaponController(controller)
{

}


LaserController::~LaserController()
{

}


Controller *LaserController::Replicate() const
{
    return new LaserController(*this);
}


void LaserController::Preprocess()
{
    WeaponController::Preprocess();
}
