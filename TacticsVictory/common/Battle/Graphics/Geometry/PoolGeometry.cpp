// 2021/12/15 12:03:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Geometry/PoolGeometry.h"
#include "Graphics/Meshes/WorldGizmo.h"


using namespace Pi;


namespace Pi
{
    namespace PoolGeometry
    {
        static Array<Node *> geometries;
    
        Node *CreateSelectorLandscape();
        Node *CreateGizmoObject();
    }
}


void PoolGeometry::Construct()
{
    geometries.SetElementCount((int)TTypeGeometry::Count);

    geometries[(int)TTypeGeometry::SelectorLandscape] = CreateSelectorLandscape();
    geometries[(int)TTypeGeometry::GizmoObject] = CreateGizmoObject();
}


void PoolGeometry::Destruct()
{
    for (int i = 0; i < geometries.GetElementCount(); i++)
    {
        delete geometries[i];
    }
}


Node *PoolGeometry::Get(TTypeGeometry type)
{
    if (type == TTypeGeometry::GizmoObject)
    {
        return new WorldGizmo(1.5f, 0.02f);
    }

    return nullptr;
}


Node *PoolGeometry::CreateSelectorLandscape()
{
    return nullptr;
}


Node *PoolGeometry::CreateGizmoObject()
{
    return new WorldGizmo(1.5f, 0.01f);
}
