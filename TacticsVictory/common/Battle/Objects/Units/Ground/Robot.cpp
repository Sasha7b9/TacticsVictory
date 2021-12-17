// 2021/12/15 21:25:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Robot.h"
#include "Objects/Units/UnitParameters.h"


using namespace Pi;


GameObject *Robot::Create()
{
    return nullptr;
}


RobotController::RobotController() : GroundUnitController(TypeGroundUnit::Robot, &parameters)
{

}


RobotController::RobotController(const RobotController &controller) : GroundUnitController(controller)
{

}


RobotController::~RobotController()
{

}


Controller *RobotController::Replicate() const
{
    return new RobotController(*this);
}


void RobotController::Preprocess()
{
    GroundUnitController::Preprocess();
}


NavigatorRobot::NavigatorRobot(UnitController *controller) : Commander(controller)
{

}


void NavigatorRobot::Update(float dT)
{

}


DriverRobot::DriverRobot(UnitController *controller) : Driver(controller)
{

}


void DriverRobot::Update(float dT)
{

}


ShooterRobot::ShooterRobot(UnitController *controller) : Shooter(controller)
{

}
