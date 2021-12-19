// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Array2D.h"


namespace Pi
{

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

        Landscape(pchar nameFile, float delta = 0.0F);

        void    Reload();
        bool    IsCreated() const { return created; }
        int     GetSizeX_Columns();
        int     GetSizeY_Rows();

        // ����� ������ �������� ������ - ��� ���������� �� ������
        float   GetHeightAccurately(float x_col, float y_row, bool forPanelMap = false);

        // ���������� ������ ��������� � ������ ������, ������� ������������ ���������� x,y - ��� �������� � ����� .lvl
        float   GetHeightCenter(float x_col, float y_row);

        // ���������� true, ���� ����� ����������� ������ �����������
        bool    UnderWater(int x, int y);

    private:

        Array2D<float>  heightMap;
        File            file;

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

        float           delta = 0.0f;
        bool            created = false;
        LandscapeController *controller = nullptr;
    };


    class LandscapeController final : public Controller
    {
        friend class Landscape;

    public:

        LandscapeController();
        ~LandscapeController();

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
}
