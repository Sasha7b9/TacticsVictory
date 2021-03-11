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


/*
   0 1 2 3 ...........................N
 0 +--------------------------------------> colZ
   |
 2 |
   |
 3 |
   |
 4 |
 . |
 . |
 . |
 . |
 . |
 . |
   |
   | rowX

*/



class TerrainT : public Object
{
    URHO3D_OBJECT(TerrainT, Object);

public:

    TerrainT(Context *context = TheContext);

    ~TerrainT();

    void Update(float dT);

    void CreateFromVector(const Vector<Vector<float>> &level);

    float GetHeight(uint rowX, uint colZ) const;
    float GetHeight(float rowX, float colZ) const;
    float GetHeight(const Vector2 coord) const;

    void SetHeight(uint row, uint col, float height);

    uint HeightX() const;
    uint WidthZ() const;

    bool IsEmpty() const;

    // "Положить" игровой объект в точку {colZ, rowX}. Объект будет на поверхности ланшафта. Если объект может находить-
    // ся над поверхностью, его координата Y не изменится, если он находится над землёй. Иначе так же как и для
    // остальных
    void PutIn(ObjectT *object, uint rowX, uint colZ);

    TPlane GetIntersectionPlane(Ray &ray);

    Line GetIntersectionEdge(Ray &ray);

    TPlane GetPlane(uint row, uint col);

    Vector<Vector<float>> GetHeightMap();

    PODVector<CubeTerrain*>* GetColumnCubes(const CubeTerrain *cube, DIR::E dir);

    static Vector<Vector<PODVector<CubeTerrain*>>> columnsCubes;

    struct LogicCell
    {
        float height;                   // Высота ячейки
        Vector<ObjectT *> objects;      // Объекты, находящиеся в ячейке
    };

    struct Level
    {
        void Clear() { level.Clear(); };

        void CreateFromVector(const Vector<Vector<float>> &lev);

        float GetHeight(uint rowX, uint colZ) const
        {
            if (colZ >= level[0].Size() || rowX >= level.Size())
            {
                return 0;
            }

            return level[rowX][colZ].height;
        }

        Vector<Vector<LogicCell>> level;
    };

private:

    Level level;
    
    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;

    SegmentTerrain *GetSegmentForCoord(uint row, uint col);
};
