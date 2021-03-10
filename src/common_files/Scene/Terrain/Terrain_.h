// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Object_.h"
#include "Scene/Primitives/Plane_.h"
#include "Scene/Terrain/CubeTerrain_.h"


class SegmentTerrain;


struct DIR { enum E {
    LEFT,
    TOPLEFT,
    TOP,
    TOPRIGHT,
    RIGHT,
    DOWNRIGHT,
    DOWN,
    DOWNLEFT
}; };



class TerrainT : public Object
{
    URHO3D_OBJECT(TerrainT, Object);

public:

    TerrainT(Context *context = TheContext);

    ~TerrainT();

    void CreateFromVector(const Vector<Vector<float>> &level);

    float GetHeight(uint colZ, uint rowX);

    float GetHeight(float colZ, float rowX);

    void SetHeight(uint row, uint col, float height);

    uint HeightX();

    uint WidthZ();

    bool Empty();

    // "Положить" игровой объект в точку {colZ, rowX}. Объект будет на поверхности ланшафта. Если объект может находить-
    // ся над поверхностью, его координата Y не изменится, если он находится над землёй. Иначе так же как и для
    // остальных
    void PutIn(ObjectT *object, uint colZ, uint rowX);

    TPlane GetIntersectionPlane(Ray &ray);

    Line GetIntersectionEdge(Ray &ray);

    TPlane GetPlane(uint row, uint col);

    Vector<Vector<float>> GetMap();

    PODVector<CubeTerrain*>* GetColumnCubes(const CubeTerrain *cube, DIR::E dir);

    static Vector<Vector<PODVector<CubeTerrain*>>> columnsCubes;

private:

    Vector<Vector<float>> level;

    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;

    SegmentTerrain *GetSegmentForCoord(uint row, uint col);
};
