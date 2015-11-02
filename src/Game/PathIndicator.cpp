#include <stdafx.h>


#include "PathIndicator.h"
#include "GUI/Elements/Cursor.h"
#include "Game/Objects/Terrain.h"
#include "Game/Path/TilePath.h"


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
            lTilePath::DisableAll();

            Coord start(gTerrain->NumRows() / 2, gTerrain->NumCols() / 2);
            PODVector<Coord> path = pathFinder.FindPath(start, Coord((uint)-hitPos->z_, (uint)hitPos->x_));

            if(path.Size() == 0)
            {
                return;
            }

            Timer timer;
            for (uint i = 0; i < path.Size(); i++)
            {
                hitPos->x_ = (float)path[i].col;
                hitPos->z_ = -(float)(path[i].row);
                hitPos->y_ = (float)(int)hitPos->y_;
                lTilePath::Add(*hitPos);
            }
        }
    }
}
