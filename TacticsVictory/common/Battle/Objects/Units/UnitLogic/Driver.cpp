// 2021/12/17 0:03:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/UnitLogic/Driver.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/Air/AirUnit.h"
#include "Objects/Units/Ground/GroundUnit.h"
#include "Objects/Units/Water/WaterUnit.h"
#include "Objects/Units/Air/Airplane.h"
#include "Objects/Units/Air/Helicopter.h"
#include "Objects/Units/Ground/Robot.h"
#include "Objects/Units/Ground/Tank.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Boat.h"
#include "Objects/Units/Water/Submarine.h"


using namespace Pi;


Driver::Driver(UnitController *_controller) : controller(_controller)
{
    unit = (UnitObject *)controller->GetTargetNode();
}


Driver::~Driver()
{
    if (tasks.GetElementCount())
    {
        for (const UnitTask *task : tasks)
        {
            delete task;
        }
    }
}


Driver *Driver::New(UnitController *controller)
{
    if (controller->BelongAir())
    {
        TypeAirUnit::S type = ((AirUnitController *)controller)->GetAirUnitObject()->typeAirUnit;

        if (type == TypeAirUnit::Airplane)        return new DriverAirplane(controller);
        else if (type == TypeAirUnit::Helicopter) return new DriverHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit::S type = ((GroundUnitController *)controller)->GetGroundUnitObject()->typeGroundUnit;

        if (type == TypeGroundUnit::Robot)     return new DriverRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new DriverTank(controller);
        else if (type == TypeGroundUnit::Worm) return new DriverWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit::S type = ((WaterUnitController *)controller)->GetWaterUnitObject()->typeWaterUnit;

        if (type == TypeWaterUnit::Boat)           return new DriverBoat(controller);
        else if (type == TypeWaterUnit::Submarine) return new DriverSubmarine(controller);
    }

    return nullptr;
}


void Driver::Update(float dT)
{
    
}


void Driver::AppendTask(const UnitTask *task)
{
    tasks.AddElement(task);
}
