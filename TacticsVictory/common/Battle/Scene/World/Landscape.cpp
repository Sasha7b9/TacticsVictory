// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Scene/World/Landscape.h"
#include "Utils/Log.h"
#include "Scene/World/GameWorld.h"
#include "Graphics/CanvasTexture.h"


namespace Pi
{

class TCell;
class TField;
class Landscape;


static TCell    *mapCell = nullptr;
static TField   *mapField = nullptr;
static Landscape *landscape = nullptr;


class TCell : public ListElement <TCell>
{

public:

    static int NUM_ROWS_Y;          // Количество клеток по Y
    static int NUM_COLS_X;          // Количество клеток по X

    TCell() {};

    void Construct(int x, int y, float _height)
    {
        coord = Integer2D(x, y);
        height = _height;
    }

    ~TCell() {};

    Integer2D   coord;
    float       height = 1.0F;
    TField *   field = nullptr;

};

TCell *GGetCell(int x, int y)
{
    if(x >= 0 && x < TCell::NUM_COLS_X && y >= 0 && y < TCell::NUM_ROWS_Y)
    {
        return  &(mapCell[(size_t)x + (size_t)y * (size_t)TCell::NUM_COLS_X]);
    }

    static TCell cell;

    return &cell;
}


// Этот класс представляет собой прямоугольник, заполняемый потоком
class TField
{

public:

    static int NUM_ROWS_Y;      // Количество зон, на которые бъётся ландшафт, по оси Y
    static int NUM_COLS_X;

    static const int SIZE_SIDE = 64;
    static const int SIZE_IN_CELLS = SIZE_SIDE * SIZE_SIDE;

    TField() = default;

    void Construct(int col, int row)
    {
        coord = Integer2D(col, row);

        int xFirst = col * SIZE_SIDE;
        int yFirst = row * SIZE_SIDE;
        int xLast = MaxZero(TCell::NUM_COLS_X);
        int yLast = (row + 1) * SIZE_SIDE;

        if(yLast > TCell::NUM_ROWS_Y)
        {
            yLast = TCell::NUM_ROWS_Y;
        }
 
       for(int y = yFirst; y < yLast; y++)
        {
            for(int x = xFirst; x < xLast; x++)
            {
                TCell *cell = GGetCell(x, y);
                if(cell)
                {
                    cell->field = this;
                    cells.Append(cell);
                }
            }
        }
    };

    TCell *GetCell(int numCell)
    {
        if(numCell >= cells.GetElementCount())
        {
            return nullptr;
        }

        TCell *cell = cells.First();

        for(int i = 0; i < numCell; i++)
        {
            cell = cell->Next();
        }

        return cell;
    }
    Integer2D       coord {0, 0};
    List<TCell>    cells;

    enum class State
    {
        Empty,      
        Created,    // Surface create but not added to mesh
        Added       // Surface create and added to mesh. Complete
    } state = State::Empty;

    GenericGeometry *geometry = nullptr;
    Mutex mutexCreating;
};

TField *GetField(int x, int y)
{
    if(x >= 0 && x < TField::NUM_COLS_X && y >= 0 && y < TField::NUM_ROWS_Y)
    {
        return &(mapField[(size_t)x + (size_t)y * (size_t)TField::NUM_COLS_X]);
    }

    static TField empty;

    return &empty;
}

int TField::NUM_ROWS_Y = 0;
int TField::NUM_COLS_X = 0;

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

static ControllerReg<LandscapeController> *TheControllerReg = nullptr;

}


using namespace Pi;



Landscape::Landscape(pchar nameFile, float delta) : Node()
{
    this->delta = delta;
    landscape = this;

    FillMap(nameFile);

    TheControllerReg = new ControllerReg<LandscapeController>(PiTypeController::Landscape, "Landscape");
    controller = new LandscapeController();
    SetController(controller);
    controller->Wake();
    SetNodePosition({0, (float)GetSizeY_Rows(), 0});
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
    SAFE_DELETE(TheControllerReg);

    SAFE_DELETE_ARRAY(mapCell);
    SAFE_DELETE_ARRAY(mapField);
    SAFE_DELETE_ARRAY(mapField);
}


void Landscape::CreateGeometryForField(TField *field)
{
    if(!field->mutexCreating.TryAcquire())
    {
        return;
    }

    if(field->state == TField::State::Empty)
    {
        GeometrySurface *surface = new GeometrySurface();

        for(int i = 0; i < TField::SIZE_IN_CELLS; i++)
        {
            TCell *cell = field->GetCell(i);
            if(cell)
            {
                AddFace(surface, cell->coord.x, cell->coord.y);
            }
        }

        surface->texcoordCount = 1;
        surface->surfaceFlags = PiFlagSurface::ValidNormals;

        List<GeometrySurface> *surfaceList = new List<GeometrySurface>();
        surfaceList->Append(surface);
        const List<GeometrySurface> *surfaceTable = surfaceList;

        MaterialObject *material = new MaterialObject();

        CanvasTexture *canvas = new CanvasTexture();

        DiffuseTextureAttribute *diffTexture = new DiffuseTextureAttribute(canvas->GetTexture());
        material->AddAttribute(diffTexture);

        Array<MaterialObject*> materialArray;
        materialArray.AddElement(material);

        field->geometry = new GenericGeometry(1, &surfaceTable, materialArray);

        material->Release();

        canvas->SetColorBrush({0.0f, 0.0f, 0.3f});
        canvas->FillRegion(5, 5, 10, 10);
        canvas->EndPaint();

        delete surfaceList;

        field->state = TField::State::Created;
    }

    field->mutexCreating.Release();
}


void Landscape::AddSurfaceToMesh(TField *field)
{
    if(field->state == TField::State::Empty || field->state == TField::State::Added)
    {
        return;
    }

    AppendNewSubnode(field->geometry);
    field->geometry->GetObject()->SetCollisionExclusionMask(PiKindCollision::Landscape);

    field->state = TField::State::Added;
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
        TCell *cell = GGetCell(x, y);
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
    TCell *cell = GGetCell(x, y);
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

    const float k = 32.0f;

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


void Landscape::FillMap(pchar nameFile)
{
    FillTables();

    File file;
    
    if(file.Open(nameFile) != EngineResult::Okay)
    {
        LOG_ERROR("Can't open file %s", nameFile);
        return;
    }
    

    uint64 size = file.GetSize();

    char *buffer = new char[size];
    file.Read(buffer, (uint)size);

    file.Close();

    TCell::NUM_ROWS_Y = GetNumLines(buffer, (int)size);
    TCell::NUM_COLS_X = GetNumElementInLine(buffer);

    heightMap.SetDimensions(TCell::NUM_COLS_X, TCell::NUM_ROWS_Y);

    TField::NUM_ROWS_Y = TCell::NUM_ROWS_Y / TField::SIZE_SIDE + ((TCell::NUM_ROWS_Y % TField::SIZE_SIDE == 0) ? 0 : 1);
    TField::NUM_COLS_X = TCell::NUM_COLS_X / TField::SIZE_SIDE + ((TCell::NUM_COLS_X % TField::SIZE_SIDE == 0) ? 0 : 1);

    mapCell = new TCell[(size_t)TCell::NUM_ROWS_Y * (size_t)TCell::NUM_COLS_X];
    mapField = new TField[(size_t)TField::NUM_ROWS_Y * (size_t)TField::NUM_COLS_X];

    char *pointer = buffer;

    for(int i = 0; i < TCell::NUM_ROWS_Y; i++)
    {
        pointer = ParseLineText(pointer, mapCell + i * TCell::NUM_COLS_X);
    }

    for(int row = 0; row < TField::NUM_ROWS_Y; row++)
    {
        for(int col = 0; col < TField::NUM_COLS_X; col++)
        {
            TField *field = GetField(col, row);
            if (field)
            {
                field->Construct(col, row);
            }
        }
    }

    SAFE_DELETE_ARRAY(buffer);
}

int Landscape::GetNumLines(char *buffer, int size)
{
    int numLines = 0;

    char *end_buffer = buffer + (size_t)size;

    while(buffer < end_buffer)
    {
        if(*buffer == 0x0d)
        {
            numLines++; //-V127
        }
        buffer++;
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


char *Landscape::ParseLineText(char * const text, TCell *values)
{
    char *pointer = text;
    size_t numValue = 0;

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

    do {
        pointer++;

        symbol = *pointer;

        switch(state)
        {
            case State::InValue:
                if(symbol == ' ' || symbol == 0x0d)
                {
                    int numCell = (int)(values + numValue - mapCell);
                    int y = numCell / TCell::NUM_COLS_X;
                    int x = (numCell - y * TCell::NUM_COLS_X) % TCell::NUM_COLS_X;

                    values[numValue].Construct(x, y, (float)SymbolsToInt(firstSymbol, lastSymbol));
                    heightMap.At(x, TCell::NUM_ROWS_Y - y - 1) = values[numValue].height;                   // Отражаем y, потому что после загрузки ландшафт смещается по Y
                    state = State::InSpace;
                    numValue++;
                }
                else
                {
                    lastSymbol++;
                }
                break;

            case State::InSpace:
                if(symbol != ' ')
                {
                    firstSymbol = pointer;
                    lastSymbol = pointer;
                    state = State::InValue;
                }
                break;
        }

    } while(symbol != 0x0d);

    return pointer + 2;
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

    if (GameWorld::Get()->DetectCollision({x, y, 100.0f}, {x, y, -100.0f}, 0.0f, ~PiKindCollision::Landscape, &data))
    {
        return data.position.z;
    }

    return 0.0f;
}


float Landscape::GetHeightCenter(float x, float y)
{
    return heightMap.At((int)x, (int)y);
}


Point3D Landscape::GetPointScreen(float x, float y, bool &result)
{
    result = false;

    Ray ray = CameraRTS::self->GetWorldRayFromPoint({x, y});

    CollisionData data;

    Point3D p1 = ray.origin;
    Point3D p2 = p1 + ray.direction * ray.tmax;

    // Сначала определяем столкновение первой попавшейся геометрией
    if (GameWorld::Get()->DetectCollision(p1, p2, 0.0f, PiKindCollision::PathUnit, &data))
    {
        GeometryObject *object = data.geometry->GetObject();

        if (object->GetCollisionExclusionMask() == PiKindCollision::Landscape)
        {
            result = true;
            return data.position;
        }
    }

    return Point3D::ZERO;
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
    for(int i = 0; i < numThreads; i++)
    {
        SAFE_DELETE(threads[i]);
    }
}


void LandscapeController::Preprocess()
{
    Controller::Preprocess();

    for(int i = 0; i < numThreads; i++)
    {
        threads[i] = new Thread(&TheAdditionsOfSurfaces, nullptr);
    }
}


void LandscapeController::Move()
{
    Controller::Move();

    if(!landscape->created)
    {
        int added = 0;

        for(int y = 0; y < TField::NUM_ROWS_Y; y++)
        {
            for(int x = 0; x < TField::NUM_COLS_X; x++)
            {
                TField *field = GetField(x, y);

                if(field && field->state == TField::State::Created)
                {
                    landscape->AddSurfaceToMesh(field);
                }

                if (field && field->state == TField::State::Added)
                {
                    added++;
                }
            }
        }

        if (added == TField::NUM_ROWS_Y * TField::NUM_COLS_X)
        {
            landscape->created = true;
        }
    }
}


void LandscapeController::TheAdditionsOfSurfaces(const Thread * /*thread*/, void * /*cookie*/)
{
    for(int y = 0; y < TField::NUM_ROWS_Y; y++)
    {
        for(int x = 0; x < TField::NUM_COLS_X; x++)
        {
            landscape->CreateGeometryForField(GetField(x, y));
        }
    }
}
