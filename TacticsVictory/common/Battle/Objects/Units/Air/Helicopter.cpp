// 2021/12/15 21:18:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Helicopter.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/UnitParameters.h"


using namespace Pi;


GameObject *Helicopter::Create()
{
    return nullptr;
}


HelicopterController::HelicopterController() : AirUnitController(TypeAirUnit::Helicopter, &parameters)
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


NavigatorHelicopter::NavigatorHelicopter(UnitController *controller) : Commander(controller)
{

}


void NavigatorHelicopter::Update(float dT)
{
    Commander::Update(dT);
}


DriverHelicopter::DriverHelicopter(UnitController *controller) : Driver(controller)
{

}


void DriverHelicopter::Update(float dT)
{

}


ShooterHelicopter::ShooterHelicopter(UnitController *controller) : Shooter(controller)
{

}
