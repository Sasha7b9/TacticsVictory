// 2021/12/15 21:18:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Helicopter.h"


using namespace Pi;


GameObject *Helicopter::Create()
{
    return nullptr;
}


HelicopterController::HelicopterController() : AirUnitController(TTypeAirUnit::Helicopter)
{

}


HelicopterController::HelicopterController(const HelicopterController &controller) : AirUnitController(controller)
{

}


HelicopterController::~HelicopterController()
{

}


Controller *HelicopterController::Replicate() const
{
    return new HelicopterController(*this);
}


void HelicopterController::Preprocess()
{
    AirUnitController::Preprocess();
}
