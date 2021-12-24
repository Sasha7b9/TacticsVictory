// 2021/12/15 19:42:11 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Bullet_.h"


using namespace Pi;


GameObject *Bullet::Create()
{
    return nullptr;
}


Bullet::Bullet(int id) : AmmoObject(TypeAmmo::Bullet, id, new BulletController(this))
{
}


BulletController::BulletController(Bullet *bullet) : AmmoController(bullet)
{

}


BulletController::BulletController(const BulletController &controller) : AmmoController(controller)
{

}


BulletController::~BulletController()
{

}


void BulletController::Preprocess()
{
    AmmoController::Preprocess();
}
