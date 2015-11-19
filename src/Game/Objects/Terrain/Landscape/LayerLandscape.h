#pragma once


#include "CubeLandscape.h"


class LayerLandscape : public Object
{
    URHO3D_OBJECT(LayerLandscape, Object);

public:
    LayerLandscape(Context *context = gContext);

    Vector<CubeLandscape> cubes;
private:
    LayerLandscape& operator=(const LayerLandscape&)
    {};
};