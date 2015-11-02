#include <stdafx.h>


#include "WaveAlgorithm.h"
#include "Game/Objects/Terrain.h"


PODVector<Coord> WaveAlgorithm::GetPath(Coord start, Coord end)
{
    cells.Resize(gTerrain->NumRows());

    for(uint row = 0; row < gTerrain->NumRows(); row++)
    {
        cells[row].Resize(gTerrain->NumCols());
        for(uint col = 0; col < gTerrain->NumCols(); col++)
        {
            cells[row][col].numWave = -1;
        }
    }

    this->end = end;
    height = gTerrain->GetHeight(start.row, start.col);

    cells[(uint)start.row][(uint)start.col].numWave = 0;

    CalculateWaves(start, 1);

    PODVector<Coord> path;

    if(cells[(uint)start.row][(uint)start.col].numWave == -2)
    {
        return path;
    }

    Coord coord = end;

    do
    {
        path.Insert(0, coord);
        coord = cells[(uint)coord.row][(uint)coord.col].parent;
    } while(!(coord == start));

    path.Insert(0, coord);

    return path;
}

void WaveAlgorithm::CalculateWaves(Coord coord, int numWave)
{
    uint col = (uint)coord.col;
    uint row = (uint)coord.row;

    // Left
    if(col > 0)
    {
        col--;
        if(cells[row][col].numWave == -1)
        {
            if(gTerrain->GetHeight(row, col) != height)
            {
                cells[row][col].numWave = -2;
            }
            else
            {
                cells[row][col].numWave = numWave;
                cells[row][col].parent = Coord((int)row, (int)(col + 1));
                CalculateWaves(Coord((int)row, (int)col), numWave + 1);
            }
        }
    }

    // Top
    if(row > 0)
    {
        row--;
        if(cells[row][col].numWave == -1)
        {
            if(gTerrain->GetHeight(row, col) != height)
            {
                cells[row][col].numWave = -2;
            }
            else
            {
                cells[row][col].numWave = numWave;
                cells[row][col].parent = Coord(row + 1, col);
                CalculateWaves(Coord(row, col), numWave + 1);
            }
        }
    }

    // Right
    if(col < gTerrain->NumCols() - 1)
    {
        col++;
        if(cells[row][col].numWave == -1)
        {
            if(gTerrain->GetHeight(row, col) != height)
            {
                cells[row][col].numWave = -2;
            }
            else
            {
                cells[row][col].numWave = numWave;
                cells[row][col].parent = Coord(row, col - 1);
                CalculateWaves(Coord(row, col), numWave + 1);
            }
        }
    }

    // Bottom
    if(row < gTerrain->NumRows() - 1)
    {
        row++;
        if(cells[row][col].numWave == -1)
        {
            if(gTerrain->GetHeight(row, col) != height)
            {
                cells[row][col].numWave = -2;
            }
            else
            {
                cells[row][col].numWave = numWave;
                cells[row][col].parent = Coord(row - 1, col);
                CalculateWaves(Coord(row, col), numWave + 1);
            }
        }
    }
}
