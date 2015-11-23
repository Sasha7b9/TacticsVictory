#pragma once


#include "SegmentTerrain.h"
#include "Graphics/Objects/Plane.h"
#include "Graphics/Objects/Line.h"


class Terrain : public Object
{
    URHO3D_OBJECT(Terrain, Object);

public:
    Terrain(Context *context = gContext);

    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFie);

    float GetHeight(uint row, uint col);

    void SetHeight(uint row, uint col, float height);

    void Update();

    uint NumRows();

    uint NumCols();

    bool Empty();

    Plane GetIntersectionPlane(Ray &ray);

    Line GetIntersectionEdge(Ray &ray);

    Plane GetPlane(uint row, uint col);

    Vector<Vector<float>> GetMap();

private:
    Terrain& operator=(const Terrain&)
    {};

    Vector<Vector<float>> level;

    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;
};