// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Array2D_.h"


namespace Pi
{
    class PeriodicTask;
    class LandscapeController;
    class TCell;
    class TZone;

    namespace PiTypeController
    {
        const S Landscape = 'land';
    }

    namespace PiKindCollision
    {
        const B Landscape = 1 << 17;        // �������
        const B PathUnit  = 1 << 18;        // ����� ����
        const B Water     = 1 << 19;        // ����
        const B Unit      = 1 << 20;
    }

    class Landscape : public Node
    {
        friend class LandscapeController;
        friend class DrawTriangle;

    public:

        // ���� ������ afterTask, �� ��� ����� ��������� �� ���������� ��������
        Landscape(pchar nameFile, PeriodicTask *afterTask = nullptr, float delta = 0.1F);

        static Landscape *self;

        void    Reload();
        int     GetSizeX_Columns();
        int     GetSizeY_Rows();

        // ����� ������ �������� ������ - ��� ���������� �� ������
        float   GetHeightAccurately(float x_col, float y_row, bool forPanelMap = false);

        // ���������� ������ ��������� � ������ ������, ������� ������������ ���������� x,y - ��� �������� � ����� .lvl
        float   GetHeightCenter(float x_col, float y_row);
        float   GetHeightCenter(const Point3D &point);

        // ���������� true, ���� ����� ����������� ������ �����������
        bool    UnderWater(int x, int y);

        // ��������� true, ���� ���� ����� ��������� ��� ������������
        bool    AboveSurface(int x, int y);

        // ���������� ��� ������������ ���������
        String<> GetNameFile() { return file.GetFileName(); }

    private:

        Array2D<float>  heightMap;
        File            file;
        PeriodicTask   *taskAfter = nullptr;            // ��� ������ ����� ��������� ����� �������� ��������

        virtual ~Landscape();

        Array2D<float>  ReadFile(pchar nameFile);
        // ��������� ����� ���������, ����������� � �������� ����������� x, y
        Point3D         GetPointScreen(float x_col, float y_row, bool &result);
        static int      AddTriangle(GeometrySurface *surface, const Point3D points[3]);
        static int      AddTriangle(GeometrySurface *surface, const Point3D &point0, const Point3D &point1, const Point3D &point2);
        static Point3D  NewPoint(int x, int y, int num, int dX, int dY);
        void            FillMap(const Array2D<float> &array);
        // ���������� ���������� ����� � �����
        int             GetRowsInMap(char *buffer, int size);
        int             GetNumElementInLine(char *buffer);

        // ������� ������ *TCell �� ������ �������
        void            FillRowTCell(int row, const Array2D<float> &array, TCell *values);

        // ���������� ������ ���������� ����� � ������
        char           *ParseRowLandscape(bool forWater, char * const text, int row, Array2D<float> &array);

        int             SymbolsToInt(pchar firstSymbol, pchar lastSymbol);
        int             AddFace(GeometrySurface *surface, int x, int y);
        static Point3D  CoordVertex(int numVert, int x, int y);
        static float    CellZ(int x, int y);
        void            FillTables();
        static int      DeltaZ(int thisX, int thisY, int x, int y);
        int             AddPlane(GeometrySurface *surface, const Point3D points[4]);  // 0-----1
                                                                                      // |     |
                                                                                      // |     |
                                                                                      // 3-----2
        int             AddPlane(GeometrySurface *surface, const Point3D &point0, const Point3D &point1, const Point3D &point2, const Point3D &point3);
        Vector2D        CalculateSizePlane(const Point3D ponts[4]);

        // �������� ���� ���������
        void            CreateGeometryForZone(TZone *field);

        // ���������� ���� ��������� � ����� ���������
        void            AddSurfaceToMesh(TZone *field);

        // ������������� ��������, ���� ����������
        void            ReloadIfNeed();

        float           delta = 0.0f;
//        bool            created = false;
        LandscapeController *controller = nullptr;
    };


    class LandscapeController final : public Controller
    {
        friend class Landscape;

    public:

        LandscapeController();
        virtual ~LandscapeController();

        virtual void Preprocess() override;
        virtual void Move() override;

    private:

        int numThreads = 4;
        static const int MAX_THREADS = 32;
        Thread *threads[MAX_THREADS];

        // ��� ������� ����� ��������� ����������� �������� ��� �������� ��������� ��� ���������
        static void CreateGeometeryZones(const Thread *thread, void *cookie);
    };

    namespace Water
    {
        void Create();

        float Level();

        // ���������� ����������� � �����
        bool DetectHeight(float x, float y, float *height);

        void SetFogDensity(float density);
    }

    extern TCell *mapCell;
    extern TZone *mapZone;


    class TCell : public ListElement <TCell>
    {

    public:

        static int NUM_ROWS_Y;          // ���������� ������ �� Y
        static int NUM_COLS_X;          // ���������� ������ �� X

        TCell()
        {
        };

        ~TCell()
        {
        };

        static TCell *Get(int x, int y)
        {
            if (x >= 0 && x < TCell::NUM_COLS_X && y >= 0 && y < TCell::NUM_ROWS_Y)
            {
                return  &(mapCell[(size_t)x + (size_t)y * (size_t)TCell::NUM_COLS_X]);
            }

            static TCell cell;

            return &cell;
        }

        void Construct(int x, int y, float _height)
        {
            coord = Integer2D(x, y);
            height = _height;
        }

        Integer2D coord;
        float     height = 1.0F;
        TZone *zone = nullptr;
    };


    // ���� ����� ������������ ����� ���� ���������, ����������� ������� �� ���
    class TZone
    {

    public:

        static int NUM_ROWS_Y;      // ���������� ���, �� ������� ������ ��������, �� ��� Y
        static int NUM_COLS_X;

        static const int SIZE_SIDE = 50;
        static const int SIZE_IN_CELLS = SIZE_SIDE * SIZE_SIDE;

        TZone() = default;

        void Construct(int col, int row)
        {
            cells.RemoveAll();

            coord = Integer2D(col, row);

            int xFirst = col * SIZE_SIDE;
            int yFirst = row * SIZE_SIDE;
            int xLast = MaxZero(TCell::NUM_COLS_X);
            int yLast = (row + 1) * SIZE_SIDE;

            if (yLast > TCell::NUM_ROWS_Y)
            {
                yLast = TCell::NUM_ROWS_Y;
            }

            for (int y = yFirst; y < yLast; y++)
            {
                for (int x = xFirst; x < xLast; x++)
                {
                    TCell *cell = TCell::Get(x, y);
                    if (cell)
                    {
                        cell->zone = this;
                        cells.Append(cell);
                    }
                }
            }
        };

        TCell *GetCell(int numCell)
        {
            if (numCell >= cells.GetElementCount())
            {
                return nullptr;
            }

            TCell *cell = cells.First();

            for (int i = 0; i < numCell; i++)
            {
                cell = cell->Next();
            }

            return cell;
        }

        static TZone *Get(int x, int y)
        {
            if (x >= 0 && x < TZone::NUM_COLS_X && y >= 0 && y < TZone::NUM_ROWS_Y)
            {
                return &(mapZone[(size_t)x + (size_t)y * (size_t)TZone::NUM_COLS_X]);
            }

            static TZone empty;

            return &empty;
        }

        enum class State
        {
            Empty,
            Created,        // Surface create but not added to mesh
            Added,          // Surface create and added to mesh. Complete
            NeedReload      // ���� ��������� � ����������� (������, ��-�� ����, ��� ���� � ������ ����� ���������)
        };


        State            state = State::Empty;
        Integer2D        coord{0, 0};
        List<TCell>      cells;
        GenericGeometry *geometry = nullptr;
        Mutex            mutexCreating;
    };
}
