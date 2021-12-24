// 2021/12/15 21:25:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/UnitParameters_.h"


using namespace Pi;


GameObject *Robot::Create()
{
    return nullptr;
}


Robot::Robot(int id) : GroundUnitObject(TypeGroundUnit::Robot, id, new RobotController(this))
{
}


RobotController::RobotController(Robot *robot) : GroundUnitController(robot, parameters)
{
}


RobotController::~RobotController()
{
}


void RobotController::Preprocess()
{
    GroundUnitController::Preprocess();
}


CommanderRobot::CommanderRobot(UnitController *controller) : Commander(controller)
{
}


DriverRobot::DriverRobot(UnitController *controller) : Driver(controller)
{
}


ShooterRobot::ShooterRobot(UnitController *controller) : Shooter(controller)
{
}
