#pragma once
#include "PlaneCube.h"



class SideCube : public Object
{
    URHO3D_OBJECT(SideCube, Object);

public:
    SideCube(Context *context = gContext);
    PlaneCube plane;

private:
    DEFAULT_MEMBERS(SideCube);
};
