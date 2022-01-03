// 2021/12/28 12:17:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Units/Air/Airplane_.h"


using namespace Pi;



DriverTask::DriverTask(Driver *_driver) :
    object(_driver->object),
    driver(*_driver),
    params(object.params)
{
}


void DriverTask::RunStep(float dT)
{
    if (first)
    {
        first = false;
        Preprocess();
    }
}


DriverTaskDive::DriverTaskDive(Driver *driver, float z) : DriverTask(driver), destination_z(z)
{
    position_z = object.GetNodePosition().z;

    GameObjectParameters &param = object.params;
    speed = Fsgn(destination_z - position_z) > 0 ? param.max.velocity.z : -param.max.velocity.z;
}


void DriverTaskDive::RunStep(float dT)
{
    Point3D position = object.GetNodePosition();

    position_z = position.z;

    float delta_before = destination_z - position_z;

    position_z += speed * dT;

    float delta_after = destination_z - position_z;

    if (Fsgn(delta_after) != Fsgn(delta_before))
    {
        completed = true;
        position_z = destination_z;
    }

    position.z = position_z;
}


DriverAirplaneTaskFreeFlight::DriverAirplaneTaskFreeFlight(Driver *driver) : DriverTask(driver)
{
    GameObjectParameters &param = object.params;

    //param.direction.RotateAboutZ(K::pi / 2.0f / 1000.0f * (float)rand());

    param.cur.velocity = 2.0f;
    param.cur.speed_rotate.x = Math::RandomFloat(0.25f, 0.75f);
    param.cur.speed_rotate.y = Math::RandomFloat(2.25f, 2.75f);
    param.cur.speed_rotate.z = 0.0f;
}


void DriverAirplaneTaskFreeFlight::RunStep(float dT)
{
    driver.MoveForward(dT);

    driver.RotateYawCompensate(dT);

    driver.RotateRoll(dT);

    driver.RotatePitchCompensate(dT);
}


DriverTaskRotate::DriverTaskRotate(Driver *driver, const Vector3D &_axis, float _angle) :
    DriverTask(driver), axis(_axis), target_angle(_angle)
{
    target_direction = params.cur.direction;
    target_direction.RotateAboutAxis(target_angle, axis);

    target_up = params.cur.up;
    target_up.RotateAboutAxis(target_angle, axis);
}


void DriverTaskRotate::RunStep(float dT)
{
    float delta_angle = dT * object.params.max.speed_rotate.z * Fsgn(target_angle);
    rotated += delta_angle;

    Vector3D &direction = params.cur.direction;
    Vector3D &up = params.cur.up;

    direction.RotateAboutAxis(delta_angle, axis);
    up.RotateAboutAxis(delta_angle, axis);

    params.apply_rotate = true;

    if (Fabs(rotated) >= Fabs(target_angle))
    {
        params.cur.direction = target_direction;
        params.cur.up = target_up;

        completed = true;
    }
}


DriverTaskAlignDirection::DriverTaskAlignDirection(Driver *driver) : DriverTask(driver)
{
}


void DriverTaskAlignDirection::RunStep(float dT)
{
    completed = true;
}


DriverTaskMove::DriverTaskMove(Driver *_driver, Direction::B _direction) :
    DriverTask(_driver),
    direction(_direction)
{
}


void DriverTaskMove::Preprocess()
{
    params.cur.velocity = params.max.velocity.y;
}


void DriverTaskMove::RunStep(float dT)
{
    DriverTask::RunStep(dT);

    driver.MoveForward(dT);
}



DriverTaskTurnClockwise::DriverTaskTurnClockwise(Driver *driver) :
    DriverTask(driver)
{

}


void DriverTaskTurnClockwise::RunStep(float dT)
{

}
