#pragma once



class CornerCube : public Object
{
    URHO3D_OBJECT(CornerCube, Object);

public:
    CornerCube(Context *context = gContext);

private:
    DEFAULT_MEMBERS(CornerCube);
};
