#pragma once


#include "PlaneCube.h"


class EdgeCube : public Object
{
    URHO3D_OBJECT(EdgeCube, Object);

public:
    EdgeCube(Context *context = gContext);

    PlaneCube plane;

private:
    EdgeCube& operator=(const EdgeCube&)
    {};
};