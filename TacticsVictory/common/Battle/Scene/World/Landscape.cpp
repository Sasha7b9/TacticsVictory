#include <stdafx.h>
#include "Scene/World/Landscape.h"
#include "Utils/Log.h"
#include "Scene/World/GameWorld.h"


namespace Pi
{

class CellTV;
class FieldTV;
class Landscape;


static CellTV    *mapCell = nullptr;
static FieldTV   *mapField = nullptr;
static Landscape *landscape = nullptr;


#include "Landscape.h"
#include "Utils/Log.h"


class CellTV : public ListElement <CellTV>
{

public:

    static int NUM_ROWS;
    static int NUM_COLS;

    CellTV() {};

    void Construct(int x, int y, float _height)
    {
        coord = Integer2D(x, y);
        height = _height;
    }

    ~CellTV() {};

    Integer2D   coord;
    float       height = 1.0F;
    FieldTV *   field = nullptr;

};

CellTV *GGetCell(int x, int y)
{
    if(x >= 0 && x < CellTV::NUM_COLS && y >= 0 && y < CellTV::NUM_ROWS)
    {
        return  &(mapCell[(size_t)x + (size_t)y * (size_t)CellTV::NUM_COLS]);
    }

    static CellTV cell;

    return &cell;
}


// Этот класс представляет собой прямоугольник, заполняемый потоком
class FieldTV
{

public:

    static int NUM_ROWS;
    static int NUM_COLS;

    static const int SIZE_SIDE = 64;
    static const int SIZE_IN_CELLS = SIZE_SIDE * SIZE_SIDE;

    FieldTV() {};

    void Construct(int col, int row)
    {
        coord = Integer2D(col, row);

        int xFirst = col * SIZE_SIDE;
        int yFirst = row * SIZE_SIDE;
        int xLast = MaxZero(CellTV::NUM_COLS);
        int yLast = (row + 1) * SIZE_SIDE;

        if(yLast > CellTV::NUM_ROWS)
        {
            yLast = CellTV::NUM_ROWS;
        }
 
       for(int y = yFirst; y < yLast; y++)
        {
            for(int x = xFirst; x < xLast; x++)
            {
                CellTV *cell = GGetCell(x, y);
                if(cell)
                {
                    cell->field = this;
                    cells.Append(cell);
                }
            }
        }
    };

    CellTV *GetCell(int numCell)
    {
        if(numCell >= cells.GetElementCount())
        {
            return nullptr;
        }

        CellTV *cell = cells.First();

        for(int i = 0; i < numCell; i++)
        {
            cell = cell->Next();
        }

        return cell;
    }
    Integer2D       coord {0, 0};
    List<CellTV>    cells;

    enum class State
    {
        Empty,      
        Created,    // Surface create but not added to mesh
        Added       // Surface create and added to mesh. Complete
    } state = State::Empty;

    GenericGeometry *geometry = nullptr;
    Mutex mutexCreating;
};

FieldTV *GetField(int x, int y)
{
    if(x >= 0 && x < FieldTV::NUM_COLS && y >= 0 && y < FieldTV::NUM_ROWS)
    {
        return &(mapField[(size_t)x + (size_t)y * (size_t)FieldTV::NUM_COLS]);
    }

    static FieldTV empty;

    return &empty;
}

int FieldTV::NUM_ROWS = 0;
int FieldTV::NUM_COLS = 0;

int CellTV::NUM_ROWS = 0;
int CellTV::NUM_COLS = 0;

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



Landscape::Landscape(pchar nameFile, float delta) :
    Node()
{
//    FUNC_ENTER

    this->delta = delta;
    landscape = this;

    FillMap(nameFile);

    TheControllerReg = new ControllerReg<LandscapeController>(PiTypeController::Landscape, "Landscape");
    controller = new LandscapeController();
    SetController(controller);
    controller->Wake();
    SetNodePosition({0, (float)GetSizeY(), 0});

//    FUNC_LEAVE
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
//    SAFE_DELETE_ARRAY(mapField);
}


void Landscape::CreateGeometryForField(FieldTV *field)
{
    if(!field->mutexCreating.TryAcquire())
    {
        return;
    }

    if(field->state == FieldTV::State::Empty)
    {
        GeometrySurface *surface = new GeometrySurface();

        for(int i = 0; i < FieldTV::SIZE_IN_CELLS; i++)
        {
            CellTV *cell = field->GetCell(i);
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
        DiffuseTextureAttribute *diffTexture = new DiffuseTextureAttribute("MapCell");
        material->AddAttribute(diffTexture);
        //DiffuseAttribute *diffAttrib = new DiffuseAttribute(ColorRGBA(0.6f, 0.6f, 0.6f));
        //material->AddAttribute(diffAttrib);
        SpecularTextureAttribute *specTexture = new SpecularTextureAttribute("MapCell");
        material->AddAttribute(specTexture);
        //SpecularAttribute *specAttrib = new SpecularAttribute(ColorRGBA(1.0f, 1.0f, 1.0f), 1.0f);
        //material->AddAttribute(specAttrib);
        //ReflectionAttribute *reflection = new ReflectionAttribute(ColorRGBA(1.0f, 0.0f, 0.0f), 1.0f, 1.0f);
        //material->AddAttribute(reflection);

        Array<MaterialObject*> materialArray;
        materialArray.AddElement(material);

        field->geometry = new GenericGeometry(1, &surfaceTable, materialArray);

        material->Release();

        delete surfaceList;

        field->state = FieldTV::State::Created;
    }

    field->mutexCreating.Release();
}


void Landscape::AddSurfaceToMesh(FieldTV *field)
{
    if(field->state == FieldTV::State::Empty || field->state == FieldTV::State::Added)
    {
        return;
    }

    AppendNewSubnode(field->geometry);
    field->geometry->GetObject()->SetCollisionExclusionMask(PiKindCollision::Landscape);

    field->state = FieldTV::State::Added;
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

    if(x >= 0 && x < CellTV::NUM_COLS && y >= 0 && y < CellTV::NUM_ROWS)
    {
        CellTV *cell = GGetCell(x, y);
        if (cell)
        {
            Z = cell->height;
        }
    }

    switch(numVert)
    {
        case 0:
        {
            if((y < 0 || x < 0) || (x > CellTV::NUM_COLS - 1) || (y > CellTV::NUM_ROWS - 1))
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
            if((y < 0 || x > CellTV::NUM_COLS - 1) || (x < 0) || (y > CellTV::NUM_ROWS - 1))
            {
                return Point3D(1.0f, 0.0f, 0.0f);
            }
            if((y == 0) || (x == CellTV::NUM_COLS - 1))
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
            if(y == CellTV::NUM_ROWS - 1 || x == CellTV::NUM_COLS - 1)
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
            if((y < 0) || (x > CellTV::NUM_COLS - 1))
            {
                return Point3D(0.0f, -1.0f, 0.0f);
            }
            if(x == 0 || y == CellTV::NUM_ROWS - 1)
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
    CellTV *cell = GGetCell(x, y);
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

    Point2D texCoord[] = {
        Point2D(0.0f, 0.0f),
        Point2D(0.0f, 1.0f * size.y),
        Point2D(1.0f * size.x, 0.0f),
        Point2D(1.0f * size.x, 0.0f),
        Point2D(0.0f, 1.0f * size.y),
        Point2D(1.0f * size.x, 1.0f * size.y)
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

    GeometryPolygon *polygon = new GeometryPolygon();

    for (int i = 0; i < 3; i++)
    {
        GeometryVertex *vertex = new GeometryVertex();
        vertex->position = positons[i];
        vertex->normal = normals[i];
        vertex->texcoord[0] = texCoord[i];
        polygon->vertexList.Append(vertex);
    }

    surface->polygonList.Append(polygon);

    polygon = new GeometryPolygon();

    for (int i = 3; i < 6; i++)
    {
        GeometryVertex *vertex = new GeometryVertex();
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

    if(x == CellTV::NUM_COLS - 1)
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

    if(y == CellTV::NUM_ROWS - 1)
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

    if(x > 0 && y < CellTV::NUM_ROWS - 1)
    {
        DrawTriangle *triangle = triangleLeftBottom.Find(DrawTriangle::Key(DeltaZ(x, y, x - 1, y), DeltaZ(x, y, x - 1, y + 1), DeltaZ(x, y, x, y + 1)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    if(x < CellTV::NUM_COLS - 1 && y < CellTV::NUM_ROWS - 1)
    {
        DrawTriangle *triangle = triangleRightBottom.Find(DrawTriangle::Key(DeltaZ(x, y, x + 1, y), DeltaZ(x, y, x + 1, y + 1), DeltaZ(x, y, x, y + 1)));
        if(triangle)
        {
            numVertices += triangle->Draw(surface, x, y);
        }
    }

    if(x < CellTV::NUM_COLS - 1 && y > 0)
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

    /*
    Cell::NUM_ROWS = 50;
    Cell::NUM_COLS = 100;

    Field::NUM_ROWS = Cell::NUM_ROWS / Field::SIZE_SIDE + ((Cell::NUM_ROWS % Field::SIZE_SIDE == 0) ? 0 : 1);
    Field::NUM_COLS = Cell::NUM_COLS / Field::SIZE_SIDE + ((Cell::NUM_COLS % Field::SIZE_SIDE == 0) ? 0 : 1);

    mapCell = new Cell[(size_t)(Cell::NUM_ROWS * Cell::NUM_COLS)];
    mapField = new Field[(size_t)(Field::NUM_ROWS * Field::NUM_COLS)];

    for(int y = 0; y < Cell::NUM_ROWS; y++)
    {
        for(int x = 0; x < Cell::NUM_COLS; x++)
        {
            //mapCell[x + y * Cell::NUM_COLS].Construct(x, y, 5.0f);
            GetCell(x, y)->Construct(x, y, (float)Random(10));
        }
    }

    for(int row = 0; row < Field::NUM_ROWS; row++)
    {
        for(int col = 0; col < Field::NUM_COLS; col++)
        {
            mapField[col + row * Field::NUM_COLS].Construct(col, row);
        }
    }

    return;
    */
    
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

    CellTV::NUM_ROWS = GetNumLines(buffer, (int)size);
    CellTV::NUM_COLS = GetNumElementInLine(buffer);

    FieldTV::NUM_ROWS = CellTV::NUM_ROWS / FieldTV::SIZE_SIDE + ((CellTV::NUM_ROWS % FieldTV::SIZE_SIDE == 0) ? 0 : 1);
    FieldTV::NUM_COLS = CellTV::NUM_COLS / FieldTV::SIZE_SIDE + ((CellTV::NUM_COLS % FieldTV::SIZE_SIDE == 0) ? 0 : 1);

    mapCell = new CellTV[(size_t)CellTV::NUM_ROWS * (size_t)CellTV::NUM_COLS];
    mapField = new FieldTV[(size_t)FieldTV::NUM_ROWS * (size_t)FieldTV::NUM_COLS];

    char *pointer = buffer;

    for(int i = 0; i < CellTV::NUM_ROWS; i++)
    {
        pointer = ParseLineText(pointer, mapCell + i * CellTV::NUM_COLS);
    }

    for(int row = 0; row < FieldTV::NUM_ROWS; row++)
    {
        for(int col = 0; col < FieldTV::NUM_COLS; col++)
        {
            FieldTV *field = GetField(col, row);
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

    char *end = buffer + (size_t)size;

    while(buffer < end)
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


char *Landscape::ParseLineText(char *text, CellTV *values)
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
                    int y = numCell / CellTV::NUM_COLS;
                    int x = (numCell - y * CellTV::NUM_COLS) % CellTV::NUM_COLS;

                    values[numValue].Construct(x, y, (float)SymbolsToInt(firstSymbol, lastSymbol));
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


int Landscape::GetSizeX()
{
    return CellTV::NUM_COLS;
}


int Landscape::GetSizeY()
{
    return CellTV::NUM_ROWS;
}


float Landscape::GetHeight(float x, float y, bool forPanelMap)
{
    if (forPanelMap)
    {
        return 10.0f;
    }

    CollisionData data;

    if (GameWorld::Get()->DetectCollision({x, y, 100.0f}, {x, y, -100.0f}, 0.0f, PiKindCollision::Landscape, &data))
    {
        return data.position.z;
    }

    return 0.0f;
}


float Landscape::GetHeightCenter(float x, float y)
{
    return GetHeight((float)(int)x, (float)(int)y);
}


Point3D Landscape::GetPointScreen(float x, float y, bool &result)
{
    result = false;

    Ray ray = TheCamera->GetWorldRayFromPoint({x, y});

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

        for(int y = 0; y < FieldTV::NUM_ROWS; y++)
        {
            for(int x = 0; x < FieldTV::NUM_COLS; x++)
            {
                FieldTV *field = GetField(x, y);

                if(field && field->state == FieldTV::State::Created)
                {
                    landscape->AddSurfaceToMesh(field);
                }

                if (field->state == FieldTV::State::Added)
                {
                    added++;
                }
            }
        }

        if (added == FieldTV::NUM_ROWS * FieldTV::NUM_COLS)
        {
            landscape->created = true;
        }
    }
}


void LandscapeController::TheAdditionsOfSurfaces(const Thread * /*thread*/, void * /*cookie*/)
{
    for(int y = 0; y < FieldTV::NUM_ROWS; y++)
    {
        for(int x = 0; x < FieldTV::NUM_COLS; x++)
        {
            landscape->CreateGeometryForField(GetField(x, y));
        }
    }
}
