// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathFinder/WaveAlgorithm.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(x,z) (fabs(landscape->GetHeight((float)x, (float)z) - heightStart) < K::epsilon)

namespace Pi
{

    namespace WaveAlgorithm
    {
        typedef Array<Point2D> Wave;

        static void JobFunction(Job *, void *);

        static void SetCell(Wave &wave, uint row, uint col, int numWave);
        static void NextWave(Array<Wave> &waves);
        static bool Contain(const Wave &wave, const Point2D &coord);
        static void AddPrevWave(Array<Point2D> &path);
        static void FindPath();
        static void SetSize();

        static bool pathIsFound = false;
        static Point2D start {0.0f, 0.0f};
        static Point2D end   {0.0f, 0.0f};
        static Array<Array<int>> cells;
        static float heightStart = 0.0f;
        static uint numRows = 0;                // Количество ячеек по X
        static uint numCols = 0;                // Количество ячеек по Y
        static Array<Point2D> path;             // Здесь хранится рассчитанный путь
        static Landscape *landscape = nullptr;

        class JobPathFinder : public Job
        {
        public:
            JobPathFinder() : Job(JobFunction) {};
        };

        static JobPathFinder jobFinder;
    }
}


void Pi::WaveAlgorithm::Calculate(const Point2D &_start, const Point2D &_end)
{
    static bool submitted = false;       // true, если работа уже добавлена в менеджер работ

    pathIsFound = false;

    start = _start;
    end = _end;

    landscape = GameWorld::Get()->GetLandscape();
    SetSize();

    if(submitted)
    {
        TheJobMgr->CancelJob(&jobFinder);
    
        while (!jobFinder.Cancelled() || !jobFinder.Complete())
        {}
    }

    TheJobMgr->SubmitJob(&jobFinder);

    submitted = true;
}


static void Pi::WaveAlgorithm::JobFunction(Job *, void *)
{
    path.Clear();
    FindPath();
}


bool Pi::WaveAlgorithm::PathIsFound()
{
    return pathIsFound;
}


Array<Point2D> Pi::WaveAlgorithm::GetPath()
{
    return path;
}


void Pi::WaveAlgorithm::Enable()
{

}


void Pi::WaveAlgorithm::Disable()
{

}


static void Pi::WaveAlgorithm::SetSize()
{
    numRows = (uint)landscape->GetSizeX();
    numCols = (uint)landscape->GetSizeY();

    cells.SetElementCount((int)numRows);

    for (auto &row : cells)
    {
        row.SetElementCount((int)numCols);
    }
}


static void Pi::WaveAlgorithm::FindPath()
{
    if (fabs(landscape->GetHeight(start.x, start.y) - landscape->GetHeight(end.x, end.y)) > K::epsilon)
    {
        pathIsFound = true;
        return;
    }

    if (start == end)
    {
        path.AddElement(start);
        pathIsFound = true;
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

    pathIsFound = true;
}


static bool Pi::WaveAlgorithm::Contain(const Wave &wave, const Point2D &coord)
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


static void Pi::WaveAlgorithm::NextWave(Array<Wave> &waves)
{
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


static void Pi::WaveAlgorithm::SetCell(Wave &wave, uint row, uint col, int numWave)
{
    wave.AddElement(Point2D((float)row, (float)col));
    cells[row][col] = numWave;
}


static void Pi::WaveAlgorithm::AddPrevWave(Array<Point2D> &path_)
{
    Point2D coord = path_[0];
    uint rowX = (uint)coord.x;
    uint colZ = (uint)coord.y;
    int numWave = cells[rowX][colZ];

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


void Pi::WaveAlgorithm::Destroy()
{
    path.Purge();

    for (auto &row : cells)
    {
        row.Purge();
    }

    cells.Purge();
}
