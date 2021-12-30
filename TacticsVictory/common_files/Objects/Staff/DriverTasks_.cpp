// 2021/12/28 12:17:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Units/Air/Airplane_.h"


using namespace Pi;



DriverTask::DriverTask(Driver *driver) : unit((UnitObject *)driver->object)
{
}


DriverTaskDive::DriverTaskDive(Driver *driver, float z) : DriverTask(driver), destination_z(z)
{
    position_z = unit->GetNodePosition().z;

    GameObjectParameters &param = *unit->params;
    speed = Fsgn(destination_z - position_z) > 0 ? param.max.speed.z : -param.max.speed.z;
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
}


void DriverTaskDive::ExecuteAfterCompletion()
{
    position_z = destination_z;
}


DriverTaskMove::DriverTaskMove(Driver *driver, const Point3D &pointTo) : DriverTask(driver), destination(pointTo)
{
    Point3D unitPosition = unit->GetNodePosition();

    Vector3D direction = (destination - unitPosition).Normalize();

    speed = direction * unit->params->max.speed.y;
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
}


DriverAirplaneTaskFreeFlight::DriverAirplaneTaskFreeFlight(Driver *driver) : DriverTask(driver)
{
    GameObjectParameters &param = *unit->params;

    //param.direction.RotateAboutZ(K::pi / 2.0f / 1000.0f * (float)rand());

    param.speed = 2.0f;
    param.speedRotate.x = Math::RandomFloat(0.25f, 0.75f);
    param.speedRotate.y = Math::RandomFloat(2.25f, 2.75f);
    param.speedRotate.z = 0.0f;
}


void DriverAirplaneTaskFreeFlight::RunStep(float dT)
{
    Driver *driver = unit->driver;

    driver->MoveForward(dT);

    driver->RotateYawCompensate(dT);

    driver->RotateRoll(dT);

    driver->RotatePitchCompensate(dT);
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
    float angle = dT * unit->params->max.rotate.z * Fsgn(target_angle);
    rotated += angle;

    GameObjectParameters &param = *unit->params;

    Vector3D &direction = param.direction;
    Vector3D &up = param.up;

    direction.RotateAboutZ(angle);

    unit->SetDirection(direction, up);

    if (Fabs(rotated) >= Fabs(target_angle))
    {
        completed = true;
    }
}
