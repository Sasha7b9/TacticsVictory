#pragma once


#include "SegmentLandscape.h"


class Landscape : public Object
{
    URHO3D_OBJECT(Landscape, Object);

public:
    Landscape(Context *context = gContext);

private:
    Landscape& operator=(const Landscape&)
    {};

    Vector<Vector<SharedPtr<SegmentLandscape>>> segments;
};