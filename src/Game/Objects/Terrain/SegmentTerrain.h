#pragma once


#include "LayerTerrain.h"


class SegmentTerrain : public Object
{
    URHO3D_OBJECT(SegmentTerrain, Object);

public:
    SegmentTerrain(Context *context = gContext);
    ~SegmentTerrain();

    enum
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM
    };

    void CreateFromVector(Vector<Vector<float>> &level, uint row0, uint col0, uint numRows, uint numCols);

    void Build();

    void GetColumnCubes(uint row, uint col, PODVector<CubeTerrain*> &column);

    static const uint WIDTH = 50;
    static const uint HEIGHT = 50;

    SegmentTerrain* neighbours[4];

private:
    SegmentTerrain& operator=(const SegmentTerrain&)
    {};

    Vector<SharedPtr<LayerTerrain>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerTerrain>> underGround;     // Height [0, -1, -2, ...)

    void AddCube(SharedPtr<CubeTerrain> &cube);
    void CreateLayers();
};
