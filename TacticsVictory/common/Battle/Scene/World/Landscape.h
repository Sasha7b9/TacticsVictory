#pragma once


namespace Pi
{

    class LandscapeController;
    class CellTV;
    class FieldTV;
    
    namespace PiTypeController
    {
        const S Landscape = 'land';
    }

    namespace PiKindCollision
    {
        const B Landscape = 1 << 17;
        const B PathUnit  = 1 << 18;
    }
    
    class Landscape : public Node
    {
        friend class LandscapeController;
        friend class DrawTriangle;
    
    public:
    
        Landscape(pchar nameFile, float delta = 0.0F);
        virtual ~Landscape();

        bool            IsCreated() const { return created; }
        int             GetSizeX();
        int             GetSizeY();
        float           GetHeight(float x, float y, bool forPanelMap = false);

        // Возвращает высоту ландшафта в центре клетки, которой принадлежать координаты x,y
        float           GetHeightCenter(float x, float y);

        // Возвращет точку ландшафта, находящуюся в экранных координатах x, y
        Point3D         GetPointScreen(float x, float y, bool &result);

    private:
        static int      AddTriangle(GeometrySurface *surface, const Point3D points[3]);
        static int      AddTriangle(GeometrySurface *surface, const Point3D& point0, const Point3D& point1, const Point3D& point2);
        static Point3D  NewPoint(int x, int y, int num, int dX, int dY);
        void            FillMap(pchar nameFile);
        int             GetNumLines(char *buffer, int size);
        int             GetNumElementInLine(char *buffer);
        char            *ParseLineText(char *text, CellTV *values);
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
        int             AddPlane(GeometrySurface *surface, const Point3D& point0, const Point3D& point1, const Point3D& point2, const Point3D& point3);
        Vector2D        CalculateSizePlane(const Point3D ponts[4]);
        void            CreateGeometryForField(FieldTV *field);
        void            AddSurfaceToMesh(FieldTV *field);
    
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
    
        void Preprocess() override;
        void Move() override;
    
    private:

        int numThreads = 4;
        static const int MAX_THREADS = 32;
        Thread *threads[MAX_THREADS];
        
        static void TheAdditionsOfSurfaces(const Thread *thread, void *cookie);
    };

}
