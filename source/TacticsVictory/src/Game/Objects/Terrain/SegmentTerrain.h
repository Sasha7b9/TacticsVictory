#pragma once
#include "LayerTerrain.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SegmentTerrain : public Object
{
    URHO3D_OBJECT(SegmentTerrain, Object);

public:

    enum
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM
    };

    SegmentTerrain(Context *context = gContext);
    ~SegmentTerrain();
    void CreateFromVector(Vector<Vector<float>> &level, uint row0, uint col0, uint numRows, uint numCols);
    void Build();
    void GetColumnCubes(uint row, uint col, PODVector<CubeTerrain*> &column);

    static const uint WIDTH = 50;
    static const uint HEIGHT = 50;
    SegmentTerrain* neighbours[4];      // Соседи соотвественно с четырёх сторон

private:
    Vector<SharedPtr<LayerTerrain>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerTerrain>> underGround;     // Height [0, -1, -2, ...)

    void AddCube(SharedPtr<CubeTerrain> &cube);
    void CreateLayers();
};
