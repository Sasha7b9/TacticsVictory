// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Primitives/Plane_.h"


class Editor : public Object
{
    URHO3D_OBJECT(Editor, Object);
public:
    Editor(Editor **self);
    void Run();
    void ClearScene();

private:
    PlaneT currentPlane;
    PlaneT selectedPlane;
    Line currentEdge;
    Line selectedEdge;
    SharedPtr<Node> lightNode;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
    void HandleMouseDown(StringHash, VariantMap&);
    void HandleKeyDown(StringHash, VariantMap&);
};
