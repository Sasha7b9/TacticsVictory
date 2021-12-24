// 2021/12/17 0:00:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Staff/Commander_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Scene/World/Landscape_.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


Commander::Commander(UnitController *_controller) : controller(_controller)
{
    unit = controller->object;
}


Commander *Commander::New(UnitController *controller)
{
    if (controller->BelongAir())
    {
        TypeAirUnit type = controller->GetAirUnitObject()->typeAirUnit;

        if (type == TypeAirUnit::Airplane)         return new CommanderAirplane(controller);
        else if (type == TypeAirUnit::Helicopter)  return new CommanderHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit type = controller->GetGroundUnitObject()->typeGroundUnit;

        if (type == TypeGroundUnit::Robot)     return new CommanderRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new CommanderTank(controller);
        else if (type == TypeGroundUnit::Worm) return new CommanderWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit type = controller->GetWaterUnitObject()->typeWaterUnit;

        if (type == TypeWaterUnit::Boat)           return new CommanderBoat(controller);
        else if (type == TypeWaterUnit::Submarine) return new CommanderSubmarine(controller);
    }

    return nullptr;
}


void Commander::Update(float dT)
{
#ifdef PiSERVER

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

#endif
}


void Commander::AppendRandomTask()
{
    int value = 27;

    if ((rand() % value) == 0)
    {
        Point3D position = unit->GetNodePosition();

        AppendTask(new CommanderTaskDive(Math::RandomFloat(Landscape::self->GetHeightCenter(position.x, position.y), Water::Level())));
    }
    else if ((rand() % value) == 0)
    {
        AppendTask(new CommanderTaskRotate({0.0f, 0.0f, Math::RandomFloat(-K::pi, K::pi)}));
    }
    else if ((rand() % value) == 0)
    {
        Point3D position = unit->GetNodePosition();

        int dX[4] = {0, 0,  1, -1};
        int dY[4] = {1, -1, 0, 0};

        int index = rand() % 4;

        AppendTask(new CommanderTaskMove(position.x + (float)dX[index], position.y + (float)dY[index]));
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
