/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Graphics/Objects/Plane.h"


class Editor : public Object
{
    URHO3D_OBJECT(Editor, Object);
public:
    Editor(Context *context);
    void Run();
    void ClearScene();

private:
    PlaneRTS currentPlane;
    PlaneRTS selectedPlane;
    Line currentEdge;
    Line selectedEdge;
    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
