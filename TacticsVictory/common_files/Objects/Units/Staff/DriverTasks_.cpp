// 2021/12/28 12:17:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Staff/DriverTasks_.h"
#include "Objects/Units/Staff/Driver_.h"
#include "Objects/Units/Air/Airplane_.h"


using namespace Pi;



DriverTask::DriverTask(Driver *driver) : controller(driver->controller), unit(controller->object)
{
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


DriverAirplaneTaskFreeFlight::DriverAirplaneTaskFreeFlight(Driver *driver) : DriverTask(driver)
{
    UnitParameters &param = controller->param;

    param.direction.RotateAboutZ(K::pi / 2.0f / 1000.0f * (float)rand());

    param.speed = 2.0f;
    param.speedRotate.x = Math::RandomFloat(0.025f, 0.075f);
    param.speedRotate.y = Math::RandomFloat(0.025f, 0.075f);
    param.speedRotate.z = Math::RandomFloat(0.025f, 0.075f);
}


void DriverAirplaneTaskFreeFlight::RunStep(float dT)
{
    Driver *driver = controller->GetDriver();

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
