// 2021/12/17 0:03:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Staff/Driver_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Air/Helicopter_.h"
#include "Objects/Units/Ground/Robot_.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/Ground/Worm.h"
#include "Objects/Units/Water/Boat_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Utils/Math_.h"
#include "Objects/Units/Staff/DriverTasks_.h"


using namespace Pi;


Driver::Driver(UnitController *_controller) : controller(_controller), unit(controller->object), param(controller->param)
{
}


Driver::~Driver()
{
    if (tasks.GetElementCount())
    {
        for (const DriverTask *task : tasks)
        {
            delete task;
        }
    }
}


Driver *Driver::Create(UnitController *controller)
{
    if (controller->BelongAir())
    {
        TypeAirUnit type = ((AirUnitController *)controller)->GetAirUnitObject()->typeAirUnit; //-V522

        if (type == TypeAirUnit::Airplane)        return new Driver(controller);
        else if (type == TypeAirUnit::Helicopter) return new DriverHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit type = ((GroundUnitController *)controller)->GetGroundUnitObject()->typeGroundUnit; //-V522

        if (type == TypeGroundUnit::Robot)     return new DriverRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new DriverTank(controller);
        else if (type == TypeGroundUnit::Worm) return new DriverWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit type = ((WaterUnitController *)controller)->GetWaterUnitObject()->typeWaterUnit; //-V522

        if (type == TypeWaterUnit::Boat)           return new DriverBoat(controller);
        else if (type == TypeWaterUnit::Submarine) return new DriverSubmarine(controller);
    }

    return nullptr;
}


void Driver::Update(float dT)
{
    if (!tasks.Empty())
    {
        DriverTask *task = tasks[0];

        task->RunStep(dT);

        if (task->Completed())
        {
            delete task;
            tasks.RemoveElement(0);
        }

        ApplyTransform();
    }
}


void Driver::ApplyTransform()
{
    if (param->applyRotate)
    {
        param->applyRotate = false;

#ifdef PiCLIENT

        unit->SetDirection(param->direction, param->up);

        unit->Invalidate();
#endif
    }

    if (param->applyTranslation)
    {
        param->applyTranslation = false;

#ifdef PiCLIENT

        param->stat.distance += Magnitude(unit->GetNodePosition() - param->position);

        Node *node = unit;

        node->SetNodePosition(param->position);

        node->Invalidate();
#endif
    }
}


void Driver::MoveForward(float dT)
{
    if(param->speed != 0.0f)
    {
        param->position += param->direction * param->speed * dT;

        param->applyTranslation = true;
    }
}


void Driver::RotateYaw(float dT)
{
    if(param->speedRotate.z != 0.0f)
    {
        param->direction.RotateAboutAxis(param->speedRotate.z * dT, param->up);

        param->applyRotate = true;
    }
}


void Driver::RotateYawCompensate(float dT)
{
    if(param->speedRotate.z != 0.0f)
    {
        param->direction.RotateAboutAxis(param->speedRotate.z * dT, param->upPitch);

        param->applyRotate = true;
    }
}


void Driver::RotateRoll(float dT)
{
    if(param->speedRotate.y != 0.0f)
    {
        param->up.RotateAboutAxis(-param->speedRotate.y * dT, param->direction);

        param->applyRotate = true;
    }
}


void Driver::RotatePitch(float dT)
{
    if(param->speedRotate.x != 0.0f)
    {
        float angle = param->speedRotate.x * dT;

        Vector3D axis = Cross(param->direction, param->up).Normalize();

        param->direction.RotateAboutAxis(angle, axis);
        param->up.RotateAboutAxis(angle, axis);
        param->upPitch.RotateAboutAxis(angle, axis);

        param->applyRotate = true;
    }
}


void Driver::RotatePitchCompensate(float dT)
{
    if(param->speedRotate.x != 0.0f)
    {
        float angle = param->speedRotate.x * dT;

        Vector3D axis = Cross(param->direction, param->upPitch).Normalize();

        param->direction.RotateAboutAxis(angle, axis);
        param->up.RotateAboutAxis(angle, axis);
        param->upPitch.RotateAboutAxis(angle, axis);

        param->applyRotate = true;
    }
}


void Driver::AppendTask(DriverTask *task)
{
    tasks.AddElement(task);
}

