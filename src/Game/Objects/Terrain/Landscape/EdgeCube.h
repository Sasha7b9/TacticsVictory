#pragma once


class EdgeCube : public Object
{
    URHO3D_OBJECT(EdgeCube, Object);

public:
    EdgeCube(Context *context = gContext);

private:
    EdgeCube& operator=(const EdgeCube&)
    {};
};