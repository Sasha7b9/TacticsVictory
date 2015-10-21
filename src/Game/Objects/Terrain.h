#pragma once


class lTerrain : public Object
{
    OBJECT(lTerrain);

public:
    lTerrain(Vector<Vector<float> > &map);

    lPlane GetIntersection(Ray &ray);

    void SetHeight(uint row, uint col, float height);

    static const uint SIZE_BLOCK = 50;

private:
    lTerrain& operator=(const lTerrain&)
    {};

    Vector<Vector<float> >map;
    Vector<Vector<SharedPtr<lTerrainBlock>>> blocks;
    uint numBlocksInZ = 0;
    uint numBlocksInX = 0;

    Vector<Vector<float> > ExtractSubMap(uint startX, uint startZ, uint size);
};