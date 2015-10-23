#pragma once


class lTerrain : public Object
{
    OBJECT(lTerrain);

public:
    lTerrain(Vector<Vector<float> > &map);
    ~lTerrain();

    lPlane GetIntersection(Ray &ray);

    void SetHeight(uint row, uint col, float height);
    void Update();                                      // Call this function after SetHeight() for applying changes.

    void Clear();
    bool Empty();
    uint NumRows();
    uint NumCols();

    static const uint SIZE_BLOCK = 50;

private:
    lTerrain& operator=(const lTerrain&)
    {};

    Vector<Vector<float>> map;
    Vector<Vector<bool>>  heightChanged;

    Vector<Vector<SharedPtr<lTerrainBlock>>> blocks;
    uint numBlocksInZ = 0;
    uint numBlocksInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
};