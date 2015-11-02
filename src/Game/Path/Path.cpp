#include <stdafx.h>


#include "Path.h"
#include "Game/Objects/Terrain.h"
#include "Core/Math.h"


lPath::lPath()
{

}

void lPath::SetTerrain(lTerrain *terrain)
{
    this->terrain = terrain;

    paths.Resize(terrain->NumRows());

    for(uint row = 0; row < terrain->NumRows(); row++)
    {
        paths[row].Resize(terrain->NumCols());
    }
}

PODVector<Coord> lPath::GetPath(Coord start, Coord end)
{
    for(uint row = 0; row < terrain->NumRows(); row++)
    {
        for(uint col = 0; col < terrain->NumCols(); col++)
        {
            paths[row][col].path.Resize(0);
            paths[row][col].pathLeft.Resize(0);
            paths[row][col].pathTop.Resize(0);
            paths[row][col].pathRight.Resize(0);
            paths[row][col].pathBottom.Resize(0);
            paths[row][col].isCalculated = false;
        }
    }

    CalculatePath(start, end);

    return paths[(uint)start.row][(uint)start.col].path;
}

void lPath::CalculatePath(Coord start, Coord end)
{
    uint row0 = (uint)start.row;
    uint col0 = (uint)start.col;

    uint row1 = (uint)end.row;
    uint col1 = (uint)end.col;

    StructPath strct = paths[row0][col0];

    if(strct.isCalculated)
    {
        return;
    }

    uint rowMax = terrain->NumRows() - 1;
    uint colMax = terrain->NumCols() - 1;

    float height0 = terrain->GetHeight(row0, col0);
    float height1 = terrain->GetHeight(row1, col1);

    if(height0 != height1)
    {
        paths[row0][col0].isCalculated = true;
        paths[row1][col1].isCalculated = true;
        return;
    }

    if(start == end)
    {
        PODVector<Coord> path;
        path.Push(start);
        WritePath(path);
        return;
    }

    // Stand near
    if((row0 == row1 && ABS((int)col0 - (int)col1) == 1) ||
       (col0 == col1 && ABS((int)row0 - (int)row1) == 1))
    {
        PODVector<Coord> path;
        path.Push(start);
        path.Push(end);
        WritePath(path);
        return;
    }

    // Left
    if (col0 > 1)
    {
        CalculatePath(Coord(row0, col0 - 1), end);
        paths[row0][col0].pathLeft = paths[row0][col0 - 1].path;
        if (paths[row0][col0].pathLeft.Size())
        {
            paths[row0][col0].pathLeft.Insert(0, start);
        }
    }

    // Top
    if (row0 > 1)
    {
        CalculatePath(Coord(row0 - 1, col0), end);
        paths[row0][col0].pathTop = paths[row0 - 1][col0].path;
        if (paths[row0][col0].pathTop.Size())
        {
            paths[row0][col0].pathTop.Insert(0, start);
        }
    }

    // Right
    if (row0 < rowMax)
    {
        CalculatePath(Coord(row0 + 1, col0), end);
        paths[row0][col0].pathRight = paths[row0 + 1][col0].path;
        if (paths[row0][col0].pathRight.Size())
        {
            paths[row0][col0].pathRight.Insert(0, start);
        }
    }

    // Bottom
    if (col0 < colMax)
    {
        CalculatePath(Coord(row0, col0 + 1), end);
        paths[row0][col0].pathBottom = paths[row0][col0 + 1].path;
        if (paths[row0][col0].pathBottom.Size())
        {
            paths[row0][col0].pathBottom.Insert(0, start);
        }
    }

    uint maxSize = Math::Max(paths[row0][col0].pathLeft.Size(), paths[row0][col0].pathTop.Size(), paths[row0][col0].pathRight.Size(), paths[row0][col0].pathBottom.Size());
    if (maxSize == 0)
    {
        paths[row0][col0].isCalculated = true;
    }
    else
    {
        PODVector<Coord> *addPath = nullptr;
        if (paths[row0][col0].pathBottom.Size() > 0 && paths[row0][col0].pathBottom.Size() <= maxSize)
        {
            addPath = &paths[row0][col0].pathBottom;
            maxSize = paths[row0][col0].pathBottom.Size();
        }
        if (paths[row0][col0].pathRight.Size() > 0 && paths[row0][col0].pathRight.Size() <= maxSize)
        {
            addPath = &paths[row0][col0].pathRight;
            maxSize = paths[row0][col0].pathRight.Size();
        }
        if (paths[row0][col0].pathTop.Size() > 0 && paths[row0][col0].pathTop.Size() <= maxSize)
        {
            addPath = &paths[row0][col0].pathTop;
            maxSize = paths[row0][col0].pathTop.Size();
        }
        if (paths[row0][col0].pathLeft.Size() > 0 && paths[row0][col0].pathLeft.Size() <= maxSize)
        {
            addPath = &paths[row0][col0].pathLeft;
            maxSize = paths[row0][col0].pathLeft.Size();
        }
        WritePath(*addPath);
    }
}

void lPath::WritePath(PODVector<Coord> path)
{
    paths[(uint)path[0].row][(uint)path[0].col].isCalculated = true;
    paths[(uint)path[0].row][(uint)path[0].col].path = path;

    if (path.Size() > 1)
    {
        path = ReversePath(path);

        paths[(uint)path[0].row][(uint)path[0].col].isCalculated = true;
        paths[(uint)path[0].row][(uint)path[0].col].path = path;
    }
}

PODVector<Coord> lPath::ReversePath(PODVector<Coord> path)
{
    PODVector<Coord> ret;

    for (uint i = 0; i < path.Size(); i++)
    {
        ret.Insert(0, path[i]);
    }

    return ret;
}
