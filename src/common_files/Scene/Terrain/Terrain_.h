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

    void Update(float dT);

    void CreateFromVector(const Vector<Vector<float>> &level);

    float GetHeight(uint colZ, uint rowX) const;
    float GetHeight(float colZ, float rowX) const;
    float GetHeight(const Vector2 coord) const;

    void SetHeight(uint row, uint col, float height);

    uint HeightX() const;
    uint WidthZ() const;

    bool IsEmpty() const;

    // "��������" ������� ������ � ����� {colZ, rowX}. ������ ����� �� ����������� ��������. ���� ������ ����� ��������-
    // �� ��� ������������, ��� ���������� Y �� ���������, ���� �� ��������� ��� �����. ����� ��� �� ��� � ���
    // ���������
    void PutIn(ObjectT *object, uint colZ, uint rowX);

    TPlane GetIntersectionPlane(Ray &ray);

    Line GetIntersectionEdge(Ray &ray);

    TPlane GetPlane(uint row, uint col);

    Vector<Vector<float>> GetHeightMap();

    PODVector<CubeTerrain*>* GetColumnCubes(const CubeTerrain *cube, DIR::E dir);

    static Vector<Vector<PODVector<CubeTerrain*>>> columnsCubes;

    struct LogicCell
    {
        float height;
    };

private:

    Vector<Vector<LogicCell>> level;
    Vector<Vector<Vector<Object *>>> objects;               // ������ ��������, ����������� � ������ ��������
    Vector<Vector<SharedPtr<SegmentTerrain>>> segments;

    SegmentTerrain *GetSegmentForCoord(uint row, uint col);
};
