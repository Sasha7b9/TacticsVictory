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


using namespace Pi;


Driver::Driver(UnitController *_controller) : controller(_controller)
{
    unit = controller->object;
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
        TypeAirUnit type = ((AirUnitController *)controller)->GetAirUnitObject()->typeAirUnit;

        if (type == TypeAirUnit::Airplane)        return new DriverAirplane(controller);
        else if (type == TypeAirUnit::Helicopter) return new DriverHelicopter(controller);
    }
    else if (controller->BelongGround())
    {
        TypeGroundUnit type = ((GroundUnitController *)controller)->GetGroundUnitObject()->typeGroundUnit;

        if (type == TypeGroundUnit::Robot)     return new DriverRobot(controller);
        else if (type == TypeGroundUnit::Tank) return new DriverTank(controller);
        else if (type == TypeGroundUnit::Worm) return new DriverWorm(controller);
    }
    else if (controller->BelongWater())
    {
        TypeWaterUnit type = ((WaterUnitController *)controller)->GetWaterUnitObject()->typeWaterUnit;

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
    }
}


void Driver::MoveForward(float dT)
{
    UnitParameters &param = controller->param;

    Point3D position = unit->GetNodePosition() + param.direction * param.speed;

    unit->SetNodePosition(position);

    unit->Invalidate();
}


void Driver::Yaw(float dT)
{
    UnitParameters &param = controller->param;

    param.direction.RotateAboutAxis(param.speedRotate.z * dT, param.up);
}


void Driver::YawCompensate(float dT)
{
    UnitParameters &param = controller->param;

    param.direction.RotateAboutAxis(param.speedRotate.z * dT, param.upPitch);
}


void Driver::Roll(float dT)
{
    UnitParameters &param = controller->param;

    param.up.RotateAboutAxis(-param.speedRotate.y * dT, param.direction);
}


void Driver::Pitch(float dT)
{
    UnitParameters &param = controller->param;

    Vector3D axis = Cross(param.direction, param.up).Normalize();

    float angle = controller->param.speedRotate.x * dT;

    param.direction.RotateAboutAxis(angle, axis);
    param.up.RotateAboutAxis(angle, axis);
    param.upPitch.RotateAboutAxis(angle, axis);
}


void Driver::PitchCompensate(float dT)
{
    UnitParameters &param = controller->param;

    Vector3D axis = Cross(param.direction, param.upPitch).Normalize();

    float angle = controller->param.speedRotate.x * dT;

    param.direction.RotateAboutAxis(angle, axis);
    param.up.RotateAboutAxis(angle, axis);
    param.upPitch.RotateAboutAxis(angle, axis);
}


void Driver::AppendTask(DriverTask *task)
{
    tasks.AddElement(task);
}


DriverTask::DriverTask(Driver *driver) : controller(driver->controller)
{
    unit = controller->object;
}


DriverTaskDive::DriverTaskDive(Driver *driver, float z) : DriverTask(driver), destination_z(z)
{
    position_z = unit->GetNodePosition().z;
    speed = Fsgn(destination_z - position_z) > 0 ? controller->param.max.speed.z : -controller->param.max.speed.z;
}


void DriverTaskDive::RunStep(float dT)
{
    Point3D position = unit->GetNodePosition();

    position_z = position.z;

    float delta_before = destination_z - position_z;

    position_z += speed * dT;

    float delta_after = destination_z - position_z;

    if (Fsgn(delta_after) != Fsgn(delta_before))
    {
        completed = true;
        ExecuteAfterCompletion();
    }

    position.z = position_z;

    unit->SetNodePosition(position);
    unit->Invalidate();
}


void DriverTaskDive::ExecuteAfterCompletion()
{
    position_z = destination_z;
}


DriverTaskMove::DriverTaskMove(Driver *driver, const Point3D &pointTo) : DriverTask(driver), destination(pointTo)
{
    Point3D unitPosition = unit->GetNodePosition();

    Vector3D direction = (destination - unitPosition).Normalize();

    speed = direction * controller->param.max.speed.y;
}


void DriverTaskMove::RunStep(float dT)
{
    position = unit->GetNodePosition();

    float magnitude_before = Magnitude(destination - position);

    position += speed * dT;

    float magnitude_after = Magnitude(destination - position);

    if (magnitude_after > magnitude_before)
    {
        completed = true;
        ExecuteAfterCompletion();
    }

    unit->SetNodePosition(position);
    unit->Invalidate();
}


void DriverTaskMove::ExecuteAfterCompletion()
{
    position = destination;
}


DriverTaskRotate::DriverTaskRotate(Driver *driver, const Vector3D &_axis, float _angle) :
    DriverTask(driver), axis(_axis), target_angle(_angle)
{
}


void DriverTaskRotate::RunStep(float dT)
{
    float angle = dT * controller->param.max.rotate.z * Fsgn(target_angle);
    rotated += angle;

    Vector3D &direction = unit->GetUnitController()->param.direction;
    Vector3D &up = unit->GetUnitController()->param.up;

    direction.RotateAboutZ(angle);

    unit->SetDirection(direction, up);

    if (Fabs(rotated) >= Fabs(target_angle))
    {
        completed = true;
    }
}


void DriverTaskRotate::ExecuteAfterCompletion()
{
}
