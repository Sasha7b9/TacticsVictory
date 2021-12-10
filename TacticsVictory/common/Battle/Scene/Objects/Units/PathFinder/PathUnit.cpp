// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/Units/Unit.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(x,z) (fabs(landscape->GetHeight((float)x, (float)z) - heightStart) < K::epsilon)


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
        pathUnit->start.x = (float)(int)pathUnit->start.x;
        pathUnit->start.y = (float)(int)pathUnit->start.y;
        pathUnit->end = Point2D{99.0f, 99.0f};

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

    while (!GameWorld::Get()->GetLandscape()->IsCreated())
    {
    }

    pathUnit->landscape = GameWorld::Get()->GetLandscape();
    pathUnit->SetSize();
    pathUnit->path.Clear();
    pathUnit->FindPath(job);
}


Array<Point2D> PathUnit::ToArray()
{
    return path;
}


void PathUnit::Visualize()
{
    for (Point2D &point : path)
    {
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
            AppendSubnode(new CellPath(point));
        }
    }

    visualized = true;
}


void PathUnit::SetSize()
{
    numRows = (uint)landscape->GetSizeX();
    numCols = (uint)landscape->GetSizeY();

    cells.SetDimensions((int)numRows, (int)numCols);
}


void PathUnit::FindPath(Job *job)
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

    cells.Fill(-1);

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


bool PathUnit::Contain(const Wave &wave, const Point2D &coord)
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


void PathUnit::NextWave(Array<Wave> &waves)
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


void PathUnit::SetCell(Wave &wave, uint row, uint col, int numWave)
{
    wave.AddElement(Point2D((float)row, (float)col));
    cells[row][col] = numWave;
}


void PathUnit::AddPrevWave(Array<Point2D> &path_)
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


PathUnit::CellPath::CellPath(const Point2D &position) : Node(), ListElement<CellPath>()
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


void PathUnit::CellPath::MoveTo(const Point2D &position)
{
    SetNodePosition({position.x, position.y, GameWorld::Get()->GetLandscape()->GetHeight(position.x, position.y)});
}
