// 2021/12/15 22:27:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Weapons/Laser.h"


using namespace Pi;


GameObject *Laser::Create()
{
    return nullptr;
}


Laser::Laser(int id) : WeaponObject(TypeWeapon::Laser, id, new LaserController(this))
{
}


LaserController::LaserController(Laser *laser) : WeaponController(laser)
{
}


LaserController::~LaserController()
{
}


void LaserController::Preprocess()
{
    WeaponController::Preprocess();
}
