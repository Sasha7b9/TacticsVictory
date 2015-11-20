#pragma once


#include "SegmentLandscape.h"


class Landscape : public Object
{
    URHO3D_OBJECT(Landscape, Object);

public:
    Landscape(Context *context = gContext);

    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFie);

private:
    Landscape& operator=(const Landscape&)
    {};

    Vector<Vector<SharedPtr<SegmentLandscape>>> segments;
};