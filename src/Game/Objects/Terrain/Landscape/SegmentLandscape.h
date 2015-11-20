#pragma once


#include "LayerLandscape.h"


class SegmentLandscape : public Object
{
    URHO3D_OBJECT(SegmentLandscape, Object);

public:
    SegmentLandscape(Context *context = gContext);
    ~SegmentLandscape();


    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFile);

private:
    SegmentLandscape& operator=(const SegmentLandscape&)
    {};

    Vector<SharedPtr<LayerLandscape>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerLandscape>> underGround;     // Height [0, -1, -2, ...)

    void AddCube(SharedPtr<CubeLandscape> &cube);
    void CreateLayers();
    void Build();
};
