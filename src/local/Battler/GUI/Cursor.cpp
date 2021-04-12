// 2021/04/12 23:34:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor_.h"
#include "Scene/Cameras/Camera.h"


Drawable *CursorT::GetRaycastNode(Vector3 *hitPos_)
{
    if (TheUI->GetElementAt(TheUI->GetCursorPosition(), true))
    {
        return nullptr;
    }

    if (!TheCamera)
    {
        return nullptr;
    }

    Ray ray = TheCamera->GetCursorRay();
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, RAY_TRIANGLE, M_INFINITY, DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
    TheScene->GetComponent<Octree>()->Raycast(query);

    if (results.Size())
    {
        RayQueryResult &result = results[0];
        String name = result.drawable_->GetNode()->GetName();
        if (result.drawable_->GetNode()->GetName() == NAME_NODE_TILE_PATH && results.Size() > 1)
        {
            result = results[1];
        }

        if (hitPos_)
        {
            *hitPos_ = result.position_;
        }
        return result.drawable_;
    }

    return nullptr;
}
