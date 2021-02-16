/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "PlaneCube.h"


class SideCube : public Object
{
    URHO3D_OBJECT(SideCube, Object);

public:
    SideCube(Context *context = TheContext);
    PlaneCube plane;
};
