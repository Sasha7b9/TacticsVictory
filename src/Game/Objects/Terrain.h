#pragma once


class lTerrain : public Object
{
    OBJECT(lTerrain);

public:
    lTerrain(Vector<Vector<float> > &map);
    ~lTerrain();

    lPlane GetIntersectionPlane(Ray &ray);
    lPlane GetPlane(uint row, uint col);

    lLine  GetIntersectionEdge(Ray &ray);

    void SetHeight(uint row, uint col, float height);
    float GetHeight(uint row, uint col);
    void Update();                                      // Call this function after SetHeight() for applying changes.

    void Clear();
    bool Empty();
    uint NumRows();
    uint NumCols();
    Vector<Vector<float>> GetMap() { return map; };

    static const uint SIZE_SEGMENT = 50;

private:
    lTerrain& operator=(const lTerrain&)
    {};

    Vector<Vector<float>> map;
    Vector<Vector<bool>>  heightChanged;

    Vector<Vector<SharedPtr<lTerrainSegment>>> segments;
    uint numSegmentsInZ = 0;
    uint numSegmentsInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
    Vector3 CalculateShift(uint xSegment, uint zSegment);
};