// 2021/12/17 0:03:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Staff/Driver_.h"
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
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/World/Landscape_.h"


using namespace Pi;


Driver::Driver(GameObject *_object) : object(*_object), params(object.params)
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


Driver *Driver::Create(GameObject *object)
{
    TypeGameObject typeGameObject = object->typeGameObject;

    if(typeGameObject == TypeGameObject::Unit)
    {
        UnitObject *unit = object->GetUnitObject();

        if (unit->typeUnit == TypeUnit::Air)
        {
            TypeAirUnit type = unit->GetAirUnit()->typeAirUnit;

            if (type == TypeAirUnit::Airplane)        return new Driver(object);
            else if (type == TypeAirUnit::Helicopter) return new Driver(object);
        }
        else if (unit->typeUnit == TypeUnit::Ground)
        {
            TypeGroundUnit type = unit->GetGroundUnit()->typeGroundUnit;

            if (type == TypeGroundUnit::Robot)     return new Driver(object);
            else if (type == TypeGroundUnit::Tank) return new Driver(object);
            else if (type == TypeGroundUnit::Worm) return new Driver(object);
        }
        else if (unit->typeUnit == TypeUnit::Water)
        {
            TypeWaterUnit type = unit->GetWaterUnit()->typeWaterUnit;

            if (type == TypeWaterUnit::Boat)           return new Driver(object);
            else if (type == TypeWaterUnit::Submarine) return new Driver(object);
        }
    }

    return new Driver(object);
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
    if (params.apply_rotate)
    {
        params.apply_rotate = false;

#ifdef PiCLIENT

        object.SetDirection(params.cur.direction, params.cur.up);

        object.Invalidate();
#endif
    }

    if (params.apply_translation)
    {
        params.apply_translation = false;

#ifdef PiCLIENT

        params.stat.distance += Magnitude(object.GetNodePosition() - params.cur.position);

        Node &node = object;

        node.SetNodePosition(params.cur.position);

        node.Invalidate();
#endif
    }
}


void Driver::MoveForward(float dT)
{
    if(params.cur.velocity != 0.0f)
    {
        params.cur.position += params.cur.direction * params.cur.velocity * dT;

        params.apply_translation = true;
    }
}


void Driver::RotateYaw(float dT)
{
    if(params.cur.speed_rotate.z != 0.0f)
    {
        params.cur.direction.RotateAboutAxis(params.cur.speed_rotate.z * dT, params.cur.up);

        params.apply_rotate = true;
    }
}


void Driver::RotateYawCompensate(float dT)
{
    if(params.cur.speed_rotate.z != 0.0f)
    {
        params.cur.direction.RotateAboutAxis(params.cur.speed_rotate.z * dT, params.cur.up_ortho);

        params.apply_rotate = true;
    }
}


void Driver::RotateRoll(float dT)
{
    if(params.cur.speed_rotate.y != 0.0f)
    {
        params.cur.up.RotateAboutAxis(-params.cur.speed_rotate.y * dT, params.cur.direction);

        params.apply_rotate = true;
    }
}


void Driver::RotatePitch(float dT)
{
    if(params.cur.speed_rotate.x != 0.0f)
    {
        float angle = params.cur.speed_rotate.x * dT;

        Vector3D axis = Cross(params.cur.direction, params.cur.up).Normalize();

        params.cur.direction.RotateAboutAxis(angle, axis);
        params.cur.up.RotateAboutAxis(angle, axis);
        params.cur.up_ortho.RotateAboutAxis(angle, axis);

        params.apply_rotate = true;
    }
}


void Driver::RotatePitchCompensate(float dT)
{
    if(params.cur.speed_rotate.x != 0.0f)
    {
        float angle = params.cur.speed_rotate.x * dT;

        Vector3D axis = Cross(params.cur.direction, params.cur.up_ortho).Normalize();

        params.cur.direction.RotateAboutAxis(angle, axis);
        params.cur.up.RotateAboutAxis(angle, axis);
        params.cur.up_ortho.RotateAboutAxis(angle, axis);

        params.apply_rotate = true;
    }
}


void Driver::AppendTask(DriverTask *task)
{
    tasks.AddElement(task);
}


void Driver::RemoveTasks()
{
    tasks.Purge();
}


bool Driver::CanMoveForward() const
{
    Point3D position = params.cur.position + params.cur.direction;      // В эту точку мы перемещаемся виртуально

    if (position.x < 0.0f || position.y < 0.0f ||                   // Вышли за пределы ландшафта
        position.x >= (float)Landscape::self->GetSizeX_Columns() ||
        position.y >= (float)Landscape::self->GetSizeY_Rows())
    {
        return false;
    }

    float height = Landscape::self->GetHeightCenter(params.cur.position.x + 0.5f, params.cur.position.y + 0.5f);

    if (height != Landscape::self->GetHeightCenter(position.x + 0.5f, position.y + 0.5f))
    {
        return false;
    }

    return true;
}
