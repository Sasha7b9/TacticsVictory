// 2021/12/4 11:09:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Objects/Units/PathFinder/PathUnit.h"
#include "Scene/World/Landscape.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/Units/Unit.h"


using namespace Pi;


#define TERRAIN_HEIGHT_EQUAL(x,z) (fabs(landscape->GetHeight((float)x, (float)z) - heightStart) < K::epsilon)


PathUnit *PathUnit::self = nullptr;


void PathUnitController::Move()
{
    Controller::Move();

    PathUnit *pathUnit = (PathUnit *)GetTargetNode();

    if(pathUnit->PathIsFound() && !pathUnit->Enabled())
    {
        pathUnit->Enable();
        pathUnit->Visualize();
    }
}


PathUnit::PathUnit() : Node("PathUnit"), Singleton<PathUnit>(self)
{
    PathUnitController *controller = new PathUnitController();
    SetController(controller);
    controller->Wake();
    Disable();

    TheWorldMgr->GetWorld()->GetRootNode()->AppendNewSubnode(this);
}


void PathUnit::Find(const UnitObject *unit, const Point2D &destination)
{
    Find(unit->GetWorldPosition().GetPoint2D(), destination);
}


void PathUnit::Find(const Point2D &source, const Point2D &destination)
{
    static bool submitted = false;       // true, если работа уже добавлена в менеджер работ

    pathIsFound = false;

    start = source;
    end = destination;

    if (jobFinder == nullptr)
    {
        jobFinder = new JobPathFinder(this);
    }

    if(submitted)
    {
        TheJobMgr->CancelJob(jobFinder);
    
        while (!jobFinder->Cancelled() || !jobFinder->Complete())
        {}
    }

    TheJobMgr->SubmitJob(jobFinder);

    submitted = true;
}


void PathUnit::JobPathFinder::JobFunction(Job *, void *cookie)
{
    PathUnit *pathUnit = (PathUnit *)cookie;

    while (!GameWorld::Get()->GetLandscape()->IsCreated())
    {
    }

    pathUnit->landscape = GameWorld::Get()->GetLandscape();
    pathUnit->SetSize();
    pathUnit->path.Clear();
    pathUnit->FindPath();
}


bool PathUnit::PathIsFound()
{
    return pathIsFound;
}


Array<Point2D> PathUnit::ToArray()
{
    return path;
}


void PathUnit::Visualize()
{
    for (Point2D &cell : path)
    {
        AppendSubnode(new CellPath(cell));
    }
}


void PathUnit::SetSize()
{
    numRows = (uint)landscape->GetSizeX();
    numCols = (uint)landscape->GetSizeY();

    cells.SetElementCount((int)numRows);

    for (auto &row : cells)
    {
        row.SetElementCount((int)numCols);
    }
}


void PathUnit::FindPath()
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


void PathUnit::Destroy()
{
}


PathUnit::CellPath::CellPath(const Point2D &position) : Node("PathUnit")
{
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

    geometry->SetNodePosition({position.x, position.y, GameWorld::Get()->GetLandscape()->GetHeight(position.x, position.y)});

    return geometry;
}
