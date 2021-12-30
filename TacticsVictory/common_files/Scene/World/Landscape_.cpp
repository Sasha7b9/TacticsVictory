// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/World/Landscape_.h"
#include "Scene/World/GameWorld.h"
#include "GameState.h"
#include "PeriodicTasks.h"


namespace Pi
{
class TCell;
class TZone;
class Landscape;


TCell     *mapCell = nullptr;
TZone     *mapZone = nullptr;
static Landscape *landscape = nullptr;

Landscape *Landscape::self = nullptr;

int TZone::NUM_ROWS_Y = 0;
int TZone::NUM_COLS_X = 0;

int TCell::NUM_ROWS_Y = 0;
int TCell::NUM_COLS_X = 0;


class CoordCell : public MapElement <CoordCell>
{

public:

    typedef Type KeyType;

    static KeyType Key(int firstNeighbor, int secondNeighbor, int thirdNeighbor)
    {
        return (uint)((firstNeighbor + 1) << 4) + (uint)((secondNeighbor + 1) << 2) + (uint)(thirdNeighbor + 1);
    }

    CoordCell(int firstNeighbor, int secondNeighbor, int thirdNeighbor, float x, float y) : coord(x, y)
    {
        key = (uint)((firstNeighbor + 1) << 4) + (uint)((secondNeighbor + 1) << 2) + (uint)(thirdNeighbor + 1);
    };

    KeyType GetKey() const
    {
        return key;
    }

    Point2D coord;

private:

    KeyType key;
};

static Map<CoordCell> mapLeftTop;       //  second  third   -
                                        //  first   me      -
                                        //  -       -       -

static Map<CoordCell> mapRightTop;      //  -       first   second
                                        //  -       me      third
                                        //  -       -       -

static Map<CoordCell> mapRightBottom;   //  -       -       -
                                        //  -       me      first
                                        //  -       third   second

static Map<CoordCell> mapLeftBottom;    //  -       -       -
                                        //  first   me      -
                                        //  second  third   -


class DrawTriangle : public MapElement < DrawTriangle >
{

public:

    typedef Type KeyType;

    static KeyType Key(int firstNeighbor, int secondNeighbor, int thirdNeighbor)
    {
        return (uint)((firstNeighbor + 1) << 4) + (uint)((secondNeighbor + 1) << 2) + (uint)(thirdNeighbor + 1);
    }

    DrawTriangle(int firstNeighbor, int secondNeighbor, int thirdNeighbor, const Integer3D& _p0, const Integer3D& _p1, const Integer3D& _p2) : p0(_p0), p1(_p1), p2(_p2)
    {
        key = (uint)((firstNeighbor + 1) << 4) + (uint)((secondNeighbor + 1) << 2) + (uint)(thirdNeighbor + 1);
    }

    int Draw(GeometrySurface *surface, int x, int y)
    {
        return Landscape::AddTriangle(surface, Landscape::NewPoint(x, y, p0.x, p0.y, p0.z), Landscape::NewPoint(x, y, p1.x, p1.y, p1.z),
            Landscape::NewPoint(x, y, p2.x, p2.y, p2.z));
    }

    KeyType GetKey() const
    {
        return key;
    }

private:

    Integer3D p0;
    Integer3D p1;
    Integer3D p2;

    KeyType key;
};

static Map<DrawTriangle> triangleLeftTop;
static Map<DrawTriangle> triangleRightTop;
static Map<DrawTriangle> triangleRightBottom;
static Map<DrawTriangle> triangleLeftBottom;

}


using namespace Pi;



Landscape::Landscape(pchar nameFile, PeriodicTask *afterTask, float delta) : Node()
{
    self = this;
    this->delta = delta;
    landscape = this;
    taskAfter = afterTask;

    heightMap = ReadFile(nameFile);

    FillTables();

    TCell::NUM_ROWS_Y = heightMap.GetNumberRows();
    TCell::NUM_COLS_X = heightMap.GetNumberColumns();

    TZone::NUM_ROWS_Y = TCell::NUM_ROWS_Y / TZone::SIZE_SIDE + ((TCell::NUM_ROWS_Y % TZone::SIZE_SIDE == 0) ? 0 : 1);
    TZone::NUM_COLS_X = TCell::NUM_COLS_X / TZone::SIZE_SIDE + ((TCell::NUM_COLS_X % TZone::SIZE_SIDE == 0) ? 0 : 1);

    mapCell = new TCell[(size_t)TCell::NUM_ROWS_Y * (size_t)TCell::NUM_COLS_X];
    mapZone = new TZone[(size_t)TZone::NUM_ROWS_Y * (size_t)TZone::NUM_COLS_X];

    FillMap(heightMap);

    controller = new LandscapeController();
    SetController(controller);
    controller->Wake();
    SetNodePosition({0 - 0.5f, (float)GetSizeY_Rows() - 0.5f, 0});
}


Landscape::~Landscape()
{
    mapLeftTop.Purge();
    mapRightTop.Purge();
    mapLeftBottom.Purge();
    mapRightBottom.Purge();
    triangleLeftTop.Purge();
    triangleRightTop.Purge();
    triangleLeftBottom.Purge();
    triangleRightBottom.Purge();

    SAFE_DELETE(controller);

    SAFE_DELETE_ARRAY(mapCell);
    SAFE_DELETE_ARRAY(mapZone);
}


void Landscape::FillMap(const Array2D<float> &array)
{
    for (int row = 0; row < TCell::NUM_ROWS_Y; row++)
    {
        FillRowTCell(row, array, mapCell + row * TCell::NUM_COLS_X);
    }

    for (int row = 0; row < TZone::NUM_ROWS_Y; row++)
    {
        for (int col = 0; col < TZone::NUM_COLS_X; col++)
        {
            TZone *zone = TZone::Get(col, row);
            if (zone)
            {
                zone->Construct(col, row);
            }
        }
    }
}


void Landscape::Reload()
{
    Array2D<float> map = ReadFile(file.GetFileName());

    for (int col = 0; col < map.GetNumberColumns(); col++)
    {
        for (int row = 0; row < map.GetNumberRows(); row++)
        {
            if (map.At(col, row) != heightMap.At(col, row))
            {
                TCell::Get(col, row)->zone->state = TZone::State::NeedReload;
            }
        }
    }

    heightMap = map;

    for (int row = 0; row < TCell::NUM_ROWS_Y; row++)
    {
        FillRowTCell(row, heightMap, mapCell + row * TCell::NUM_COLS_X);
    }

    for (int col = 0; col < TZone::NUM_COLS_X; col++)
    {
        for (int row = 0; row < TZone::NUM_ROWS_Y; row++)
        {
            TZone *zone = TZone::Get(col, row);

            if (zone->state == TZone::State::NeedReload)
            {
                zone->geometry->Neutralize();
                RemoveSubnode(zone->geometry);
                delete zone->geometry;
                zone->state = TZone::State::Empty;
                CreateGeometryForZone(zone);
                AddSurfaceToMesh(zone);
            }
        }
    }
}


void Landscape::AddSurfaceToMesh(TZone *zone)
{
    if (zone->state == TZone::State::Empty || zone->state == TZone::State::Added)
    {
        return;
    }

    AppendNewSubnode(zone->geometry);
    zone->geometry->GetObject()->SetCollisionExclusionMask(PiKindCollision::Landscape);
    zone->state = TZone::State::Added;
}


int Landscape::DeltaZ(int thisX, int thisY, int x, int y)
{
    float thisDelta = CellZ(thisX, thisY);
    float dZ = CellZ(x, y);
    if(thisDelta == dZ)        
    {
        return 0;
    }
    return thisDelta < dZ ? 1 : -1;
}
void Landscape::FillTables()
{
    mapLeftTop.Insert(new CoordCell(0, 0, 1, -delta, -delta));
    mapLeftTop.Insert(new CoordCell(0, 1, 0, delta, -delta));
    mapLeftTop.Insert(new CoordCell(0, 1, 1, 0.0f, -delta));
    mapLeftTop.Insert(new CoordCell(1, 0, 0, delta, delta));
    mapLeftTop.Insert(new CoordCell(1, 1, 0, delta, 0.0f));
    mapLeftTop.Insert(new CoordCell(1, 1, 1, delta, -delta));

    mapLeftTop.Insert(new CoordCell(0, 0, -1, -delta, -delta));
    mapLeftTop.Insert(new CoordCell(0, -1, 0, delta, -delta));
    mapLeftTop.Insert(new CoordCell(0, -1, -1, 0.0f, -delta));
    mapLeftTop.Insert(new CoordCell(-1, 0, 0, delta, delta));
    mapLeftTop.Insert(new CoordCell(-1, -1, 0, delta, 0.0f));
    mapLeftTop.Insert(new CoordCell(-1, -1, -1, delta, -delta));

    mapLeftTop.Insert(new CoordCell(-1, 1, 0, delta, 0.0f));
    mapLeftTop.Insert(new CoordCell(1, -1, 0, delta, 0.0f));
    mapLeftTop.Insert(new CoordCell(0, -1, 1, 0, -delta));
    mapLeftTop.Insert(new CoordCell(0, 1, -1, 0, -delta));
    mapLeftTop.Insert(new CoordCell(-1, 1, -1, delta, -delta));
    mapLeftTop.Insert(new CoordCell(1, -1, -1, delta, -delta));
    mapLeftTop.Insert(new CoordCell(-1, 1, 1, delta, -delta));
    mapLeftTop.Insert(new CoordCell(1, 1, -1, delta, -delta));
    mapLeftTop.Insert(new CoordCell(-1, -1, 1, delta, -delta));

    mapRightTop.Insert(new CoordCell(0, 0, 1, 1.0f - delta, delta));
    mapRightTop.Insert(new CoordCell(0, 1, 0, 1.0f - delta, -delta));
    mapRightTop.Insert(new CoordCell(0, 1, 1, 1.0f - delta, 0.0f));
    mapRightTop.Insert(new CoordCell(1, 0, 0, 1.0f + delta, -delta));
    mapRightTop.Insert(new CoordCell(1, 1, 0, 1.0f, -delta));
    mapRightTop.Insert(new CoordCell(1, 1, 1, 1.0f - delta, -delta));

    mapRightTop.Insert(new CoordCell(0, 0, -1, 1.0f - delta, delta));
    mapRightTop.Insert(new CoordCell(0, -1, 0, 1.0f - delta, -delta));
    mapRightTop.Insert(new CoordCell(0, -1, -1, 1.0f - delta, 0.0f));
    mapRightTop.Insert(new CoordCell(-1, 0, 0, 1.0f + delta, -delta));
    mapRightTop.Insert(new CoordCell(-1, -1, 0, 1.0f, -delta));
    mapRightTop.Insert(new CoordCell(-1, -1, -1, 1.0f - delta, -delta));

    mapRightTop.Insert(new CoordCell(-1, -1, 1, 1.0f - delta, -delta));
    mapRightTop.Insert(new CoordCell(-1, 1, 0, 1.0f, -delta));
    mapRightTop.Insert(new CoordCell(1, -1, 0, 1.0f, -delta));
    mapRightTop.Insert(new CoordCell(0, -1, 1, 1.0f - delta, 0.0f));
    mapRightTop.Insert(new CoordCell(-1, 1, -1, 1.0f - delta, -delta));
    mapRightTop.Insert(new CoordCell(0, 1, -1, 1.0f - delta, 0.0f));
    mapRightTop.Insert(new CoordCell(1, 1, -1, 1.0f - delta, -delta));
    mapRightTop.Insert(new CoordCell(1, -1, -1, 1.0f - delta, -delta));

    mapLeftBottom.Insert(new CoordCell(0, 0, 1, -delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, 1, 1, 0.0f, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, 1, 0, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(1, 1, 0, delta, -1.0f));
    mapLeftBottom.Insert(new CoordCell(1, 0, 0, delta, -1.0f - delta));
    mapLeftBottom.Insert(new CoordCell(1, 1, 1, delta, -1.0f + delta));

    mapLeftBottom.Insert(new CoordCell(-1, -1, 0, delta, -1.0f));
    mapLeftBottom.Insert(new CoordCell(-1, -1, -1, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, -1, -1, 0.0f, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, 0, -1, -delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, -1, 0, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(-1, 0, 0, delta, -1.0f - delta));

    mapLeftBottom.Insert(new CoordCell(1, -1, 0, delta, -1.0f));
    mapLeftBottom.Insert(new CoordCell(-1, 1, 0, delta, -1.0f));
    mapLeftBottom.Insert(new CoordCell(-1, -1, 1, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(-1, 1, -1, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, 1, -1, 0.0f, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(0, -1, 1, 0.0f, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(1, -1, -1, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(1, 1, -1, delta, -1.0f + delta));
    mapLeftBottom.Insert(new CoordCell(-1, 1, 1, delta, -1.0f + delta));

    mapRightBottom.Insert(new CoordCell(0, 1, 0, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(1, 1, 0, 1.0f - delta, -1.0f));
    mapRightBottom.Insert(new CoordCell(1, 0, 0, 1.0f - delta, -1.0f - delta));
    mapRightBottom.Insert(new CoordCell(0, 1, 1, 1.0f, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(0, 0, 1, 1.0f + delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(1, 1, 1, 1.0f - delta, -1.0f + delta));

    mapRightBottom.Insert(new CoordCell(0, -1, -1, 1.0f, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(0, -1, 0, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, -1, 0, 1.0f - delta, -1.0f));
    mapRightBottom.Insert(new CoordCell(-1, 0, 0, 1.0f - delta, -1.0f - delta));
    mapRightBottom.Insert(new CoordCell(0, 0, -1, 1.0f + delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, -1, -1, 1.0f - delta, -1.0f + delta));

    mapRightBottom.Insert(new CoordCell(1, -1, -1, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, -1, 1, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(1, 1, -1, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, 1, -1, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, 1, 0, 1.0f - delta, -1.0f));
    mapRightBottom.Insert(new CoordCell(1, -1, 0, 1.0f - delta, -1.0f));
    mapRightBottom.Insert(new CoordCell(0, -1, 1, 1.0f, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(0, 1, -1, 1.0f, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(-1, 1, 1, 1.0f - delta, -1.0f + delta));
    mapRightBottom.Insert(new CoordCell(1, -1, 1, 1.0f - delta, -1.0f + delta));

    triangleLeftTop.Insert(new DrawTriangle(-1, 1, 1, {1, -1, 0}, {2, -1, -1}, {0, 0, 0}));
    triangleLeftTop.Insert(new DrawTriangle(1, 1, -1, {0, 0, 0}, {1, -1, 0}, {3, 0, -1}));
    triangleLeftTop.Insert(new DrawTriangle(1, -1, -1, {0, 0, 0}, {1, -1, 0}, {2, -1, -1}));
    triangleLeftTop.Insert(new DrawTriangle(0, 1, -1, {0, 0, 0}, {2, -1, -1}, {3, 0, -1}));
    triangleLeftTop.Insert(new DrawTriangle(1, -1, 0, {0, 0, 0}, {1, -1, 0}, {2, -1, -1}));
    triangleLeftTop.Insert(new DrawTriangle(-1, -1, 1, {0, 0, 0}, {1, -1, 0}, {3, 0, -1}));

    triangleLeftBottom.Insert(new DrawTriangle(1, 1, -1, {0, 0, 1}, {1, -1, 1}, {3, 0, 0}));
    triangleLeftBottom.Insert(new DrawTriangle(-1, 1, 1, {2, -1, 0}, {3, 0, 0}, {1, -1, 1}));
    triangleLeftBottom.Insert(new DrawTriangle(1, -1, -1, {1, -1, 1}, {2, -1, 0}, {3, 0, 0}));
    triangleLeftBottom.Insert(new DrawTriangle(0, -1, 1, {1, -1, 1}, {3, 0, 0}, {0, 0, 1}));
    triangleLeftBottom.Insert(new DrawTriangle(1, -1, 0, {3, 0, 0}, {1, -1, 1}, {2, -1, 0}));
    triangleLeftBottom.Insert(new DrawTriangle(-1, -1, 1, {3, 0, 0}, {0, 0, 1}, {1, -1, 1}));

    triangleRightBottom.Insert(new DrawTriangle(1, -1, -1, {2, 0, 0}, {3, 1, 0}, {0, 1, 1}));
    triangleRightBottom.Insert(new DrawTriangle(-1, -1, 1, {2, 0, 0}, {3, 1, 0}, {1, 0, 1}));
    triangleRightBottom.Insert(new DrawTriangle(-1, 1, 0, {2, 0, 0}, {3, 1, 0}, {0, 1, 1}));
    triangleRightBottom.Insert(new DrawTriangle(0, -1, 1, {2, 0, 0}, {0, 1, 1}, {1, 0, 1}));
    triangleRightBottom.Insert(new DrawTriangle(-1, 1, 1, {2, 0, 0}, {3, 1, 0}, {0, 1, 1}));

    triangleRightTop.Insert(new DrawTriangle(-1, -1, 1, {1, 0, 0}, {2, 0, -1}, {0, 1, 0}));
    triangleRightTop.Insert(new DrawTriangle(1, 1, -1, {1, 0, 0}, {2, 0, -1}, {0, 1, 0}));
    triangleRightTop.Insert(new DrawTriangle(1, -1, -1, {1, 0, 0}, {2, 0, -1}, {0, 1, 0}));
    triangleRightTop.Insert(new DrawTriangle(-1, 1, 0, {1, 0, 0}, {2, 0, -1}, {3, 1, -1}));
}


Point3D Landscape::CoordVertex(int numVert, int x, int y)
{
    /*
    0,0   1,0
    0 0---1
    |\ \  |
    | \ \ |   // If see from up
    |  \ \|
    3---2 2
    0,-1  1,-1
    */
    
    float Z = 0.0f;

    if(x >= 0 && x < TCell::NUM_COLS_X && y >= 0 && y < TCell::NUM_ROWS_Y)
    {
        TCell *cell = TCell::Get(x, y);
        if (cell)
        {
            Z = cell->height;
        }
    }

    switch(numVert)
    {
        case 0:
        {
            if((y < 0 || x < 0) || (x > TCell::NUM_COLS_X - 1) || (y > TCell::NUM_ROWS_Y - 1))
            {
                return Point3D(0.0f, 0.0f, 0.0f);
            }
            if(y == 0 || x == 0)
            {
                return Point3D(0.0f, 0.0f, Z);
            }
            
            CoordCell *coord = mapLeftTop.Find(CoordCell::Key(DeltaZ(x, y, x - 1, y), DeltaZ(x, y, x - 1, y - 1), DeltaZ(x, y, x, y - 1)));
            if(coord)
            {
                return Point3D(coord->coord, Z);
            }
            
            return Point3D(0.0f, 0.0f, Z);
        }

        case 1:
        {
            if((y < 0 || x > TCell::NUM_COLS_X - 1) || (x < 0) || (y > TCell::NUM_ROWS_Y - 1))
            {
                return Point3D(1.0f, 0.0f, 0.0f);
            }
            if((y == 0) || (x == TCell::NUM_COLS_X - 1))
            {
                return Point3D(1.0f, 0.0f, Z);
            }
           
            CoordCell *coord = mapRightTop.Find(CoordCell::Key(DeltaZ(x, y, x, y - 1), DeltaZ(x, y, x + 1, y - 1), DeltaZ(x, y, x + 1, y)));
            if(coord)
            {
                return Point3D(coord->coord, Z);
            }


            return Point3D(1.0f, 0.0f, Z);
        }

        case 2:
        {
            if((y < 0) || (x < 0))
            {
                return Point3D(1.0f, -1.0f, 0.0f);
            }
            if(y == TCell::NUM_ROWS_Y - 1 || x == TCell::NUM_COLS_X - 1)
            {
                return Point3D(1.0f, -1.0f, Z);
            }
            CoordCell *coord = mapRightBottom.Find(CoordCell::Key(DeltaZ(x, y, x + 1, y), DeltaZ(x, y, x + 1, y + 1), DeltaZ(x, y, x, y + 1)));
            if(coord)
            {
                return Point3D(coord->coord, Z);
            }
            

            return Point3D(1.0f, -1.0f, Z);
        }

        case 3:
        {
            if((y < 0) || (x > TCell::NUM_COLS_X - 1))
            {
                return Point3D(0.0f, -1.0f, 0.0f);
            }
            if(x == 0 || y == TCell::NUM_ROWS_Y - 1)
            {
                return Point3D(0.0f, -1.0f, Z);
            }

            CoordCell *coord = mapLeftBottom.Find(CoordCell::Key(DeltaZ(x, y, x - 1, y), DeltaZ(x, y, x - 1, y + 1), DeltaZ(x, y, x, y + 1)));
            if(coord)
            {
                return Point3D(coord->coord, Z);
            }

            return Point3D(0.0f, -1.0f, Z);
        }


    }

    return Point3D(0.0f, 0.0f, Z);
}

float Landscape::CellZ(int x, int y)
{
    TCell *cell = TCell::Get(x, y);
    return cell ? cell->height : 0.0f;
}

float MyCeil(float x)
{
    //for(float value = 1000.0f; value > 1.0F; value--)
    for(int v = 1000; v > 1; v--)
    {
        float value = (float)v;

        if(x > value)
        {
            return value;
        }
    }
    return 1.0F;
}

int Landscape::AddTriangle(GeometrySurface *surface, const Point3D& point0, const Point3D& point1, const Point3D& point2)
{
    Point3D points[] = {
        point0,
        point2,
        point1
    };

    return Landscape::AddTriangle(surface, points);
}

int Landscape::AddTriangle(GeometrySurface *surface, const Point3D points[3])
{
    Point2D texCoord[] = {
        Point2D(0.0f, 0.0f),
        Point2D(0.0f, 1.0f),
        Point2D(1.0f, 0.0f)
    };

    Vector3D normals[] = {
        Cross(points[1] - points[0], points[2] - points[0]),
        Cross(points[2] - points[1], points[0] - points[1]),
        Cross(points[0] - points[2], points[1] - points[2])
    };

    GeometryPolygon *polygon = new GeometryPolygon();

    for(int i = 0; i < 3; i++)
    {
        GeometryVertex *vertex = new GeometryVertex();
        vertex->position = points[i];
        vertex->normal = normals[i];
        vertex->texcoord[0] = texCoord[i];
        polygon->vertexList.Append(vertex);
    }

    surface->polygonList.Append(polygon);

    return 3;
}

int Landscape::AddPlane(GeometrySurface *surface, const Point3D& point0, const Point3D& point1, const Point3D& point2, const Point3D& point3)
{
    Point3D points[4] = {
        point0,
        point1,
        point2,
        point3
    };

    return AddPlane(surface, points);
}

int Landscape::AddPlane(GeometrySurface *surface, const Point3D points[4])
{
    Vector2D size = CalculateSizePlane(points);
    size.x = MyCeil(size.x);
    size.y = MyCeil(size.y);

    const float k = 1.0f;

    Point2D texCoord[] = {
        Point2D(0.0f, 0.0f),
        Point2D(0.0f, 1.0f * size.y * k),
        Point2D(1.0f * size.x * k, 0.0f),
        Point2D(1.0f * size.x * k, 0.0f),
        Point2D(0.0f, 1.0f * size.y * k),
        Point2D(1.0f * size.x * k, 1.0f * size.y * k)
    };

    Point3D positons[6] = {
        points[3],
        points[0],
        points[2],
        points[2],
        points[0],
        points[1]
    };

    Vector3D normals[6] = {
        Cross(points[3] - points[0], points[3] - points[2]),
        Cross(points[0] - points[2], points[0] - points[3]),
        Cross(points[2] - points[3], points[2] - points[0]),
        Cross(points[0] - points[2], points[1] - points[2]),
        Cross(points[1] - points[0], points[2] - points[0]),
        Cross(points[2] - points[1], points[0] - points[1])
    };

    GeometryPolygon *polygon(new GeometryPolygon());

    for (int i = 0; i < 3; i++)
    {
        GeometryVertex *vertex(new GeometryVertex());
        vertex->position = positons[i];
        vertex->normal = normals[i];
        vertex->texcoord[0] = texCoord[i];
        polygon->vertexList.Append(vertex);
    }

    surface->polygonList.Append(polygon);

    polygon = new GeometryPolygon();

    for (int i = 3; i < 6; i++)
    {
        GeometryVertex *vertex(new GeometryVertex());
        vertex->position = positons[i];
        vertex->normal = normals[i];
        vertex->texcoord[0] = texCoord[i];
        polygon->vertexList.Append(vertex);
    }

    surface->polygonList.Append(polygon);

    return 6;
}

Vector2D Landscape::CalculateSizePlane(const Point3D ponts[4])
{
    float length0 = Magnitude(ponts[1] - ponts[0]);
    float length1 = Magnitude(ponts[2] - ponts[1]);
    float length2 = Magnitude(ponts[3] - ponts[2]);
    float length3 = Magnitude(ponts[0] - ponts[3]);

    Vector2D size;

    size.x = length0;
    if(length2 > length0)
    {
        size.x = length2;
    }

    size.y = length1;
    if(length3 > length1)
    {
        size.y = length3;
    }

    return size;
}

Point3D Landscape::NewPoint(int x, int y, int num, int dX, int dY)
{
    return CoordVertex(num, x + dX, y + dY) + Point3D((float)(x + dX), -(float)(y + dY), 0.0f);
}

#define NEW_POINT(num, dX, dY) NewPoint(x, y, num, dX, dY)

int Landscape::AddFace(GeometrySurface *surface, int x, int y)
{
    int numVertices = AddPlane(surface, NEW_POINT(0, 0, 0), NEW_POINT(3, 0, 0), NEW_POINT(2, 0, 0), NEW_POINT(1, 0, 0));

    // Draw left side plane

    if(x == 0)
    {
        numVertices += AddPlane(surface, NEW_POINT(1, -1, 0), NEW_POINT(2, -1, 0), NEW_POINT(3, 0, 0), NEW_POINT(0, 0, 0));
    }
    else
    {
        if(CellZ(x - 1, y) > CellZ(x, y))
        {
            numVertices += AddPlane(surface, NEW_POINT(2, -1, 0), NEW_POINT(3, 0, 0), NEW_POINT(0, 0, 0), NEW_POINT(1, -1, 0));
        }
    }

    // Draw right side plane

    if(x == TCell::NUM_COLS_X - 1)
    {
        numVertices += AddPlane(surface, NEW_POINT(1, 0, 0), NEW_POINT(2, 0, 0), NEW_POINT(3, 1, 0), NEW_POINT(0, 1, 0));
    }
    else
    {
        if(CellZ(x + 1, y) > CellZ(x, y))
        {
            numVertices += AddPlane(surface, NEW_POINT(1, 0, 0), NEW_POINT(2, 0, 0), NEW_POINT(3, 1, 0), NEW_POINT(0, 1, 0));
        }
    }

    // Draw top side plane

    if(y == 0)
    {
        numVertices += AddPlane(surface, NEW_POINT(0, 0, 0), NEW_POINT(1, 0, 0), NEW_POINT(2, 0, -1), NEW_POINT(3, 0, -1));
    }
    else
    {
        if(CellZ(x, y - 1) > CellZ(x, y))
        {
            numVertices += AddPlane(surface, NEW_POINT(1, 0, 0), NEW_POINT(2, 0, -1), NEW_POINT(3, 0, -1), NEW_POINT(0, 0, 0));
        }

    }

    // Draw bottom side plane

    if(y == TCell::NUM_ROWS_Y - 1)
    {
        numVertices += AddPlane(surface, NEW_POINT(3, 0, 0), NEW_POINT(0, 0, 1), NEW_POINT(1, 0, 1), NEW_POINT(2, 0, 0));
    }
    else
    {
        if(CellZ(x, y + 1) > CellZ(x, y))
        {
            numVertices += AddPlane(surface, NEW_POINT(0, 0, 1), NEW_POINT(1, 0, 1), NEW_POINT(2, 0, 0), NEW_POINT(3, 0, 0));
        }
    }

    if(x > 0 && y > 0)
    {
        DrawTriangle *triangle = triangleLeftTop.Find(DrawTriangle::Key(DeltaZ(x, y, x - 1, y), DeltaZ(x, y, x - 1, y - 1), DeltaZ(x, y, x, y - 1)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    if(x > 0 && y < TCell::NUM_ROWS_Y - 1)
    {
        DrawTriangle *triangle = triangleLeftBottom.Find(DrawTriangle::Key(DeltaZ(x, y, x - 1, y), DeltaZ(x, y, x - 1, y + 1), DeltaZ(x, y, x, y + 1)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    if(x < TCell::NUM_COLS_X - 1 && y < TCell::NUM_ROWS_Y - 1)
    {
        DrawTriangle *triangle = triangleRightBottom.Find(DrawTriangle::Key(DeltaZ(x, y, x + 1, y), DeltaZ(x, y, x + 1, y + 1), DeltaZ(x, y, x, y + 1)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    if(x < TCell::NUM_COLS_X - 1 && y > 0)
    {
        DrawTriangle *triangle = triangleRightTop.Find(DrawTriangle::Key(DeltaZ(x, y, x, y - 1), DeltaZ(x, y, x + 1, y - 1), DeltaZ(x, y, x + 1, y)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    return numVertices;
}


Array2D<float> Landscape::ReadFile(pchar nameFile)
{
    Array2D<float> result;

    if (file.Open(nameFile) != FileResult::Okay)
    {
        LOG_ERROR("Can't open file %s", nameFile);
        return result;
    }

    uint64 size = file.GetSize();

    MemoryBuffer<char> buffer(size);
    file.Read(buffer.data, (uint)size);

    file.Close();

    int sizeY = GetRowsInMap(buffer.data, (int)size);
    int sizeX = GetNumElementInLine(buffer.data);

    result.SetDimensions(sizeX, sizeY);

    char *pointer = buffer.data;

    for (int row = 0; row < sizeY; row++)
    {
        pointer = ParseRowLandscape(false, pointer, row, result);
    }

    pointer += 3;

    for (int row = 0; row < sizeY; row++)
    {
        pointer = ParseRowLandscape(true, pointer, row, result);
    }

    return result;
}


int Landscape::GetRowsInMap(char *buffer, int size)
{
    int numLines = 0;

    char *end_buffer = buffer + (size_t)size;

    while(buffer++ < end_buffer)
    {
        if(*buffer == 0x0d)
        {
            numLines++; //-V127
        }

        if (*(buffer + 1) == 0x0a &&        // Двойной конец строки означает, что дальше идёт карта глубины
            *(buffer + 2) == 0x0d &&
            *(buffer + 3) == 0x0a)
        {
            break;
        }
    }

    return numLines;
}


int Landscape::GetNumElementInLine(char *text)
{
    int numElements = 0;

    enum class State
    {
        Element,
        Space
    } state = State::Element;

    char* pointer = text;

    while(*pointer != 0x0d)
    {
        switch(state)
        {
            case State::Element:
                if(*pointer == ' ' || *pointer == 0x0d)
                {
                    numElements++;
                    state = State::Space;
                }
                break;

            case State::Space:
                if(*pointer != ' ' && *pointer != 0x0d)
                {
                    state = State::Element;
                }
                break;
        }
        pointer++;
    }

    return numElements + 1;
}


char *Landscape::ParseRowLandscape(bool forWater, char * const text, int row, Array2D<float> &array)
{
    char *pointer = text;
    int col = 0;

    char *firstSymbol = pointer;
    char *lastSymbol = pointer;
    lastSymbol--;
    pointer--;

    enum class State
    {
        InValue,
        InSpace
    } state = State::InValue;

    char symbol = 0;

    do
    {
        pointer++;

        symbol = *pointer;

        switch (state)
        {
        case State::InValue:
            if (symbol == ' ' || symbol == 0x0d)
            {
                float value = (float)SymbolsToInt(firstSymbol, lastSymbol);

                if (forWater)
                {
                    if (value > 0.0f)
                    {
                        array.At(col, row) = -value;
                    }
                }
                else
                {
                    array.At(col, row) = value;
                }

                col++;
                state = State::InSpace;
            }
            else
            {
                lastSymbol++;
            }
            break;

        case State::InSpace:
            if (symbol != ' ')
            {
                firstSymbol = pointer;
                lastSymbol = pointer;
                state = State::InValue;
            }
            break;
        }

    } while (symbol != 0x0d);

    return pointer + 2;
}


void Landscape::FillRowTCell(int row, const Array2D<float> &array, TCell *values)
{
    for (int col = 0; col < array.GetNumberColumns(); col++)
    {
        values->Construct(col, row, array.At(col, row));
        values++;
    }
}


int Landscape::SymbolsToInt(pchar firstSymbol, pchar lastSymbol)
{
    size_t size = (size_t)(lastSymbol - firstSymbol + 2);

    char *buffer = new char[size];

    memcpy(buffer, firstSymbol, size - 1);
    buffer[size - 1] = '\0';

    int value = Text::StringToInteger(buffer);

    SAFE_DELETE_ARRAY(buffer);

    return value;
}


int Landscape::GetSizeX_Columns()
{
    return TCell::NUM_COLS_X;
}


int Landscape::GetSizeY_Rows()
{
    return TCell::NUM_ROWS_Y;
}


float Landscape::GetHeightAccurately(float x, float y, bool forPanelMap)
{
    if (forPanelMap)
    {
        return 10.0f;
    }

    CollisionData data;

    if (GameWorld::self->DetectCollision({x, y, 100.0f}, {x, y, -100.0f}, 0.0f, ~PiKindCollision::Landscape, &data))
    {
        return data.position.z;
    }

    return 0.0f;
}


float Landscape::GetHeightCenter(float x, float y)
{
    int col = (int)x;
    int row = (int)y;
    row = heightMap.GetNumberRows() - row - 1;

    if (col < 0 || col >= heightMap.GetNumberColumns() || row < 0 || row >= heightMap.GetNumberRows())
    {
        return 0.0f;
    }

    return heightMap.At(col, row);
}


float Landscape::GetHeightCenter(const Point3D &point)
{
    return GetHeightCenter(point.x, point.y);
}


LandscapeController::LandscapeController() : Controller(PiTypeController::Landscape)
{
    numThreads = TheEngine->GetProcessorCount();
    if (numThreads > MAX_THREADS)
    {
        numThreads = MAX_THREADS;
    }
    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = nullptr;
    }
}


LandscapeController::~LandscapeController()
{
    for (int i = 0; i < numThreads; i++)
    {
        if(threads[i])
        {
            delete threads[i];
        }
    }
}


void LandscapeController::Preprocess()
{
    Controller::Preprocess();

    for(int i = 0; i < numThreads; i++)
    {
        threads[i] = new Thread(&CreateGeometeryZones, nullptr);
    }
}


void LandscapeController::Move()
{
    if(!GameState::landscapeCreated)
    {
        int added = 0;

        for(int y = 0; y < TZone::NUM_ROWS_Y; y++)
        {
            for(int x = 0; x < TZone::NUM_COLS_X; x++)
            {
                TZone *zone = TZone::Get(x, y);

                if(zone && zone->state == TZone::State::Created)
                {
                    landscape->AddSurfaceToMesh(zone);
                }

                if (zone && zone->state == TZone::State::Added)
                {
                    added++;
                }
            }
        }

        if (added == TZone::NUM_ROWS_Y * TZone::NUM_COLS_X)
        {
            GameState::landscapeCreated = true;
            LOG_WRITE("Landscape is created");

            if (landscape->taskAfter)
            {
                ListPeriodicTask::Self()->Append(landscape->taskAfter, 1, 1);
            }
        }
    }
    else
    {
        static bool first = true;

        if (first)
        {
            first = false;
        }
        else
        {
            landscape->ReloadIfNeed();
        }
    }
}


void LandscapeController::CreateGeometeryZones(const Thread *thread, void *)
{
    for(int y = 0; y < TZone::NUM_ROWS_Y; y++)
    {
        for(int x = 0; x < TZone::NUM_COLS_X; x++)
        {
            landscape->CreateGeometryForZone(TZone::Get(x, y));
        }
    }
}


namespace Pi
{
    namespace Water
    {
        FogSpaceObject *fog_object = nullptr;

        void CreateLake(int x, int y, int width, int height);

        float Level()
        {
            return -0.3f;
        }
    }
}


bool Landscape::UnderWater(int x, int y)
{
    return heightMap.At(x, heightMap.GetNumberRows() - y - 1) < 0.0f;
}


bool Landscape::AboveSurface(int x, int y)
{
    return (x >= 0 && x < heightMap.GetNumberColumns() && y >= 0 && y < heightMap.GetNumberRows());
}


void Water::Create()
{
    CreateLake(7, 66, 88, 31);
    CreateLake(47, 30, 20, 33);

    FogSpace *fog = new FogSpace({(float)Landscape::self->GetSizeX_Columns(), (float)Landscape::self->GetSizeX_Columns()});
    fog_object = fog->GetObject();
    fog_object->SetFogColor({0.0f, 0.0f, 0.0f});
    fog_object->SetFogDensity(0.075f);
    fog_object->SetFogFunction(PiFogFunction::Linear);
    GameWorld::self->GetRootNode()->AppendNewSubnode(fog);
}

void Water::SetFogDensity(float density)
{
    fog_object->SetFogDensity(density);
}

void Water::CreateLake(int col, int row, int width, int height)
{
    int sizeX = width / 4 + 1;
    int sizeY = height / 4 + 1;

    WaterBlock *block = new WaterBlock({sizeX, sizeY}, 4, 1.0f, 2.0f, {0, 10.0f});

    ((WaterController *)block->GetController())->Run();
    ((WaterController *)block->GetController())->SetWaterViscosity(4e-3F);
    ((WaterController *)block->GetController())->SetWaterSpeed(5.0e-3F);

    MaterialObject *material = new MaterialObject();

    material->AddAttribute(new DiffuseAttribute({0.0f, 0.0f, 1.0f}));
    material->AddAttribute(new EmissionAttribute({0.0f, 0.0f, 1.0f}));

    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            WaterGeometry *geometry = new WaterGeometry(block, {x, y});
            geometry->SetMaterialObject(0, material);
            WaterGeometryObject *object = geometry->GetObject();
            object->SetCollisionExclusionMask(PiKindCollision::Water);
            object->EnableGeometryFlags(PiFlagGeometry::RenderEffectPass);
            object->EnableGeometryEffectFlags(PiFlagGeometryEffect::Opaque | PiFlagGeometryEffect::Accumulate);
            object->Build(geometry);
            block->AppendSubnode(geometry);
        }
    }

    block->SetNodePosition({(float)col - 0.5f, (float)row - 0.5f, Level()});

    GameWorld::self->GetRootNode()->AppendNewSubnode(block);

    material->Release();
}


bool Water::DetectHeight(float x, float y, float *height)
{
    CollisionData data;

    //  \todo Не работает. Не детектит воду

    if (GameWorld::self->DetectCollision({x - 0.3f, y, 5.0f}, {x - 0.3f, y, -5.0f}, 0.0f, 0, &data))
    {
        *height = data.position.z;
        return true;
    }

    return false;
}
