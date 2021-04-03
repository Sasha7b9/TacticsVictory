// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Game/Path/PathIndicator.h"
#include "Game/Path/TilePath.h"


PathIndicator::PathIndicator() : pathFinder(TheContext)
{
    pathFinder.SetSize(TheTerrain->HeightX(), TheTerrain->WidthZ());
}

PathIndicator::~PathIndicator()
{
    pathFinder.Stop();
}


void PathIndicator::Enable()
{
    enabled = true;

    pathFinder.StartFind(start, start);
}


void PathIndicator::Disable()
{
    enabled = false;

    TilePath::DisableAll();
}


void PathIndicator::SetStartPosition(const Coord &start_)
{
    start = start_;
    pathFinder.StartFind(start, start);
    TilePath::DisableAll();
}


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
                pos.x_ = static_cast<float>(path[i].rowX);
                pos.z_ = -static_cast<float>(path[i].colZ);
                pos.y_ = (float)(int)TheTerrain->GetHeight(path[i].rowX, path[i].colZ);
                TilePath::Add(pos);
            }
        }
        Vector3 hitPos;
        Drawable *drawable = TheCursor->GetRaycastNode(&hitPos);
        pathFinder.StartFind(start, drawable ? Coord(static_cast<uint>(fabsf(-hitPos.z_)), static_cast<uint>(hitPos.x_)) : start);
    }
}


PODVector<Coord> &PathIndicator::GetPath()
{
    return path;
}
