#include <stdafx.h>


#include "PathWave.h"
#include "Game/Objects/Terrain.h"


void PathWave::SetSize(uint numRows, uint numCols)
{
    this->numRows = numRows;
    this->numCols = numCols;

    cells.Resize(numRows);
    for (auto &row : cells)
    {
        row.Resize(numCols);
    }
}


PODVector<Coord> PathWave::FindPath(Coord start, Coord end)
{
    static PODVector<Coord> path;
    path.Clear();

    if(gTerrain->GetHeight(start.row, start.col) != gTerrain->GetHeight(end.row, end.col))
    {
        return path;
    }

    for (auto &row : cells)
    {
        for (auto cell : row)
        {
            cell.numWave = -1;
        }
    }

    int numWave = 0;

    cells[start.row][start.col].numWave = numWave;

    while (cells[end.row][end.col].numWave == -1)
    {
        numWave++;
        DrawWave(numWave);
    }

    path.Push(end);

    while (!(path[0] == start))
    {
        AddPrevWave(path);
    }

    return path;
}

void PathWave::DrawWave(int numWave)
{
    for (uint row = 0; row < cells.Size(); row++)
    {
        for (uint col = 0; col < cells[row].Size(); col++)
        {
            if (cells[row][col].numWave == numWave - 1 && gTerrain->GetHeight(row, col) == heightStart)
            {
                FillNearCells(row, col, numWave);
            }
        }
    }
}

void PathWave::FillNearCells(uint row, uint col, int numWave)
{
    const int dRow[] = { 0, -1, 0, 1, -1, -1, 1,  1};
    const int dCol[] = {-1,  0, 1, 0, -1,  1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        int iRow = (int)row + dRow[i];
        int iCol = (int)col + dCol[i];

        uint newRow = (uint)iRow;
        uint newCol = (uint)iCol;

        if (newRow < gTerrain->NumRows() && newCol < gTerrain->NumCols() && cells[newRow][newCol].numWave == -1 && gTerrain->GetHeight(newRow, newCol) == heightStart)
        {
            if (i == 6 && gTerrain->GetHeight(row, col + 1) != heightStart)
            {
                continue;
            }
            if (i == 4 && gTerrain->GetHeight(row, col - 1) != heightStart)
            {
                continue;
            }
            if (i == 5 && gTerrain->GetHeight(row - 1, col) != heightStart)
            {
                continue;
            }
            if (i == 7 && gTerrain->GetHeight(newRow, col) != heightStart)
            {
                continue;
            }
            if (i == 4 && gTerrain->GetHeight(row - 1, col) != heightStart)
            {
                continue;
            }
            if (i == 5 && gTerrain->GetHeight(row, col + 1) != heightStart)
            {
                continue;
            }
            cells[newRow][newCol].numWave = numWave;
        }
    }
}

void PathWave::AddPrevWave(PODVector<Coord> &path)
{
    Coord coord = path[0];
    uint row = coord.row;
    uint col = coord.col;
    int numWave = cells[row][col].numWave;

    const int dRow[] = {0, -1, 0, 1, -1, -1, 1, 1};
    const int dCol[] = {-1, 0, 1, 0, -1, 1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        int iRow = (int)row + dRow[i];
        int iCol = (int)col + dCol[i];

        uint newRow = (uint)iRow;
        uint newCol = (uint)iCol;

        if (newRow < gTerrain->NumRows() && newCol < gTerrain->NumCols() && cells[newRow][newCol].numWave == numWave - 1)
        {
            path.Insert(0, Coord(newRow, newCol));
            return;
        }
    }
}
