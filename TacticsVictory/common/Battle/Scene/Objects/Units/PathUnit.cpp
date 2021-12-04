// 2021/12/3 20:53:10 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathUnit.h"
#include "Scene/World/GameWorld.h"
#include "Scene/World/Landscape.h"


using namespace Pi;


static PathUnit *ThePathUnit = nullptr;


PathUnit::PathUnit(float x, float y) : Node("PathUnit")
{
    AppendSubnode(CreateMember(x, y));
}


void PathUnit::Create()
{
    ThePathUnit = new PathUnit(0.0f, 0.0f);

    GameWorld::Get()->GetRootNode()->AppendNewSubnode(ThePathUnit);
}


void PathUnit::PowerOn()
{
    ThePathUnit->Enable();
}


void PathUnit::PowerOff()
{
    ThePathUnit->Disable();
}


void PathUnit::SetPosition(const Point3D &_position)
{
    Point3D position = _position;
    position.x = (float)(int)position.x + 0.5f;
    position.y = (float)(int)position.y + 0.5f;

    ThePathUnit->SetNodePosition(position);
    ThePathUnit->Invalidate();
}


Node *PathUnit::CreateMember(float x, float y)
{
    float size = 0.4f;

    PrimitiveGeometry *geometry = new SphereGeometry({size, size, 0.1f});
    PrimitiveGeometryObject *object = geometry->GetObject();
    object->SetCollisionExclusionMask(PiKindCollision::PathUnit);
    object->DissableGeometryFlags(PiFlagGeometry::CastShadows);
    object->SetBuildLevelCount(1);
    geometry->Update();
    object->Build(geometry);
    geometry->Update();

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(K::blue);
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    geometry->SetNodePosition({x, y, GameWorld::Get()->GetLandscape()->GetHeight(x, y)});

    return geometry;
}
