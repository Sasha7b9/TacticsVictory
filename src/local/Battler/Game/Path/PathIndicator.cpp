// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "PathIndicator.h"
#include "GUI/Cursor.h"
#include "Game/Path/TilePath.h"



PathIndicator::PathIndicator()
{
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PathIndicator::Init()
{
    pathFinder.SetSize(gTerrain->NumRows(), gTerrain->NumCols());
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PathIndicator::Enable(bool enable)
{
    enabled = enable;
    if (!enabled)
    {
        TilePath::DisableAll();
    }
    else
    {
        pathFinder.StartFind(start, start);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PathIndicator::SetStartPosition(const Coord &start_)
{
    start = start_;
    pathFinder.StartFind(start, start);
    TilePath::DisableAll();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PathIndicator::Update()
{
    if (!enabled)
    {
        return;
    }

    if (pathFinder.PathIsFound())
    {
        path = pathFinder.GetPath();
        if (path.Size())
        {
            TilePath::DisableAll();
            Vector3 pos;
            for (uint i = 0; i < path.Size(); i++)
            {
                pos.x_ = static_cast<float>(path[i].col);
                pos.z_ = -static_cast<float>(path[i].row);
                pos.y_ = (float)(int)gTerrain->GetHeight(path[i].row, path[i].col);
                TilePath::Add(pos);
            }
        }
        Vector3 hitPos;
        Drawable *drawable = gCursor->GetRaycastNode(&hitPos);
        pathFinder.StartFind(start, drawable ? Coord(static_cast<uint>(fabsf(-hitPos.z_)), static_cast<uint>(hitPos.x_)) : start);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PathIndicator::Stop()
{
    pathFinder.Stop();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
PODVector<Coord> &PathIndicator::GetPath()
{
    return path;
}
