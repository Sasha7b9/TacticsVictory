// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Terrain/TPlaneCube_.h"


class SideCube : public Object
{
    URHO3D_OBJECT(SideCube, Object);

public:
    SideCube(Context *context = TheContext);
    PlaneCube plane;
};
