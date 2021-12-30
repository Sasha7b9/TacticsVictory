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


using namespace Pi;


Driver::Driver(GameObject *_object) : object(_object), params(object->params)
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
    if (params->applyRotate)
    {
        params->applyRotate = false;

#ifdef PiCLIENT

        object->SetDirection(params->direction, params->up);

        object->Invalidate();
#endif
    }

    if (params->applyTranslation)
    {
        params->applyTranslation = false;

#ifdef PiCLIENT

        params->stat.distance += Magnitude(object->GetNodePosition() - params->position);

        Node *node = object;

        node->SetNodePosition(params->position);

        node->Invalidate();
#endif
    }
}


void Driver::MoveForward(float dT)
{
    if(params->speed != 0.0f)
    {
        params->position += params->direction * params->speed * dT;

        params->applyTranslation = true;
    }
}


void Driver::RotateYaw(float dT)
{
    if(params->speedRotate.z != 0.0f)
    {
        params->direction.RotateAboutAxis(params->speedRotate.z * dT, params->up);

        params->applyRotate = true;
    }
}


void Driver::RotateYawCompensate(float dT)
{
    if(params->speedRotate.z != 0.0f)
    {
        params->direction.RotateAboutAxis(params->speedRotate.z * dT, params->upPitch);

        params->applyRotate = true;
    }
}


void Driver::RotateRoll(float dT)
{
    if(params->speedRotate.y != 0.0f)
    {
        params->up.RotateAboutAxis(-params->speedRotate.y * dT, params->direction);

        params->applyRotate = true;
    }
}


void Driver::RotatePitch(float dT)
{
    if(params->speedRotate.x != 0.0f)
    {
        float angle = params->speedRotate.x * dT;

        Vector3D axis = Cross(params->direction, params->up).Normalize();

        params->direction.RotateAboutAxis(angle, axis);
        params->up.RotateAboutAxis(angle, axis);
        params->upPitch.RotateAboutAxis(angle, axis);

        params->applyRotate = true;
    }
}


void Driver::RotatePitchCompensate(float dT)
{
    if(params->speedRotate.x != 0.0f)
    {
        float angle = params->speedRotate.x * dT;

        Vector3D axis = Cross(params->direction, params->upPitch).Normalize();

        params->direction.RotateAboutAxis(angle, axis);
        params->up.RotateAboutAxis(angle, axis);
        params->upPitch.RotateAboutAxis(angle, axis);

        params->applyRotate = true;
    }
}


void Driver::AppendTask(DriverTask *task)
{
    tasks.AddElement(task);
}

