// 2021/12/15 21:18:14 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/UnitParameters_.h"


using namespace Pi;


GameObject *Helicopter::Create()
{
    return nullptr;
}


HelicopterController::HelicopterController(Helicopter *helicopter) :
    AirUnitController(helicopter)
{
}


HelicopterController::HelicopterController(const HelicopterController &controller) : AirUnitController(controller)
{
}


HelicopterController::~HelicopterController()
{
}


void HelicopterController::Preprocess()
{
    AirUnitController::Preprocess();
}


CommanderHelicopter::CommanderHelicopter(UnitController *controller) : Commander(controller)
{
}


DriverHelicopter::DriverHelicopter(UnitController *controller) : Driver(controller)
{
}


ShooterHelicopter::ShooterHelicopter(UnitController *controller) : Shooter(controller)
{
}
