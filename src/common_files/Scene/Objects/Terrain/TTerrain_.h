// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Terrain/TCubeTerrain_.h"
#include "Scene/Primitives/TPlane_.h"


class GameObject;
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



class TTerrain : public Object
{
    URHO3D_OBJECT(TTerrain, Object);

public:

    TTerrain(Context *context = TheContext);

    ~TTerrain();

    void CreateFromVector(const Vector<Vector<float>> &level);

    float GetHeight(uint colZ, uint rowX);

    void SetHeight(uint row, uint col, float height);

    uint HeightX();

    uint WidthZ();

    bool Empty();

    // "Положить" игровой объект в точку {colZ, rowX}. Объект будет на поверхности ланшафта. Если объект может находить-
    // ся над поверхностью, его координата Y не изменится, если он находится над землёй. Иначе так же как и для
    // остальных
    void PutIn(GameObject *object, uint colZ, uint rowX);

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
