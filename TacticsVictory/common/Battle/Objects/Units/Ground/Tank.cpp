// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Tank.h"
#include "Objects/Units/UnitParameters.h"


using namespace Pi;


GameObject *Tank::Create()
{
    Tank *node = new Tank();

    node->SetController(new TankController());

    Model *model = Model::Get(TypeGroundUnit::Tank);

    node->AppendNewSubnode(model);

    return node;
}


TankController::TankController() : GroundUnitController(TypeGroundUnit::Tank, &parameters)
{
}


TankController::TankController(const TankController &controller) : GroundUnitController(controller)
{

}


TankController::~TankController()
{

}


Controller *TankController::Replicate() const
{
    return new TankController(*this);
}


void TankController::Preprocess()
{
    GroundUnitController::Preprocess();
}


NavigatorTank::NavigatorTank(UnitController *controller) : Commander(controller)
{

}


void NavigatorTank::Update(float dT)
{

}


DriverTank::DriverTank(UnitController *controller) : Driver(controller)
{

}


void DriverTank::Update(float dT)
{

}


ShooterTank::ShooterTank(UnitController *controller) : Shooter(controller)
{

}
