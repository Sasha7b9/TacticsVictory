// 2021/12/3 13:54:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Meshes/WorldGizmo.h"


using namespace Pi;


WorldGizmo::WorldGizmo(float _size, float _radius) : Node("WorldGismo"), size(_size), radius(_radius)
{
    AppendNewSubnode(CreateAxis(K::red, Transform4D().SetRotationAboutY(K::pi / 2),    {0.0f,        -radius / 2, radius / 2}));

    AppendNewSubnode(CreateAxis(K::green, Transform4D().SetRotationAboutX(-K::pi / 2), {-radius / 2, 0.0f,        radius / 2}));

    AppendNewSubnode(CreateAxis(K::blue, Transform4D().SetRotationAboutZ(K::pi / 2),   {radius / 2,  -radius / 2, 0.0f}));
}


Node *WorldGizmo::CreateAxis(const ColorRGBA &color, const Transform4D &transform, const Point3D &position)
{
    PrimitiveGeometry *geometry = new PyramidGeometry({radius, radius}, size);
    PrimitiveGeometryObject *object = geometry->GetObject();
    object->DisableGeometryFlags(PiFlagGeometry::CastShadows);
    object->Build(geometry);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(color);
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    geometry->SetNodeTransform(transform);

    geometry->SetNodePosition(position);

    return geometry;
}
