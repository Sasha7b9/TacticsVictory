// 2021/12/15 21:25:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Robot.h"


using namespace Pi;


GameObject *Robot::Create()
{
    return nullptr;
}


RobotController::RobotController() : GroundUnitController(TTypeGroundUnit::Robot)
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
