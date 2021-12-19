// 2021/12/17 0:00:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Staff/Commander.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/Air/AirUnit.h"
#include "Objects/Units/Ground/GroundUnit.h"
#include "Objects/Units/Water/WaterUnit.h"
#include "Objects/Units/Air/Airplane.h"
#include "Objects/Units/Air/Helicopter.h"
#include "Objects/Units/Water/Boat.h"
#include "Objects/Units/Ground/Robot.h"
#include "Objects/Units/Ground/Tank.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Submarine.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


Commander::Commander(UnitController *_controller) : controller(_controller)
{
    unit = (UnitObject *)controller->GetTargetNode();
}


Commander *Commander::New(UnitController *controller)
{
    if (controller->BelongAir())
    {
        TypeAirUnit::S type = ((AirUnitController *)controller)->GetAirUnitObject()->typeAirUnit;

        if (type == TypeAirUnit::Airplane)         return new NavigatorAirplane(controller);
        else if (type == TypeAirUnit::Helicopter)  return new NavigatorHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit::S type = ((GroundUnitController *)controller)->GetGroundUnitObject()->typeGroundUnit;

        if (type == TypeGroundUnit::Robot)     return new NavigatorRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new NavigatorTank(controller);
        else if (type == TypeGroundUnit::Worm) return new NavigatorWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit::S type = ((WaterUnitController *)controller)->GetWaterUnitObject()->typeWaterUnit;

        if (type == TypeWaterUnit::Boat)           return new NavigatorBoat(controller);
        else if (type == TypeWaterUnit::Submarine) return new CommanderSubmarine(controller);
    }

    return nullptr;
}


void Commander::Update(float dT)
{
    while (!tasks.Empty())
    {
        const CommanderTask *task = tasks[0];

        BreakIntoSteps(task);

        delete task;

        tasks.RemoveElement(0);
    }

    if (driver->EmptyTaskList())
    {
        AppendRandomTask();
    }
}


void Commander::AppendRandomTask()
{
    int value = 127;

    if ((rand() % value) == 0)
    {
        Point3D position = unit->GetNodePosition();

        AppendTask(new CommanderTaskDive(Math::RandomFloat(GameWorld::self->GetLandscape()->GetHeightCenter(position.x, position.y), Water::Level())));
    }
    else if ((rand() % value) == 0)
    {
        AppendTask(new CommanderTaskRotate({0.0f, 0.0f, Math::RandomFloat(-K::pi, K::pi)}));
    }
}


void Commander::BreakIntoSteps(const CommanderTask *task) const
{
    if (!controller->CanExecute(task->type))
    {
//        LOG_ERROR("Can not process task %d", task->type);
        return;
    }

    if (task->type == CommanderTask::Type::Move)
    {
        ParseMove(task);
    }
    else if (task->type == CommanderTask::Type::Dive)
    {
        ParseDive(task);
    }
    else if (task->type == CommanderTask::Type::Rotate)
    {
        ParseRotate(task);
    }
    else
    {
        LOG_ERROR("Not processed task");
    }
}


void Commander::ParseMove(const CommanderTask *task) const
{
//    LOG_ERROR("Empty function %s", __FUNCTION__);
}


void Commander::ParseDive(const CommanderTask *task) const
{
//    LOG_ERROR("Empty function %s", __FUNCTION__);
}


void Commander::ParseRotate(const CommanderTask *task) const
{
//    LOG_ERROR("Empty function %s", __FUNCTION__);
}
