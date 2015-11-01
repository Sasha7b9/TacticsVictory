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
            paths[row][col].isCalculated = false;
        }
    }

    CalculatePath(start, end);

    return paths[(uint)start.row][(uint)start.col].path;
}

void lPath::CalculatePath(Coord start, Coord end)
{
    int row0 = start.row;
    int col0 = start.col;

    int row1 = end.row;
    int col1 = end.col;

    StructPath strct = paths[(uint)row0][(uint)col0];

    if(strct.isCalculated)
    {
        return;
    }

    PODVector<IntVector2> path;

    int rowMax = (int)terrain->NumRows() - 1;
    int rowCol = (int)terrain->NumCols() - 1;

    float height0 = terrain->GetHeight(row0, col0);
    float height1 = terrain->GetHeight(row1, col1);

    if(height0 != height1)
    {
        paths[(uint)row0][(uint)col0].isCalculated = true;
        paths[(uint)row1][(uint)col1].isCalculated = true;
        return;
    }

    if(start == end)
    {
        PODVector<Coord> path;
        path.Push(Coord(row0, col0));
        paths[(uint)row0][(uint)col0].path = path;
        paths[(uint)row0][(uint)col0].isCalculated = true;
        return;
    }

    // Stand near
    if((row0 == row1 && ABS(col0 - col1) == 1) ||
       (col0 == col1 && ABS(row0 - row1) == 1))
    {
        PODVector<Coord> path;
        path.Push(Coord(row0, col0));
        path.Push(Coord(row1, col1));
        paths[(uint)row0][(uint)col0].path = path;
        paths[(uint)row0][(uint)col0].isCalculated = true;

        path.Clear();
        path.Push(Coord(row1, col1));
        path.Push(Coord(row0, col0));
        paths[(uint)row1][(uint)col1].path = path;
        paths[(uint)row1][(uint)col1].isCalculated = true;

        return;
    }

    
}
