// 2021/12/15 21:32:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/UnitParameters_.h"


using namespace Pi;


GameObject *Worm::Create()
{
    return nullptr;
}


WormController::WormController() : GroundUnitController(TypeGroundUnit::Worm, &parameters)
{

}


WormController::WormController(const WormController &controller) : GroundUnitController(controller)
{

}


WormController::~WormController()
{

}


Controller *WormController::Replicate() const
{
    return new WormController(*this);
}


void WormController::Preprocess()
{
    GroundUnitController::Preprocess();
}


CommanderWorm::CommanderWorm(UnitController *controller) : Commander(controller)
{

}


DriverWorm::DriverWorm(UnitController *controller) : Driver(controller)
{

}


ShooterWorm::ShooterWorm(UnitController *controller) : Shooter(controller)
{

}
