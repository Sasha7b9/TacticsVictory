// 2021/12/15 19:42:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Bullet_.h"


using namespace Pi;


GameObject *Bullet::Create()
{
    return nullptr;
}


BulletController::BulletController() : AmmoController(TypeAmmo::Bullet)
{

}


BulletController::BulletController(const BulletController &controller) : AmmoController(controller)
{

}


BulletController::~BulletController()
{

}


Controller *BulletController::Replicate() const
{
    return new BulletController(*this);
}


void BulletController::Preprocess()
{
    AmmoController::Preprocess();
}
