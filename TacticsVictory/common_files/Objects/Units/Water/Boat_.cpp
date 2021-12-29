// 2021/12/15 21:41:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/UnitParameters_.h"


using namespace Pi;


GameObject *Boat::Create()
{
    return nullptr;
}


Boat::Boat(int id) : WaterUnitObject(TypeWaterUnit::Boat, id, new BoatController(this))
{
}


BoatController::BoatController(Boat *boat) : WaterUnitController(boat)
{
}


BoatController::~BoatController()
{
}


void BoatController::Preprocess()
{
    WaterUnitController::Preprocess();
}


CommanderBoat::CommanderBoat(UnitController *controller) : Commander(controller)
{
}


DriverBoat::DriverBoat(UnitController *controller) : Driver(controller)
{
}


ShooterBoat::ShooterBoat(UnitController *controller) : Shooter(controller)
{
}
