#pragma once


#include "SegmentTerrain.h"


class Terrain : public Object
{
    URHO3D_OBJECT(Terrain, Object);

public:
    Terrain(Context *context = gContext);

    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFie);

    float GetHeight(uint row, uint col);

private:
    Terrain& operator=(const Terrain&)
    {};

    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;
};