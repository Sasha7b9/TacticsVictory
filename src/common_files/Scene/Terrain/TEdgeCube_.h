// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Terrain/TPlaneCube_.h"


class EdgeCube : public Object
{
    URHO3D_OBJECT(EdgeCube, Object);

public:
    EdgeCube(Context *context = TheContext);
    PlaneCube plane;
};
