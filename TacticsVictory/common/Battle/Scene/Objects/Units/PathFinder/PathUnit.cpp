// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/Units/Unit.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(_col_, _row_) (fabs(heightMap.At(_col_, _row_) - heightStart) < K::epsilon)


PathUnit *PathUnit::self = nullptr;
List<PathUnit::CellPath> PathUnit::CellPath::chains;                   // Здесь хранятся визуализированные клеточки


void PathUnitController::Move()
{
    Controller::Move();

    PathUnit *pathUnit = (PathUnit *)GetTargetNode();

    if (!pathUnit->target)
    {
        return;
    }

    if (pathUnit->needSearching)
    {
        pathUnit->needSearching = false;
        pathUnit->start = pathUnit->target->GetWorldPosition().GetPoint2D();
        pathUnit->end = Point2DI{99, 99};

        pathUnit->SetSize();

        pathUnit->StartSearch();
    }

    if(pathUnit->pathIsFound && !pathUnit->visualized)
    {
        pathUnit->Visualize();
    }
}


void PathUnit::StartSearch()
{
    jobFinder = new PathUnit::JobPathFinder(this);
    TheJobMgr->SubmitJob(jobFinder);
}


PathUnit::PathUnit() : Node("PathUnit"), Singleton<PathUnit>(self)
{
    PathUnitController *controller = new PathUnitController();
    SetController(controller);
    controller->Wake();

    TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(this);
}


void PathUnit::SetTarget(const UnitObject *unit)
{
    StopSearch();

    target = unit;

    needSearching = true;
}


void PathUnit::RemoveTarget()
{
    StopSearch();

    target = nullptr;

    needSearching = false;
}


void PathUnit::StopSearch()
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


void PathUnit::Clear()
{
    delete jobFinder;

    jobFinder = nullptr;

    pathIsFound = false;

    for (auto *chain : CellPath::chains)
    {
        chain->Disable();
    }
}


void PathUnit::JobPathFinder::JobFunction(Job *job, void *cookie)
{
    PathUnit *pathUnit = (PathUnit *)cookie;

    pathUnit->path.Clear();
    pathUnit->FindPath(job);
}


Array<Point2DI> PathUnit::ToArray()
{
    return path;
}


void PathUnit::Visualize()
{
    TheConsoleWindow->AddText(Text::Format("In path %d elements:", path.GetElementCount()));

    for (Point2DI &point : path)
    {
        TheConsoleWindow->AddText(Text::Format("%d %d", point.x, point.y));

        if (CellPath::chains.GetElementCount())
        {
            CellPath *cell = CellPath::chains.First();
            CellPath::chains.Remove(cell);
            cell->MoveTo(point);
            AppendSubnode(cell);
            cell->Enable();
        }
        else
        {
            CellPath *cell = new CellPath(point);
            AppendSubnode(cell);
        }
    }

    visualized = true;
}


void PathUnit::SetSize()
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


void PathUnit::FindPath(Job *job)
{
    start = {0, 0};
    end = {1, 2};

    if (fabs(heightMap.At(start.x, start.y) - heightMap.At(end.x, end.y)) > K::epsilon)
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

    Array<Wave> waves;

    Wave wave;
    wave.SetCell(start.x, start.y, 0, num_wave);

    waves.AddElement(wave);

    do
    {
        int numElements = waves[waves.GetElementCount() - 1].GetElementCount();

        CalculateNextWave(waves);

        numElements = waves[waves.GetElementCount() - 1].GetElementCount();
        numElements = numElements;

    } while(waves[waves.GetElementCount() - 1].GetElementCount() &&     // В волне есть хотя бы одна клетка
            !waves[waves.GetElementCount() - 1].Contain(end));         // И волна не содержит целевую клетку

    if(waves[waves.GetElementCount() - 1].Contain(end))
    {
        path.AddElement(end);
        while(path[0] != start)
        {
            AddPrevWave(path);
        }
    }
    else
    {
        path.AddElement(start);
    }

    TheConsoleWindow->AddText(Text::Format("Start : %d %d", start.x, start.y));
    TheConsoleWindow->AddText(Text::Format("End : %d %d", end.x, end.y));
    TheConsoleWindow->AddText(Text::Format("Total %d waves", waves.GetElementCount()));

    pathIsFound = true;
}


bool PathUnit::Wave::Contain(const Point2DI &coord)
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


void PathUnit::CalculateNextWave(Array<Wave> &waves)
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

            

            if (newRow == 1 && newCol == 1)
            {
                newRow = newRow;
                float height = heightMap.At(newCol, newRow);
                height = height;
            }

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
                else if (i == 7 && (!TERRAIN_HEIGHT_EQUAL(col, row - 1) || !TERRAIN_HEIGHT_EQUAL(col + 1, row)))
                {
                    continue;
                }

                wave.SetCell(newCol, newRow, num_current_wave, num_wave);
            }
        }
    }

    waves.AddElement(wave);
}


void PathUnit::Wave::SetCell(int col, int row, int numWave, Array2D<int> &num_wave)
{
    points.AddElement(Point2DI{col, row});
    num_wave.At(col, row) = numWave;
}


void PathUnit::AddPrevWave(Array<Point2DI> &path_)
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


PathUnit::CellPath::CellPath(const Point2DI &position) : Node(), ListElement<CellPath>()
{
    SetNodeName("CellPath");
    AppendSubnode(CreateMember({(float)(int)position.x + 0.5f, (float)(int)position.y + 0.5f}));
    GameWorld::Get()->GetRootNode()->AppendNewSubnode(this);
}


Node *PathUnit::CellPath::CreateMember(const Point2D &position)
{
    float size = 0.4f;

    PrimitiveGeometry *geometry = new SphereGeometry({size, size, 0.1f});
    PrimitiveGeometryObject *object = geometry->GetObject();
    object->SetCollisionExclusionMask(PiKindCollision::PathUnit);
    object->DissableGeometryFlags(PiFlagGeometry::CastShadows);
    object->SetBuildLevelCount(1);
    geometry->Update();
    object->Build(geometry);
    geometry->Update();

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(K::blue);
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    MoveTo(position);

    return geometry;
}


void PathUnit::CellPath::MoveTo(const Point2DI &position)
{
    SetNodePosition({(float)position.x + 0.5F, (float)position.y + 0.5F,
                    GameWorld::Get()->GetLandscape()->GetHeightAccurately((float)position.x + 0.5f, (float)position.y + 0.5f)});
}
