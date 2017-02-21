#pragma once
#include "SegmentTerrain.h"
#include "Graphics/Objects/Plane.h"
#include "Graphics/Objects/Line.h"


enum DIR
{
    DIR_LEFT,
    DIR_TOPLEFT,
    DIR_TOP,
    DIR_TOPRIGHT,
    DIR_RIGHT,
    DIR_DOWNRIGHT,
    DIR_DOWN,
    DIR_DOWNLEFT
};


class TerrainRTS : public Object
{
    URHO3D_OBJECT(TerrainRTS, Object);

public:
    TerrainRTS(Context *context = gContext);
    ~TerrainRTS();

    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFie);

    float GetHeight(uint row, uint col);

    void SetHeight(uint row, uint col, float height);

    void Update();

    uint NumRows();

    uint NumCols();

    bool Empty();

    PlaneRTS GetIntersectionPlane(Ray &ray);

    Line GetIntersectionEdge(Ray &ray);

    PlaneRTS GetPlane(uint row, uint col);

    Vector<Vector<float>> GetMap();

    PODVector<CubeTerrain*>* GetColumnCubes(CubeTerrain *cube, DIR dir);

    static Vector<Vector<PODVector<CubeTerrain*>>> columnsCubes;

private:
    Vector<Vector<float>> level;
    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;

    SegmentTerrain *GetSegmentForCoord(uint row, uint col);

    CONSTRUCTORS(TerrainRTS, Object);
};
