// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathFinder/WaveAlgorithm.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(x,z) (fabs(landscape->GetHeight((float)x, (float)z) - heightStart) < K::epsilon)


static void FunctionFindPath(const Thread *, void *)
{
        
}


WaveAlgorithm::WaveAlgorithm() : Thread(FunctionFindPath, nullptr)
{

}


WaveAlgorithm::~WaveAlgorithm()
{
    // Stop();
}


void WaveAlgorithm::SetSize(uint rows, uint cols)
{
    numRows = rows;
    numCols = cols;

    cells.SetElementCount((int)numRows);
    for (auto &row : cells)
    {
        row.SetElementCount((int)numCols);
    }
}


void WaveAlgorithm::StartFind(Point2D start_, Point2D end_)
{
    start = start_;
    end = end_;
    // Run();
}


bool WaveAlgorithm::PathIsFound()
{
    return pathIsFound;
}


Array<Point2D> WaveAlgorithm::GetPath()
{
    // Stop();
    return path;
}


void WaveAlgorithm::ThreadFunction()
{
    pathIsFound = false;
    path.Clear();
    FindPath();
    pathIsFound = true;
}


void WaveAlgorithm::FindPath()
{
    Landscape *landscape = GameWorld::Get()->GetLandscape();

    if (fabs(landscape->GetHeight(start.x, start.y) - landscape->GetHeight(end.x, end.y)) > K::epsilon)
    {
        return;
    }

    if (start == end)
    {
        path.AddElement(start);
        return;
    }

    for (auto &row : cells)
    {
        for (auto &cell : row)
        {
            cell = -1;
        }
    }

    heightStart = landscape->GetHeight(start.x, start.y);

    Array<Wave> waves;

    Wave wave;
    SetCell(wave, (uint)start.x, (uint)start.y, 0);

    waves.AddElement(wave);

    do
    {
        NextWave(waves);
    } while(waves[waves.GetElementCount() - 1].GetElementCount() && !Contain(waves[waves.GetElementCount() - 1], end));

    if(Contain(waves[waves.GetElementCount() - 1], end))
    {
        path.AddElement(end);
        while(!(path[0] == start))
        {
            AddPrevWave(path);
        }
    }
    else
    {
        path.AddElement(start);
    }
}


bool WaveAlgorithm::Contain(const Wave &wave, const Point2D &coord)
{
    for (auto &crd : wave)
    {
        if (crd == coord)
        {
            return true;
        }
    }

    return false;
}


static int dRow[] = {0, -1, 0, 1, -1, -1, 1, 1};
static int dCol[] = {-1, 0, 1, 0, -1, 1, 1, -1};


void WaveAlgorithm::NextWave(Array<Wave> &waves)
{
    Landscape *landscape = GameWorld::Get()->GetLandscape();

    int numWave = static_cast<int>(waves.GetElementCount());
    Wave &prevWave = waves[static_cast<uint>(numWave - 1)];
    Wave wave;

    for (auto coord : prevWave)
    {
        for (int i = 0; i < 8; i++)
        {
            uint row = (uint)coord.x;
            uint col = (uint)coord.y;

            int dR = dRow[i];
            int dC = dCol[i];

            int iRow = static_cast<int>(row) + dR;
            int iCol = static_cast<int>(col) + dC;

            uint newRow = static_cast<uint>(iRow);
            uint newCol = static_cast<uint>(iCol);

            if (newRow < numRows &&
                newCol < numCols &&
                cells[newRow][newCol] == -1 &&
                fabs(landscape->GetHeightCenter((float)newRow, (float)newCol) - heightStart) < K::epsilon)
            {
                if (i == 4 && (!TERRAIN_HEIGHT_EQUAL(row, col - 1) || !TERRAIN_HEIGHT_EQUAL(row - 1, col)))
                {
                    continue;
                }
                else if (i == 5 && (!TERRAIN_HEIGHT_EQUAL(row - 1, col) || !TERRAIN_HEIGHT_EQUAL(row, col)))
                {
                    continue;
                }
                else if (i == 6 && (!TERRAIN_HEIGHT_EQUAL(row, col + 1) || !TERRAIN_HEIGHT_EQUAL(row + 1, col)))
                {
                    continue;
                }
                else if (i == 7 && (!TERRAIN_HEIGHT_EQUAL(row, col - 1) || !TERRAIN_HEIGHT_EQUAL(row + 1, col)))
                {
                    continue;
                }

                SetCell(wave, newRow, newCol, numWave);
            }
        }
    }

    waves.AddElement(wave);
}


void WaveAlgorithm::SetCell(Wave &wave, uint row, uint col, int numWave)
{
    wave.AddElement(Point2D((float)row, (float)col));
    cells[row][col] = numWave;
}


void WaveAlgorithm::AddPrevWave(Array<Point2D> &path_)
{
    Point2D coord = path_[0];
    uint rowX = (uint)coord.x;
    uint colZ = (uint)coord.y;
    int numWave = cells[rowX][colZ];

    Landscape *landscape = GameWorld::Get()->GetLandscape();

    for (int i = 0; i < 8; i++)
    {
        int iRow = static_cast<int>(rowX) + dRow[i];
        int iCol = static_cast<int>(colZ) + dCol[i];

        uint newRow = static_cast<uint>(iRow);
        uint newCol = static_cast<uint>(iCol);

        if (newRow < (uint)landscape->GetSizeX() && newCol < (uint)landscape->GetSizeY() && cells[newRow][newCol] == numWave - 1)
        {
            path_.InsertElement(0, Point2D((float)newRow, (float)newCol));
            return;
        }
    }
}
