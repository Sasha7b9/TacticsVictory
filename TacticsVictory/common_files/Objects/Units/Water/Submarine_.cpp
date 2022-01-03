// 2021/12/15 22:10:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Water/Submarine_.h"
#include "Utils/Math_.h"
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/World/Landscape_.h"


using namespace Pi;


Map<Submarine> Submarine::objects;


Submarine *Submarine::Create(int id)
{
    return new Submarine(id);
}


Submarine::Submarine(int id) : WaterUnitObject(TypeWaterUnit::Submarine, &parameters, id)
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

    driver = Driver::Create(this);

    commander = new Commander(this);

    objects.Insert(this);
}
