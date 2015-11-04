#include <stdafx.h>


#include "PathIndicator.h"
#include "GUI/Elements/Cursor.h"
#include "Game/Objects/Terrain.h"
#include "Game/Path/TilePath.h"


PathIndicator::PathIndicator()
{
    
}

void PathIndicator::Init()
{
    pathFinder.SetSize(gTerrain->NumRows(), gTerrain->NumCols());
}

void PathIndicator::SetInCurrentCursorPosition(UDrawable *hitDrawable, Vector3 *hitPos)
{
    static int numFrame = 0;
    static Timer timer;
    uint timeEnter = timer.GetMSec(false);
    //LOGINFOF("Time enter %d, frame %d", timer.GetMSec(false), numFrame++);

    Vector3 pos;

    if(!hitDrawable)
    {
        hitPos = &pos;
        hitDrawable = gCursor->GetRaycastNode(hitPos);
    }
    uint time0 = timer.GetMSec(false);
    //LOGINFOF("point 0 - %d", time0 - timeEnter);

    if(hitDrawable)
    {
        Node *node = hitDrawable->GetNode();

    uint time1 = timer.GetMSec(false);
    //LOGINFOF("point 1 - %d", time1 - time0);

        if(node->GetName() == NODE_TERRAIN)
        {
            TilePath::DisableAll();

            Coord start(gTerrain->NumRows() / 2, gTerrain->NumCols() / 2);
            PODVector<Coord> path = pathFinder.FindPath(start, Coord((uint)-hitPos->z_, (uint)hitPos->x_));

    uint time2 = timer.GetMSec(false);
    //LOGINFOF("point 2 - %d", time2 - time1);

            if (path.Size() != 0)
            {
                for (uint i = 0; i < path.Size(); i++)
                {
                    hitPos->x_ = (float)path[i].col;
                    hitPos->z_ = -(float)(path[i].row);
                    hitPos->y_ = (float)(int)hitPos->y_;
                    TilePath::Add(*hitPos);

                }
    //LOGINFOF("point 3 - %d", timer.GetMSec(false) - time2);
            }
        }
    }

    //LOGINFOF("time release %d, time full %d", timer.GetMSec(false), timer.GetMSec(false) - timeEnter);
}
