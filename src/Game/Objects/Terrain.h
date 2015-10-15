#pragma once


class tvTerrain : public Object
{
    OBJECT(tvTerrain);

public:
    tvTerrain(Vector<Vector<float> > &map);

    tvPlane GetIntersection(Ray &ray);

    void SetHeight(uint row, uint col, float height);

private:
    tvTerrain& operator=(const tvTerrain&)
    {};

    const uint sizeBlock = 50;
    Vector<Vector<float> >map;
    Vector<Vector<SharedPtr<tvTerrainBlock>>> blocks;
    uint numBlocksInZ = 0;
    uint numBlocksInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
};