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
        const B Landscape = 1 << 17;        // Ладшафт
        const B PathUnit  = 1 << 18;        // Метка пути
    }

    // Преобразует произвольные координаты на ланшафте в соответствующую точку клети ландшафта
    class PointLandscape
    {
    public:
        PointLandscape(const Point3D &point);
        float x;
        float y;
        float z;
    };

    class Landscape : public Node
    {
        friend class LandscapeController;
        friend class DrawTriangle;

    public:

        Landscape(pchar nameFile, float delta = 0.0F);
        virtual ~Landscape();

        bool            IsCreated() const { return created; }
        int             GetSizeX_Columns();
        int             GetSizeY_Rows();
        // Найти точное значение высоты - как нарисовано на экране
        float           GetHeightAccurately(float x_col, float y_row, bool forPanelMap = false);
        // Возвращает высоту ландшафта в центре клетки, которой принадлежать координаты x,y - как записано в файле .lvl
        float           GetHeightCenter(float x_col, float y_row);
        // Возвращет точку ландшафта, находящуюся в экранных координатах x, y
        Point3D         GetPointScreen(float x_col, float y_row, bool &result);
        Array2D<float>  heightMap;

    private:
        static int      AddTriangle(GeometrySurface *surface, const Point3D points[3]);
        static int      AddTriangle(GeometrySurface *surface, const Point3D &point0, const Point3D &point1, const Point3D &point2);
        static Point3D  NewPoint(int x, int y, int num, int dX, int dY);
        void            FillMap(pchar nameFile);
        int             GetNumLines(char *buffer, int size);
        int             GetNumElementInLine(char *buffer);
        char *ParseLineText(char *const text, TCell *values);
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

        // Создание зоны ландшафта
        void            CreateGeometryForField(TZone *field);

        // Добавление зоны лондшафта в общую геометрию
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

        // Эта функция будет вызывться несколькими потоками для создания отдельных зон ландшафта
        static void TheAdditionsOfSurfaces(const Thread *thread, void *cookie);
    };

}
