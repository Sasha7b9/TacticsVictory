#pragma once


class Terrain : public UObject
{
    OBJECT(Terrain);

public:
    Terrain(Vector<Vector<float> > &map);
    ~Terrain();

    Plane GetIntersectionPlane(URay &ray);
    Plane GetPlane(uint row, uint col);

    Line  GetIntersectionEdge(URay &ray);

    void SetHeight(uint row, uint col, float height);
    float GetHeight(uint row, uint col);
    float GetHeight(int row, int col);
    void Update();                                      // Call this function after SetHeight() for applying changes.

    void Clear();
    bool Empty();
    uint NumRows();
    uint NumCols();
    Vector<Vector<float>> GetMap() { return map; };
    void SetVisible(bool visible);

    static const uint SIZE_SEGMENT = 50;

private:
    Terrain& operator=(const Terrain&)
    {};

    Vector<Vector<float>> map;
    Vector<Vector<bool>>  heightChanged;

    Vector<Vector<SharedPtr<TerrainSegment>>> segments;
    uint numSegmentsInZ = 0;
    uint numSegmentsInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
    Vector3 CalculateShift(uint xSegment, uint zSegment);
};