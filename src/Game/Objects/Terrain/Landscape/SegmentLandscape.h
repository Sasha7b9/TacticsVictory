#pragma once


#include "LayerLandscape.h"


class SegmentLandscape : public Object
{
    URHO3D_OBJECT(SegmentLandscape, Object);

public:
    SegmentLandscape(Context *context = gContext);
    ~SegmentLandscape();

    enum
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM
    };

    void CreateFromVector(Vector<Vector<float>> &level, uint row0, uint col0, uint numRows, uint numCols);

    void Build();

    static const uint WIDTH = 50;
    static const uint HEIGHT = 50;

    SegmentLandscape* neighbours[4];

private:
    SegmentLandscape& operator=(const SegmentLandscape&)
    {};

    Vector<SharedPtr<LayerLandscape>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerLandscape>> underGround;     // Height [0, -1, -2, ...)

    void AddCube(SharedPtr<CubeLandscape> &cube);
    void CreateLayers();
};
