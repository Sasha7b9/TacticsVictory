#include <stdafx.h>


#include "PathIndicator.h"
#include "GUI/Elements/Cursor.h"


lPathIndicator::lPathIndicator()
{

}

void lPathIndicator::SetInCurrentCursorPosition(Drawable *hitDrawable, Vector3 *hitPos)
{
    if(decal)
    {
        decal->RemoveAllDecals();
    }

    Vector3 pos;

    if(!hitDrawable)
    {
        hitPos = &pos;
        hitDrawable = gCursor->GetRaycastNode(1000.0f, hitPos);
    }

    if(hitDrawable)
    {
        Node *node = hitDrawable->GetNode();
        if(node->GetName() == NODE_TERRAIN)
        {
            decal = node->GetComponent<DecalSet>();
            if(!decal)
            {
                decal = node->CreateComponent<DecalSet>();
                decal->SetMaterial(gCache->GetResource<Material>("Materials/Decals/PathDecal.xml"));
            }
            hitPos->x_ = (int)hitPos->x_ + 0.5f;
            hitPos->z_ = (int)hitPos->z_ - 0.5f;
            decal->AddDecal(hitDrawable, *hitPos, Quaternion(90.0f, 90.0f, 0.0f), 0.8f, 1.0f, 1.0f, Vector2::ZERO, Vector2::ONE);
        }
    }
}
