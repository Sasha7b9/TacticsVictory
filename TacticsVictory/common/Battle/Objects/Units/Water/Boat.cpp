// 2021/12/15 21:41:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Boat.h"
#include "Objects/Units/UnitParameters.h"


using namespace Pi;


GameObject *Boat::Create()
{
    return nullptr;
}


BoatController::BoatController() : WaterUnitController(TypeWaterUnit::Boat, &parameters)
{

}


BoatController::BoatController(const BoatController &controller) : WaterUnitController(controller)
{

}


BoatController::~BoatController()
{

}


Controller *BoatController::Replicate() const
{
    return new BoatController(*this);
}


void BoatController::Preprocess()
{
    WaterUnitController::Preprocess();
}


NavigatorBoat::NavigatorBoat(UnitController *controller) : Commander(controller)
{

}


void NavigatorBoat::Update(float dT)
{

}


DriverBoat::DriverBoat(UnitController *controller) : Driver(controller)
{

}


void DriverBoat::Update(float dT)
{

}


ShooterBoat::ShooterBoat(UnitController *controller) : Shooter(controller)
{

}
