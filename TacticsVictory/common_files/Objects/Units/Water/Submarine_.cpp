// 2021/12/15 22:10:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Scene/World/Landscape_.h"
#include "Utils/Math_.h"


using namespace Pi;


Submarine *Submarine::Create(int id)
{
    return new Submarine(id);
}


Submarine::Submarine(int id) : WaterUnitObject(TypeWaterUnit::Submarine, id, new SubmarineController(this))
{
    const float size = 1.0f;

    PrimitiveGeometry *geometry = new SphereGeometry({size / 10.0f, size / 2.0f, size / 10.0f});
    geometry->GetObject()->Build(geometry);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.1f, 0.3f, 0.0f});
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    Node *node = new Node();
    node->SetNodeName("Body");

    node->AppendNewSubnode(geometry);

    geometry->GetObject()->SetCollisionExclusionMask(PiKindCollision::Unit);

    GetNodeGeometry()->AppendNewSubnode(node);
}


void CommanderSubmarine::ParseDive(const CommanderTask *task) const
{
    if (task->destination.z != unit->GetNodePosition().z)
    {
        driver->AppendTask(new DriverTaskDive(driver, task->destination.z));
    }
}


void CommanderSubmarine::ParseRotate(const CommanderTask *task) const
{
    driver->AppendTask(new DriverTaskRotate(driver, Vector3D::UP, task->destination.z));
}


SubmarineController::SubmarineController(Submarine *submarine) : WaterUnitController(submarine, parameters)
{
}
