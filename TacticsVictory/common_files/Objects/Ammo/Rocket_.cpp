// 2021/12/15 19:42:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Ammo/Rocket_.h"


using namespace Pi;


GameObject *Rocket::Create()
{
    return nullptr;
}


RocketController::RocketController() : AmmoController(TypeAmmo::Rocket)
{

}


RocketController::RocketController(const RocketController &controller) : AmmoController(controller)
{

}


RocketController::~RocketController()
{

}


Controller *RocketController::Replicate() const
{
    return new RocketController(*this);
}


void RocketController::Preprocess()
{
    AmmoController::Preprocess();
}
