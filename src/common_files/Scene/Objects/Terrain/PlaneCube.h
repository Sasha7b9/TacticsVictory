/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once



class PointPlane
{
public:
    Vector3 coord;
    Vector3 normal;
    Vector2 texCoord;
};



class PlaneCube : public Object
{
    URHO3D_OBJECT(PlaneCube, Object);

public:
    PlaneCube(Context *context = TheContext);
    PointPlane point[4];
};
