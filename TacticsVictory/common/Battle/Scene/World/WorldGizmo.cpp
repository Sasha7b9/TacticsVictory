// 2021/12/3 13:54:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/WorldGismo.h"


using namespace Pi;


static const float radius = 0.2f;


WorldGizmo::WorldGizmo() : Node("WorldGismo")
{
    AppendNewSubnode(CreateAxis(K::red, Transform4D().SetRotationAboutY(K::pi / 2),    {0.0f,        -radius / 2, radius / 2}));

    AppendNewSubnode(CreateAxis(K::green, Transform4D().SetRotationAboutX(-K::pi / 2), {-radius / 2, 0.0f,        radius / 2}));

    AppendNewSubnode(CreateAxis(K::blue, Transform4D().SetRotationAboutZ(K::pi / 2),   {radius / 2,  -radius / 2, 0.0f}));
}


Node *WorldGizmo::CreateAxis(const ColorRGBA &color, const Transform4D &transform, const Point3D &position)
{
    PrimitiveGeometry *geometry = new PyramidGeometry({radius, radius}, 1500);
    PrimitiveGeometryObject *object = geometry->GetObject();
    object->DissableGeometryFlags(PiFlagGeometry::CastShadows);
    object->SetBuildLevelCount(1);
    geometry->Update();
    object->Build(geometry);
    geometry->Update();

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(color);
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    geometry->SetNodeTransform(transform);

    geometry->SetNodePosition(position);

    return geometry;
}
