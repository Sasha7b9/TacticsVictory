#pragma once


class TerrainSegment : public Object
{
    URHO3D_OBJECT(TerrainSegment, Object);

public:
    // NOTE row == 0 and col == 0 arrent added to terrain. From them information for creation of the left and top sides undertakes
    TerrainSegment(Vector<Vector<float>> &map, const Vector3 &shift = Vector3::ZERO);
    ~TerrainSegment();

    // If function return isClosingTriangleOut == true, return distance for inactive triangle
    float GetIntersectionPlane(Ray &ray, Plane &plane, bool &isClosingTriangleOut);
    Plane GetPlane(uint row, uint col);
    void Rebuild(Vector<Vector<float>> &map_);
    void Clear();
    void SetVisible(bool visible);

private:
    enum Direction
    {
        DIR_UP,
        DIR_RIGHT,
        DIR_DOWN,
        DIR_LEFT
    };

    void PrepareHashMaps();
    void Create(uint numPlanes, float *coords);     // size coords = numPlanes * 4 * 3
    void AddPlaneWithSubplanes(uint row, uint col); // ƒобавл€ет в vertexes и indexes вершины и индексы плоскости (row, col) и
                                                    // плоскостей, которые соедин€ют эту плоскость с (row, col - 1) и (row - 1, col) (лева€ и верхн€€)
    void AddSidePlane(uint row, uint col, Direction dir);
    void AddLeftPlane(uint row, uint col);
    void AddUpPlane(uint row, uint col);
    float HeightCell(uint row, uint col);
    Vector3 CoordCorner(uint row, uint col, Corner corner);
    void PushCoord(const Vector3& coord);
    void PushNormal(const Vector3& normal);
    void PushTexCoord(float x, float y);
    void Add2Plane(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);
    void AddPlane(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3, float dTex);
    void AddTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, float dTex);
    void AddTopLeftCornerPlanes(uint row, uint col);
    void CalculateBoundingBox();
    float GetIntersectionPlane(Ray &ray, Plane &plane);
    float GetIntersectionClosingTriangle(Ray &ray, Triangle &triangle);

    Vector<Vector<float>> map;
    Vector<float> vertexes;         // «десь будем подготавливать вершины дл€ буфера
    Vector<uint> indexes;           // «десь будем подготавливать индексы дл€ буфера
    uint widthMap = 0;
    uint heightMap = 0;

    float *bufVert = nullptr;
    uint numVert = 0;

    uint *bufInd = nullptr;
    uint numInd = 0;

    Vector<uint> bufIndPlanes;          // Buffer for indexes of the edited planes
    BoundingBox boundingBox;

    Vector<uint> bufIndClosingTriangles; // The buffer for triangles which can't be chosen

    Vector3 shift;

    SharedPtr<VertexBuffer> vb;
    SharedPtr<IndexBuffer> ib;
    SharedPtr<Geometry> geometry;
    SharedPtr<Model> model;
    Vector<SharedPtr<VertexBuffer>> vbVector;
    Vector<SharedPtr<IndexBuffer>> ibVector;
    PODVector<unsigned> morpRange;
    SharedPtr<Node> node;
    SharedPtr<StaticModel> object;

public:
    class MapPlaneKey
    {
    public:
        MapPlaneKey(int _d0 = 0, int _d1 = 0, int _d2 = 0) : d0(_d0), d1(_d1), d2(_d2) {};
        int d0;
        int d1;
        int d2;

        unsigned ToHash () const { return (uint)((d0 + 1) << 4) + ((d1 + 1) << 2) + (d2 + 1); }

        bool operator ==(const TerrainSegment::MapPlaneKey& keyRight) const
        {
            return d0 == keyRight.d0 && d1 == keyRight.d1 && d2 == keyRight.d2;
        }
    };

    class MapPlaneValue
    {
    public:
        MapPlaneValue(float _dX = 0, float _dZ = 0) : dX(_dX), dZ(_dZ) {};
        float dX;
        float dZ;
    };

    class MapCornerKey
    {
    public:
        MapCornerKey(int _dLeft = 0, int _dTopLeft = 0, int _dTop = 0, int _dDiagLeft = 0, int _dDiagTop = 0) :
            dLeft(_dLeft), dTopLeft(_dTopLeft), dTop(_dTop), dDiagLeft(_dDiagLeft), dDiagTop(_dDiagTop)
        {};
        int dLeft = 0;          // ≈сли < 0, лева€ €чейка ниже данной, если == 0, то равны по высоте
        int dTopLeft = 0;
        int dTop = 0;
        int dDiagLeft = 0;  // –азница по высоте между TopLeft €чейкой и той, котора€ снизу от неЄ (слева от нас)
        int dDiagTop = 0;   // –азница по высоте между TopLeft €чейкой и той, котора€ справа от неЄ (сверху от нас)

        unsigned ToHash() const
        {
            return (uint)((dLeft + 1) + ((dTopLeft + 1) << 2) + ((dTopLeft + 1) << 4) + ((dDiagLeft + 1) << 6) + ((dDiagTop + 1) << 8));
        }

        bool operator==(const TerrainSegment::MapCornerKey& keyRight) const
        {
            return dLeft == keyRight.dLeft && dTop == keyRight.dTop && dTopLeft == keyRight.dTopLeft && dDiagLeft == keyRight.dDiagLeft && dDiagTop == keyRight.dDiagTop;
        }
    };

    class MapCornerValue
    {
    public:
        MapCornerValue(int _dRow00 = 0, int _dCol00 = 0, Corner _corner00 = Urho3D::C_TOPLEFT, int _dRow01 = 0, int _dCol01 = 0, Corner _corner01 = Urho3D::C_TOPLEFT,
                       int _dRow10 = 0, int _dCol10 = 0, Corner _corner10 = Urho3D::C_TOPLEFT, int _dRow11 = 0, int _dCol11 = 0, Corner _corner11 = Urho3D::C_TOPLEFT, int _dRow12 = 0, int _dCol12 = 0, Corner _corner12 = Urho3D::C_TOPLEFT) :
                       dRow00(_dRow00), dCol00(_dCol00), corner00(_corner00),
                       dRow01(_dRow01), dCol01(_dCol01), corner01(_corner01),
                       dRow10(_dRow10), dCol10(_dCol10), corner10(_corner10),
                       dRow11(_dRow11), dCol11(_dCol11), corner11(_corner11),
                       dRow12(_dRow12), dCol12(_dCol12), corner12(_corner12)
        {};
        // Ёдо данные дл€ первого, об€зательного треугольника
        int dRow00 = 0;
        int dCol00 = 0;
        Corner corner00 = Urho3D::C_TOPLEFT;

        int dRow01 = 0;
        int dCol01 = 0;
        Corner corner01 = Urho3D::C_TOPLEFT;

        // Ёто данные дл€ второго треугольника, который может отсутствовать
        int dRow10 = 0;
        int dCol10 = 0;
        Corner corner10 = Urho3D::C_TOPLEFT;

        int dRow11 = 0;
        int dCol11 = 0;
        Corner corner11 = Urho3D::C_TOPLEFT;

        // Used if triangles no general top, adjacent to a corner
        int dRow12 = 0;
        int dCol12 = 0;
        Corner corner12 = Urho3D::C_TOPLEFT;
    };

private:

    HashMap<MapPlaneKey, MapPlaneValue> mapTopLeft;
    HashMap<MapPlaneKey, MapPlaneValue> mapTopRight;
    HashMap<MapPlaneKey, MapPlaneValue> mapBtmRight;
    HashMap<MapPlaneKey, MapPlaneValue> mapBtmLeft;

    HashMap<MapCornerKey, MapCornerValue> mapCornerTopLeft;

    TerrainSegment& operator=(const TerrainSegment&) {};
};
