#pragma once


class vTerrain : public Object
{
    OBJECT(vTerrain);

public:
    vTerrain(Vector<Vector<float> > &map);

    vPlane GetIntersection(Ray &ray);

    void SetHeight(uint row, uint col, float height);

private:
    vTerrain& operator=(const vTerrain&)
    {};

    const uint sizeBlock = 50;
    Vector<Vector<float> >map;
    Vector<Vector<SharedPtr<vTerrainBlock>>> blocks;
    uint numBlocksInZ = 0;
    uint numBlocksInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
};