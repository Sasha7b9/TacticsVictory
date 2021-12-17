// 2021/12/17 23:05:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Math.h"


namespace Pi
{
    struct ActionDive
    {
        bool Run(UnitObject *unit, const UnitTask *task, UnitController *controller, float dT)
        {
            bool result = false;

            Point3D position = unit->GetNodePosition();

            float delta_before = task->destination.z - position.z;

            float speed = Mathem::Sign(delta_before) > 0 ? controller->param->max.speed.z : -controller->param->max.speed.z;

            position.z += speed * dT;

            float delta_after = task->destination.z - position.z;

            if (Mathem::Sign(delta_after) != Mathem::Sign(delta_before))
            {
                result = true;
                position.z = task->destination.z;
            }

            unit->SetNodePosition(position);
            unit->Invalidate();

            return result;
        }
    };
}
