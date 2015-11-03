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
        hitDrawable = gCursor->GetRaycastNode(hitPos);
    }

    if(hitDrawable)
    {
        static HiresTimer timerFull;
        timerFull.Reset();
        static long long timeFull = 0;

        Node *node = hitDrawable->GetNode();
        if(node->GetName() == NODE_TERRAIN)
        {



            static HiresTimer timerDisable;
            timerDisable.Reset();
            long long timeDisable = 0;

            lTilePath::DisableAll();

            timeDisable += timerDisable.GetUSec(false);
            LOGINFOF("time disable %d", timeDisable / 1000);


            static HiresTimer timerFindPath;
            timerFindPath.Reset();
            long long timeFindPath = 0;

            Coord start(gTerrain->NumRows() / 2, gTerrain->NumCols() / 2);
            PODVector<Coord> path = pathFinder.FindPath(start, Coord((uint)-hitPos->z_, (uint)hitPos->x_));

            if(path.Size() == 0)
            {
                return;
            }

            timeFindPath += timerFindPath.GetUSec(false);
            LOGINFOF("time find path %d", timeFindPath / 1000);



            static HiresTimer timer;
            timer.Reset();
            static long long timeAdd = 0;

            for (uint i = 0; i < path.Size(); i++)
            {
                hitPos->x_ = (float)path[i].col;
                hitPos->z_ = -(float)(path[i].row);
                hitPos->y_ = (float)(int)hitPos->y_;
                lTilePath::Add(*hitPos);

            }
            timeAdd += timer.GetUSec(false);
            LOGINFOF("time add %d", timeAdd / 1000);




        }

        timeFull += timerFull.GetUSec(false);
        LOGINFOF("time full %d", timeFull / 1000);
    }
}
