// 2021/12/15 22:10:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Submarine.h"
#include "Scene/World/Water.h"
#include "Scene/World/Landscape.h"
#include "Utils/Math.h"
#include "Objects/Units/UnitLogic/StepAction.h"


using namespace Pi;


Submarine *Submarine::Create()
{
    Submarine *node = new Submarine();

    node->SetController(new SubmarineController());

    return node;
}


Submarine::Submarine() : WaterUnitObject(TypeWaterUnit::Submarine)
{
    const float size = 1.0f;

    PrimitiveGeometry *geometry = new SphereGeometry({size / 10.0f, size / 2.0f, size / 10.0f});
    geometry->GetObject()->Build(geometry);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.1f, 0.3f, 0.0f});
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    AppendNewSubnode(geometry);
    geometry->GetObject()->SetCollisionExclusionMask(PiKindCollision::Unit);
}


void CommanderSubmarine::ParseDive(const UnitTask *task) const
{
    if (task->destination.z == unit->GetNodePosition().z)
    {
        return;
    }

    driver->AppendTask(new DiveUnitTaskAbs(task->destination.z));
}


void CommanderSubmarine::ParseRotate(const UnitTask *) const
{

}


void DriverSubmarine::Update(float dT)
{
    Driver::Update(dT);

    if (tasks.GetElementCount() == 0)
    {
        return;
    }

    const UnitTask *task = tasks[0];

    if (task->type == UnitTask::Type::Dive)
    {
        if(ActionDive().Run(unit, task, controller, dT))
        {
            delete task;
            tasks.RemoveElement(0);
        }
    }
}
