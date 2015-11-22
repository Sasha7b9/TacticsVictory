#pragma once


#include "CubeTerrain.h"


class LayerTerrain : public Object
{
    URHO3D_OBJECT(LayerTerrain, Object);

public:
    LayerTerrain(Context *context = gContext);

    void AddCube(SharedPtr<CubeTerrain> &cube);

    void Create();

    void Build();

    Vector<SharedPtr<CubeTerrain>> cubes;

private:
    LayerTerrain& operator=(const LayerTerrain&)
    {};

    SharedPtr<Geometry> geometry;
    SharedPtr<Model> model;
    SharedPtr<StaticModel> object;
};