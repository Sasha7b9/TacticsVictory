// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Objects/Units/Unit.h"
#include "Objects/Units/PathFinder/PathFinder.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(_col_, _row_) (fabs(heightMap.At(_col_, _row_) - heightStart) < K::epsilon)


void PathFinderController::Preprocess()
{
    Controller::Preprocess();

    Wake();
}


void PathFinderController::Move()
{
    PathFinder *pathUnit = (PathFinder *)GetTargetNode();

    if (pathUnit->needSearching)
    {
        pathUnit->needSearching = false;
        pathUnit->SetSize();
        pathUnit->StartSearch();
    }

    if (pathUnit->pathIsFound)
    {
        pathUnit->callbackComplete(pathUnit->path);
        pathUnit->pathIsFound = false;
        pathUnit->Clear();

        Node *target = GetTargetNode();
        target->GetRootNode()->RemoveSubnode(target);
        delete target;
    }
}


void PathFinder::StartSearch()
{
    jobFinder = new PathFinder::JobPathFinder(this);
    TheJobMgr->SubmitJob(jobFinder);
}


PathFinder::PathFinder(const Point2D &_start, const Point2D &_finish) :
    Node(StringHash(typeid(PathFinder).name())),
    start(_start), finish(_finish)
{
    SetNodeName("PathFinder");
    SetController(new PathFinderController);
}


void PathFinder::Find(std::function<void(const Array<Point2DI> &path)> funcComplete)
{
    StopSearch();

    callbackComplete = funcComplete;

    needSearching = true;
}


void PathFinder::StopSearch()
{
    if(jobFinder)
    {
        TheJobMgr->CancelJob(jobFinder);

        while (!jobFinder->Cancelled() || !jobFinder->Complete()) { }

        delete jobFinder;
        jobFinder = nullptr;
    }

    Clear();
}


void PathFinder::Clear()
{
    delete jobFinder;

    jobFinder = nullptr;

    pathIsFound = false;
}


void PathFinder::JobPathFinder::JobFunction(Job *job, void *cookie)
{
    PathFinder *pathUnit = (PathFinder *)cookie;

    pathUnit->path.Clear();
    pathUnit->FindPath(job);
}


Array<Point2DI> PathFinder::ToArray()
{
    return path;
}


void PathFinder::SetSize()
{
    while (!GameWorld::Get()->GetLandscape()->IsCreated())
    {
    }

    Landscape *landscape = GameWorld::Get()->GetLandscape();

    int sizeX_cols = landscape->GetSizeX_Columns();
    int sizeY_rows = landscape->GetSizeY_Rows();

    heightMap.SetDimensions(sizeX_cols, sizeY_rows);

    for (int row = 0; row < sizeY_rows; row++)
    {
        for (int col = 0; col < sizeX_cols; col++)
        {
            heightMap.At(col, row) = landscape->GetHeightCenter((float)col, (float)row);
        }
    }

    num_wave.SetDimensions(sizeX_cols, sizeY_rows);

    num_wave.Fill(-1);
}


void PathFinder::FindPath(Job *job)
{
    if (fabs(heightMap.At(start.x, start.y) - heightMap.At(finish.x, finish.y)) > K::epsilon)
    {
        pathIsFound = true;
        return; 
    }

    if (start == finish)
    {
        path.AddElement(start);
        pathIsFound = true;
        return;
    }

    Array<Wave> waves;

    Wave wave;
    wave.SetCell(start.x, start.y, 0, num_wave);

    waves.AddElement(wave);

    do
    {
        CalculateNextWave(waves);

    } while(waves[waves.GetElementCount() - 1].GetElementCount() &&     // В волне есть хотя бы одна клетка
            !waves[waves.GetElementCount() - 1].Contain(finish));         // И волна не содержит целевую клетку

    if(waves[waves.GetElementCount() - 1].Contain(finish))
    {
        path.AddElement(finish);
        while(path[0] != start)
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


bool PathFinder::Wave::Contain(const Point2DI &coord)
{
    for (int i = 0; i < GetElementCount(); i++)
    {
        if (points[i] == coord)
        {
            return true;
        }
    }

    return false;
}

//                                        в
//                                     в  п   в
//                                 в   п  р   л
//                                 л   р  а   е
//                                 е   а  в   в
//                                 в   в  о   о
//                          в      о   о  -   -
//                   в      п  в   -   -  в   в
//                   л   в  р  в   в   в  в   в
//                   е   н  а  е   н   н  е   е
//                   в   и  в  р   и   и  р   р
//                   о   з  о  х   з   з  х   х
static int d_x[] = {-1,  0, 1, 0, -1,  1, 1, -1};
static int d_y[] = { 0, -1, 0, 1, -1, -1, 1,  1};
//                   0   1  2  3   4   5  6   7


void PathFinder::CalculateNextWave(Array<Wave> &waves)
{
    const int num_current_wave = waves.GetElementCount();           // Рассчитываем эту волну
    const Wave &prev_wave = waves[num_current_wave - 1];            // Предыщущая рассчитанная волна
    Wave wave;

    const int sizeX_cols = heightMap.GetNumberColumns();
    const int sizeY_rows = heightMap.GetNumberRows();

    const float heightStart = heightMap.At(start.x, start.y);

    for (int j = 0; j < prev_wave.GetElementCount(); j++)
    {
        Point2DI &coord = prev_wave[j];

        for (int i = 0; i < 8; i++)
        {
            int col = coord.x;
            int row = coord.y;

            int newRow = row + d_y[i];         // Вычисляет координаты очередной
            int newCol = col + d_x[i];         // соседней клетки

            if (newRow < sizeY_rows && newRow >= 0 &&
                newCol < sizeX_cols && newCol >= 0 &&
                num_wave.At(newCol, newRow) == -1 &&                      // Если очередная соседняя клетка ещё не принадлежит никакой волне
                fabs(heightMap.At(newCol, newRow) - heightStart) < K::epsilon)
            {
                if (i == 4 && (!TERRAIN_HEIGHT_EQUAL(col, row - 1) || !TERRAIN_HEIGHT_EQUAL(col - 1, row)))
                {
                    continue;
                }
                else if (i == 5 && (!TERRAIN_HEIGHT_EQUAL(col - 1, row) || !TERRAIN_HEIGHT_EQUAL(col, row)))
                {
                    continue;
                }
                else if (i == 6 && (!TERRAIN_HEIGHT_EQUAL(col, row + 1) || !TERRAIN_HEIGHT_EQUAL(col + 1, row)))
                {
                    continue;
                }
                else if (i == 7 && (!TERRAIN_HEIGHT_EQUAL(col - 1, row) || !TERRAIN_HEIGHT_EQUAL(col, row + 1)))
                {
                    continue;
                }

                wave.SetCell(newCol, newRow, num_current_wave, num_wave);
            }
        }
    }

    waves.AddElement(wave);
}


void PathFinder::Wave::SetCell(int col, int row, int numWave, Array2D<int> &num_wave)
{
    points.AddElement(Point2DI{col, row});
    num_wave.At(col, row) = numWave;
}


void PathFinder::AddPrevWave(Array<Point2DI> &path_)
{
    int colX = path_[0].x;
    int rowY = path_[0].y;
    int numWave = num_wave.At(colX, rowY);

    for (int i = 0; i < 8; i++)
    {
        int newRow = rowY + d_y[i];
        int newCol = colX + d_x[i];

        if (newRow < heightMap.GetNumberRows() && newRow >= 0 &&
            newCol < heightMap.GetNumberColumns() && newCol >= 0 &&
            num_wave.At(newCol, newRow) == numWave - 1)
        {
            path_.InsertElement(0, Point2D((float)newCol, (float)newRow));
            return;
        }
    }
}
