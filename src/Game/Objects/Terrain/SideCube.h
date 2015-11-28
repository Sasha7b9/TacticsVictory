#pragma once


#include "PlaneCube.h"


class SideCube : public Object
{
    URHO3D_OBJECT(SideCube, Object);

public:
    SideCube(Context *context = gContext);

    PlaneCube plane;

    bool exist = false;

private:
    SideCube& operator=(const SideCube&)
    {};
};
